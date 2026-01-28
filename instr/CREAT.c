#include "ppc.h"
#include "console.h"
#include "mmagutil.h"

#include <stdlib.h>
#include <string.h>
#include <errno.h>

void CREAT_handler(struct PPC_Ctx *ctx)
{
	int capacity = (ctx->argc > 1) ? atoi(ctx->argv[1]) : 1;
	mmag_expand(capacity);
}


