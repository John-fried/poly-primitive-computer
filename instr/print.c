#include "ppc.h"
#include "parser.h"
#include "memory.h"
#include "instr.def.h"

#include <unistd.h>
#include <stdlib.h>
#include <string.h>

MKINSTR(print)
{
	IFPIPE return VAL_ERROR;

	_ARGC_MIN(2)
	char c;

	for (int i = 1; i < ctx->argc; i++) {
		/* find range between n1..n2 */
		if (strstr(ctx->argv[i], "..")) {
			int min, max;

			find_range(ctx->argv[i], &min, &max);
			for (int j = min; j <= max; j++) {
				c = mem_get(j);
				write(1, &c, 1);
			}
		} else {
			c = mem_get(atoi(ctx->argv[i]));
			write(1, &c, 1);
		}
	}

	write(1, "\n", 1);
	return VAL_SUCCESS;
}
