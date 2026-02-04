#include "parser.h"
#include "eval.h"
#include "instr.def.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

MKINSTR(run)
{
	_DIRECT_ONLY

	struct PPC_Ctx run_ctx;
	char *code;
	init_ctx(&run_ctx);

	for (uint32_t i = 0; i <= ctx->runtime->code.max_line; i++) {
		if (!ctx->runtime->code.code[i])
			continue;

		code = strdup(ctx->runtime->code.code[i]);

		if (!code[0]) {
			free(code);
			continue;
		}

		run_ctx.runtime->mode = MODE_CODE;
		ctx->runtime->line = i;

		parse_line(code, &run_ctx);
		eval(&run_ctx);

		free(code);
	}

	free_ctx(&run_ctx);
	return VAL_SUCCESS;
}
