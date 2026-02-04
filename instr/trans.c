/**
 * TRANS - an instruction to translate characters into integrer
 **/

#include "ppc.h"
#include "instr.def.h"

#include <stdint.h>
#include <stdio.h>

MKINSTR(trans)
{
	if (ctx->argc == 1) return VAL_ERROR;

	int character = ctx->argv[1][0];
	IFNPIPE printf("%d\n", character);
	return VAL_INT(character);
}
