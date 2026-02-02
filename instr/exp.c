#include "ppc.h"
#include "console.h"
#include "mmagutil.h"
#include "instr.def.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

MKINSTR(exp)
{
	int capacity = (ctx->argc > 1) ? atoi(ctx->argv[1]) : 1;
	return (void *)(intptr_t) mmag_expand(capacity);
}


