#include "ppc.h"

#include <stdio.h>

void HOME_handler(struct PPC_Ctx *ctx)
{
	(void) ctx;
	printf("\033[H\033[2J");
}

