/**
 * TRANS - an instruction to translate characters into integrer
 **/

#include "ppc.h"
#include "instr.def.h"

#include <stdio.h>

MKINSTR(TRANS)
{
	if (ctx->argc == 1) return;

	int character = ctx->argv[1][0];
	printf("%d\n", character);
}
