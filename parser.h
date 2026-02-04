/* parser - a pack of utility to parse string and more*/

#ifndef PARSER_H
#define PARSER_H

#define PARSER_TOK_DELIM 		" \n\t\r"
#define PARSER_TOK_COMMENT 		";"
#define PARSER_TOK_SUBEVAL_OPEN 	"["
#define PARSER_TOK_SUBEVAL_CLOSE 	"]"

#include "ppc.h"

/* merge_array(arr, n, buf) - utility to merge an array with size n
 * into string buf
 */
void merge_array(char **arr, int n, char *buf);

/* slice_string(line, ctx) - utility to slice string line into
 * ctx->argv and ctx->argc counter
 */
void slice_string(char *line, struct PPC_Ctx *ctx);

/* remove_comment(line) - remove a comment token from a string,
 * return the final string
 */
char *remove_comment(char *line);

/* parse_line(line, ctx) - Utility to parse line and store parsed
 * context into ctx, (warning: not preprocessing, just simple parse
 * and then store to context)
 */
void parse_line(char *line, struct PPC_Ctx *ctx);

/* preprocess_line(line) - utility to preprocess line before evaluated
 * also store to context
 */
void preprocess_line(char *line, struct PPC_Ctx *ctx);

/* find_range(str, *min, *max) - utility to find range between
 * integrer N1..N2, and stores min/max integrer into min
 * and max pointer buffer	(example str: "1..10").
 * stores 0 to min and 1 to max as default if failed
 */
void find_range(const char *str, int *min, int *max);

/* has_digit - checks if a string has a digit, unlikely isdigit,
 * this function checks full string, if the string contain
 * not digit, it will return -1, otherwise 0
 */
int hasdigit(const char *str);

#endif /* PARSER_H */
