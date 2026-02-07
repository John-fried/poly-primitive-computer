#include "ppc.h"
#include "ast.h"
#include "console.h"
#include "parser.h"

#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>

/* --- The Parser Core --- */

// Helper: Skip whitespace & commas
STATIC void skip_junk(char **cursor)
{
	while (**cursor && (isspace(**cursor) || **cursor == ','))
		(*cursor)++;
}

// Helper: Parse string literal "text"
STATIC struct ASTNode *parse_string(char **cursor)
{
	(*cursor)++;		// Skip opening quote
	char *start = *cursor;
	while (**cursor && **cursor != '"')
		(*cursor)++;

	int len = *cursor - start;
	char *val = malloc(len + 1);
	memcpy(val, start, len);
	val[len] = '\0';

	if (**cursor == '"')
		(*cursor)++;	// Skip closing quote

	struct ASTNode *node = ast_create(NODE_STR, val);
	free(val);
	return node;
}

// Helper: Parse identifier/number
STATIC struct ASTNode *parse_word(char **cursor)
{
	char *start = *cursor;

	// Read until space, commas, subeval close
	while (**cursor && !isspace(**cursor) && **cursor != ','
	       && **cursor != PARSER_TOK_SUBEVAL_CLOSE)
		(*cursor)++;

	int len = *cursor - start;
	char *val = malloc(len + 1);
	strncpy(val, start, len);
	val[len] = '\0';

	// Detect type IDENTIFIER or DIGIT
	NodeType type = NODE_ID;
	if (isdigit(val[0]) || (val[0] == '-' && isdigit(val[1]))) {
		type = NODE_INT;
	}

	struct ASTNode *node = ast_create(type, val);
	free(val);
	return node;
}

// Recursive function untuk parse expression
struct ASTNode *parse_expr(char **cursor)
{
	skip_junk(cursor);
	if (**cursor == '\0')
		return NULL;

	// Nested Expression: [cmd arg]
	if (**cursor == PARSER_TOK_SUBEVAL_OPEN) {
		(*cursor)++;	// Skip open

		// Take command
		skip_junk(cursor);
		struct ASTNode *cmd_node = parse_word(cursor);
		cmd_node->type = NODE_EXPR;

		// Take arguments
		while (**cursor && **cursor != PARSER_TOK_SUBEVAL_CLOSE) {
			struct ASTNode *arg = parse_expr(cursor);
			if (arg)
				ast_add_arg(cmd_node, arg);
			skip_junk(cursor);
		}

		if (**cursor == PARSER_TOK_SUBEVAL_CLOSE)
			(*cursor)++;	// skip close
		else
			console_warn("Expected '%c' after '%c' (pair of '%c')",
				PARSER_TOK_SUBEVAL_CLOSE, *(*cursor - 2), PARSER_TOK_SUBEVAL_OPEN);

		return cmd_node;
	}
	// String literal
	if (**cursor == '"') {
		return parse_string(cursor);
	}
	// Regular Word / Number
	return parse_word(cursor);
}

/* Entry-point: turning one line string into AST root*/
struct ASTNode *parser_parse_line(char *line)
{
	char *comment_start = strchr(line, PARSER_TOK_COMMENT);
	if (comment_start) *comment_start = '\0';

	char *cursor = line;
	skip_junk(&cursor);

	if (*cursor == '\0')
		return NULL;

	/* Root instruction (example: 'mov') */
	struct ASTNode *root = parse_word(&cursor);
	root->type = NODE_ROOT;

	while (1) {
		skip_junk(&cursor);
		if (*cursor == '\0')
			break;

		struct ASTNode *arg = parse_expr(&cursor);
		if (arg)
			ast_add_arg(root, arg);
	}

	return root;
}

void ast_print(struct ASTNode *node, int level)
{
	if (!node)
		return;

	for (int i = 0; i < level; i++)
		printf("  ");	// Indent

	char *type_name = "???";
	switch (node->type) {
	case NODE_ROOT:
		type_name = "ROOT";
		break;
	case NODE_INT:
		type_name = "INT";
		break;
	case NODE_STR:
		type_name = "STR";
		break;
	case NODE_ID:
		type_name = "ID";
		break;
	case NODE_EXPR:
		type_name = "EXPR";
		break;
	}

	if (node->type == NODE_ROOT)
		printf("\n");

	if (level > 0)
		printf("| ");

	printf("[%s] %s\n", type_name, node->token);

	for (int i = 0; i < node->argc; i++) {
		ast_print(node->args[i], level + 1);
	}
}

/* Parsing utility */
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
