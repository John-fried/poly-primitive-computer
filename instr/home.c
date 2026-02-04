#include "instr.def.h"

#include <stdio.h>

MKINSTR(home)
{
	(void)ctx;
	IFNPIPE printf("\033[H\033[2J\033[3J");
	fflush(stdout);
	return VAL_SUCCESS;
}
