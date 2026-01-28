#include "ppc.h"
#include "mmagutil.h"

#include <stdlib.h>
#include <stdio.h>

void PRINT_handler(struct PPC_Ctx *ctx)
{
	if (ctx->argc == 1) {
		putchar(mmag_get(ctx->runtime->pointer));
		putchar('\n');
		return;
	}

	for (int i = 1; i < ctx->argc; i++) {
		int idx = atoi(ctx->argv[i]);
		putchar(mmag_get(idx));
	}
	putchar('\n');
}
