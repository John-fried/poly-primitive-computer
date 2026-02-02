#include "ppc.h"
#include "error.h"
#include "mmagutil.h"
#include "instr.def.h"

#include <stdint.h>
#include <stdlib.h>

MKINSTR(put)
{
	if (ctx->argc == 1) return (void *)(intptr_t)1;

	int src = atoi(ctx->argv[1]);
	int dest = (ctx->argc > 2) ? atoi(ctx->argv[2]) :
		ctx->runtime->pointer;
	return (void *)(intptr_t)mmag_write(dest, src);
}


