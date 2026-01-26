#include "ppc.h"
#include "error.h"

#include <stdlib.h>

void PUSH_handler(struct PPC_Ctx *ctx)
{
	if (ctx->argc == 1) return;

	int src = atoi(ctx->argv[1]);
	int dest = (ctx->argc > 2) ? atoi(ctx->argv[2]) : 
		ctx->runtime->pointer;

	ctx->runtime->slots[dest].data = src;
}


