#include "ppc.h"
#include "instr.def.h"

#include <stdio.h>

MKINSTR(home)
{
	(void) ctx;
	printf("\033[H\033[2J\033[3J");
	return NULL;
}

