/* LIST, ppc builtin command to see your code */

#include "ppc.h"

#include <stdio.h>
#include <string.h>

void LIST_handler(struct PPC_Ctx *ctx)
{
	for (int i = 0; i <= ctx->runtime->code.max_line; i++) {
		char *code = ctx->runtime->code.code[i];

		if (!code || strlen(code) <= 1) continue;

		printf("%d: %s\n", i, code);
	}
	printf("EOF\n");
}
