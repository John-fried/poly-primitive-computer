/**
 * TRANS - an instruction to translate characters into integrer
 **/

#include "ppc.h"
#include <stdio.h>

void TRANS_handler(struct PPC_Ctx *ctx)
{
	if (ctx->argc == 1) return;

	int character = ctx->argv[1][0];
	printf("%d\n", character);
}
