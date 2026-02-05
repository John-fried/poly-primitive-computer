/* parser - a pack of utility to parse string and more*/

#ifndef PARSER_H
#define PARSER_H

#define PARSER_TOK_COMMENT 		';'
#define PARSER_TOK_SUBEVAL_OPEN 	'['
#define PARSER_TOK_SUBEVAL_CLOSE 	']'

#include "ast.h"

struct ASTNode *parser_parse_line(char *line);
struct ASTNode *ast_create(NodeType type, char *token);
void ast_add_arg(struct ASTNode *parent, struct ASTNode *child);
void ast_free(struct ASTNode *node);

/* --- Utility --- */

#ifdef PARSER_DEBUG
void ast_print(struct ASTNode *node, int level);
#endif

#ifdef PARSER_UTIL

/* find_range(str, *min, *max) - utility to find range between
 * integrer N1..N2, and stores min/max integrer into min
 * and max pointer buffer	(example str: "1..10").
 * stores 0 to min and 1 to max as default if failed
 */
void find_range(const char *str, int *min, int *max);
#endif

#endif /* PARSER_H */
