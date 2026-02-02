/* LIST, ppc builtin command to see your code */

#include "ppc.h"
#include "instr.def.h"
#include "color.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

MKINSTR(list)
{
	int i;

	for (i = 0; i <= ctx->runtime->code.max_line; i++) {
		if (!ctx->runtime->code.code[i]) continue;
		char *code = ctx->runtime->code.code[i];

		if (strlen(code) <= 1) continue;

		printf("  %-5d %s\n", i, code);
	}

	return (void *)(intptr_t)i;
}
