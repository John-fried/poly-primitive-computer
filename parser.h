/* parser - a pack of utility to parse string and more*/

#ifndef PPC_PARSER_H
#define PPC_PARSER_H

#define PARSER_TOK_COMMENT 		';'
#define PARSER_TOK_SUBEVAL_OPEN 	'['
#define PARSER_TOK_SUBEVAL_CLOSE 	']'

#include "ast.h"

struct ASTNode *parser_parse_line(char *line);

/* --- Utility --- */

#ifdef PARSER_UTIL

/* isnumeric - check if a string is a numerical value
 * error: -1 ("123abc")
 * passed: 0 ("120")
 */
int isnumeric(char *s);

/* find_range(str, *min, *max) - utility to find range between
 * integrer N1..N2, and stores min/max integrer into min
 * and max pointer buffer	(example str: "1..10").
 * stores 0 to min and 1 to max as default if failed
 */
void find_range(const char *str, int *min, int *max);
#endif

#endif /* PPC_PARSER_H */
