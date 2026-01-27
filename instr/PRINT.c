#include "ppc.h"

#include <stdlib.h>
#include <stdio.h>

void PRINT_handler(struct PPC_Ctx *ctx)
{
	if (ctx->argc == 1) {
		putchar(ctx->runtime->slots[ctx->runtime->pointer].data);
		putchar('\n');
		return;
	}

	for (int i = 1; i < ctx->argc; i++) {
		int idx = atoi(ctx->argv[i]);
		putchar(ctx->runtime->slots[idx].data);
	}
	putchar('\n');
}
