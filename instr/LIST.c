/* LIST, ppc builtin command to see your code */

#include "ppc.h"
#include "instr.def.h"

#include <stdio.h>
#include <string.h>

MKINSTR(LIST)
{
	for (int i = 0; i <= ctx->runtime->code.max_line; i++) {
		char *code = ctx->runtime->code.code[i];

		if (!code || strlen(code) <= 1) continue;

		printf("%d %s\n", i, code);
	}
	printf("EOF\n");
}
