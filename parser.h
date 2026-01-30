/* parser - a pack of utility to parse string and more*/

#ifndef PARSER_H
#define PARSER_H

#include "ppc.h"

/* readtoken(line ctx) - utility to tokenize a string line into a
 * ctx buffer (stores to argv and argc)
 */
void readtoken(char *line, struct PPC_Ctx *ctx);

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
