/* mov - the best instruction ever to interact with data */

#include "ppc.h"
#include "error.h"
#include "memory.h"
#include "instr.def.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MKINSTR(mov)
{
	_ARGC_MIN(3)

	int *dest_reg = NULL;
	int *src_reg = ppc_get_register(ctx->argv[2].string);
	int src = (ctx->argv[2].type == VAL_STRING) ? *src_reg : ctx->argv[2].value;

	if (ctx->argv[1].type == VAL_STRING &&
		(dest_reg = ppc_get_register(ctx->argv[1].string)) != NULL) {
		*dest_reg = src;
		return VAL_SUCCESS;
	}

	mem_write(ctx->argv[1].value, src);
	return VAL_SUCCESS;
}
