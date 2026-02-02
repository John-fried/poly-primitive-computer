#include "ppc.h"
#include "error.h"
#include "mmagutil.h"
#include "instr.def.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MKINSTR(mov)
{
	if (ctx->argc == 1) return (void *)(intptr_t)1;

	int *dest;
	int *src = ppc_get_register(ctx->argv[2]);
	int src_atoi = atoi(ctx->argv[2]);

	if ((dest = ppc_get_register(ctx->argv[1])) != NULL) {
		*dest = (likely(src == NULL)) ? src_atoi : *src;
		return NULL;
	}

	// *dest = atoi(ctx->argv[1]); --> *dest not point to anywhere else, this will cause segfault
	// mmag_write(*dest, src_atoi);

	mmag_write(atoi(ctx->argv[1]), src_atoi);
	return NULL;
}
