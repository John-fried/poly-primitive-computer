/* mov - the best instruction ever to interact with data */

#include "ppc.h"
#include "error.h"
#include "memory.h"
#include "instr.def.h"

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

MKINSTR(mov)
{
	_ARGC_MIN(3)

	int *dest_reg = NULL;
	int *src_reg = ppc_get_register(ctx->argv[2]);
	int src = (src_reg != NULL) ? *src_reg : atoi(ctx->argv[2]);

	if ((dest_reg = ppc_get_register(ctx->argv[1])) != NULL) {
		*dest_reg = src;
		return VAL_SUCCESS;
	}

	mem_write(atoi(ctx->argv[1]), src);
	return VAL_SUCCESS;
}
