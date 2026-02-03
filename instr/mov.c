/* mov - the best instruction ever to interact with data */

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

	int *dest_reg;
	int *src_reg = ppc_get_register(ctx->argv[2]);
	int src = (src_reg != NULL) ? *src_reg : atoi(ctx->argv[2]);

	if ((dest_reg = ppc_get_register(ctx->argv[1])) != NULL) {
		*dest_reg = src;
		return NULL;
	}

	mmag_write(atoi(ctx->argv[1]), src);
	return NULL;
}
