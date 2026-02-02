/**
 * TRANS - an instruction to translate characters into integrer
 **/

#include "ppc.h"
#include "instr.def.h"

#include <stdint.h>
#include <stdio.h>

MKINSTR(trans)
{
	if (ctx->argc == 1) return (void *)(intptr_t)1;

	int character = ctx->argv[1][0];
	printf("%d\n", character);
	return (void *)(intptr_t)character;
}
