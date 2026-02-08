#include "ppc.h"
#include "ast.h"
#include "console.h"
#include "parser.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

/*forward declarations*/
int isnumeric(char *s);

/*global variables*/
ST_DATA char *cursor;

ST_FUNC void expect(int c)
{
	console_err("'%c' expected", c);
}

ST_FUNC void advance(void)
{
	if (*cursor != '\0')
		cursor++;
}

ST_FUNC void skip_junk(void)
{
	while (*cursor && (isspace(*cursor) || *cursor == ','))
		cursor++;
}

ST_FUNC struct ASTNode *parse_string(void)
{
	advance();		// Skip opening quote
	char *start = cursor;
	while (*cursor && *cursor != '"')
		advance();

	int len = cursor - start;
	char val[len + 1];
	memcpy(val, start, len);
	val[len] = '\0';

	if (*cursor == '"')
		(*cursor)++;	// Skip closing quote

	struct ASTNode *node = ast_create(NODE_STR, val);
	return node;
}

ST_FUNC struct ASTNode *parse_word(void)
{
	char *start = cursor;

	// Read until space, commas, subeval close
	while (*cursor && !isspace(*cursor) && *cursor != ','
	       && *cursor != PARSER_TOK_SUBEVAL_CLOSE)
		advance();

	if (start == cursor)
		return NULL;
	int len = cursor - start;
	if (len <= 0)
		return NULL;

	char val[len + 1];
	memcpy(val, start, len);
	val[len] = '\0';

	// Detect type IDENTIFIER or DIGIT
	NodeType type = NODE_ID;
	if (isnumeric(val)) {
		type = NODE_INT;
	}

	struct ASTNode *node = ast_create(type, val);
	return node;
}

// Recursive function untuk parse expression
struct ASTNode *parse_expr(void)
{
	skip_junk();
	if (*cursor == '\0')
		return NULL;

	// Nested Expression: [cmd arg]
	if (*cursor == PARSER_TOK_SUBEVAL_OPEN) {
		advance();	// Skip open
		skip_junk();

		// Take command
		struct ASTNode *cmd_node = parse_word();
		cmd_node->type = NODE_EXPR;

		// Take arguments
		while (*cursor && *cursor != PARSER_TOK_SUBEVAL_CLOSE) {
			struct ASTNode *arg = parse_expr();
			if (arg)
				ast_add_arg(cmd_node, arg);
			skip_junk();	/* skip argument ws */
		}

		if (*cursor == PARSER_TOK_SUBEVAL_CLOSE)
			advance();	// skip close
		else
			expect(PARSER_TOK_SUBEVAL_CLOSE);

		return cmd_node;
	}
	// String literal
	if (*cursor == '"') {
		return parse_string();
	}
	// Regular Word / Number
	return parse_word();
}

/* Entry-point: turning one line string into AST root*/
struct ASTNode *parser_parse_line(char *line)
{
	char *comment_start = strchr(line, PARSER_TOK_COMMENT);
	if (comment_start) *comment_start = '\0';

	cursor = line;
	skip_junk();

	if (*cursor == '\0')
		return NULL;

	/* Root instruction (example: 'mov') */
	struct ASTNode *root = parse_word();
	if (!root) {
		console_errno();
		return NULL;
	}
	root->type = NODE_ROOT;

	while (1) {
		skip_junk();
		if (*cursor == '\0') break;

		struct ASTNode *arg = parse_expr();
		if (arg)
			ast_add_arg(root, arg);
		else {
			console_err("Unexpected character '%c'", *cursor);
			advance();
		}
	}

	return root;
}

/************************************************************/
/* Parsing utility */
int isnumeric(char *s)
{
	if (*s == '\0') return 0;
	if (*s == '-' && isdigit(*++s)) s++;

	for (; *s; s++)
		if (!isdigit((unsigned char)*s)) return 0;

	return 1;
}

void find_range(const char *str, int *min, int *max)
{
	char *result;

	if ((result = strstr(str, ".."))) {
		char strtemp[16];
		int len = result - str;

		memcpy(strtemp, str, len);
		strtemp[len] = '\0';

		int n1 = atoi(strtemp);
		int n2 = atoi(result + 2);

		if (n1 > n2) {
			*min = n2;
			*max = n1;
			return;
		}

		*min = n1;
		*max = n2;
		return;
	}

	/* default value */
	*min = 0;
	*max = 1;
}
