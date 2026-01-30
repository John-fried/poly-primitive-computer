#ifndef PARSER_H
#define PARSER_H

#include "ppc.h"

/* readtoken(line ctx) - utility to tokenize a string line into a 
 * ctx buffer (stores to argv and argc) 
 */
void readtoken(char *line, struct PPC_Ctx *ctx);

/* find_range(str, *min, *max) - utility to find range 
 *	between integrer N1..N2,
 *	and stores min/max integrer into min 
 *	and max pointer buffer	(example str: "1..10")
 *
 * stores 0 to min and 1 to max as default if failed
 */
void find_range(const char *str, int *min, int *max);

#endif /* PARSER_H */
