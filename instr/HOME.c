#include "ppc.h"
#include "instr.def.h"

#include <stdio.h>

MKINSTR(HOME)
{
	(void) ctx;
	printf("\033[H\033[2J");
}

