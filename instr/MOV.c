#include "ppc.h"
#include "error.h"

#include <stdlib.h>
#include <string.h>

void MOV_handler(struct PPC_Ctx *ctx)
{
	if (ctx->argc == 1) return;

	if (strcmp(ctx->argv[1], "PTR") == 0) {
		ctx->runtime->pointer = (ctx->argc > 2) ? atoi(ctx->argv[2]) : 0;
		return;
	}

	int src = atoi(ctx->argv[1]);
	int dest = (ctx->argc > 2) ? atoi(ctx->argv[2]) : 0;
	
	ctx->runtime->slots[dest].data = ctx->runtime->slots[src].data;
	ctx->runtime->slots[src].data = 0;
}
