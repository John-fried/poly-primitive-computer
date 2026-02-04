#include "parser.h"
#include "ppc.h"
#include "eval.h"
#include "instr.def.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

MKINSTR(run)
{
	if (ppc_runtime.mode == MODE_CODE)
		return VAL_ERROR;

	struct PPC_Ctx run_ctx;
	char *code;
	init_ctx(&run_ctx);

	for (uint32_t i = 0; i <= ctx->runtime->code.max_line; i++) {
		if (!ctx->runtime->code.code[i])
			continue;

		code = strdup(ctx->runtime->code.code[i]);

		if (strlen(code) <= 1) {
			free(code);
			continue;
		}

		run_ctx.runtime->mode = MODE_CODE;
		ppc_context.line = i;

		parse_line(code, &run_ctx);
		eval(&run_ctx);

		free(code);
	}

	free_ctx(&run_ctx);
	return VAL_SUCCESS;
}
