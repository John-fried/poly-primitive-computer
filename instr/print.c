#include "ppc.h"
#include "parser.h"
#include "mmagutil.h"
#include "instr.def.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

MKINSTR(print)
{
	if (ctx->argc == 1) {
		putchar(mmag_get(ctx->runtime->pointer));
		putchar('\n');
		return NULL;
	}

	for (int i = 1; i < ctx->argc; i++) {
		// find string ".." in ctx->argv[0]
		if (strstr(ctx->argv[i], "..")) {
			int min, max;

			find_range(ctx->argv[i], &min, &max);
			for (int j = min; j <= max; j++) {
				putchar(mmag_get(j));
			}
		} else
			putchar(mmag_get(atoi(ctx->argv[i])));
	}


	putchar('\n');
	return NULL;
}
