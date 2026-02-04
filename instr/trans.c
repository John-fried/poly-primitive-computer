/**
 * TRANS - an instruction to translate characters into integrer
 **/

#include "instr.def.h"

#include <stdint.h>
#include <stdio.h>

MKINSTR(trans)
{
	_ARGC_MIN(2)

	int character = ctx->argv[1][0];
	IFNPIPE printf("%d\n", character);
	return VAL_INT(character);
}
