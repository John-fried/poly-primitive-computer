#include "ppc.h"
#include "error.h"
#include "mmagutil.h"
#include "instr.def.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

MKINSTR(mov)
{
	if (ctx->argc == 1) return (void *)(intptr_t)1;

	if (strcmp(ctx->argv[1], "PTR") == 0) {
		ctx->runtime->pointer = (ctx->argc > 2) ? atoi(ctx->argv[2]) : 0;
		return (void *)(intptr_t)1;
	}

	int src = atoi(ctx->argv[1]);
	int dest = (ctx->argc > 2) ? atoi(ctx->argv[2]) : 0;

	mmag_write(dest, ctx->runtime->slots[src].data);
	ctx->runtime->slots[src].data = 0;
	return NULL;
}
