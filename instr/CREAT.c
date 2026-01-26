#include "ppc.h"
#include "console.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

void CREAT_handler(struct PPC_Ctx *ctx)
{
	int new_capacity = (ctx->argc > 1) ? atoi(ctx->argv[1]) : 1;
	void *tmp = realloc(ctx->runtime->slots,
			ctx->runtime->slots_capacity + new_capacity * 
			sizeof(MemorySlot));

	if (!tmp) {
		console_err("%s", strerror(errno));
		return;
	}

	ctx->runtime->slots = tmp;
	ctx->runtime->slots_count++;
	ctx->runtime->slots_capacity = new_capacity;
}


