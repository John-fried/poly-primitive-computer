#include "parser.h"
#include "ppc.h"
#include "instr.def.h"

#include <string.h>
#include <stdlib.h>

MKINSTR(RUN)
{
	struct PPC_Ctx run_ctx;
	char *code;

	for (int i = 0; i <= ctx->runtime->code.max_line; i++) {
			if (!ctx->runtime->code.code[i]) continue;

			code = strdup(ctx->runtime->code.code[i]);

			if (strlen(code) <= 1) continue;

			init_ctx(&run_ctx);
			run_ctx.runtime->mode = MODE_CODE;
			ppc_context.line = i;

			readtoken(code, &run_ctx);
			interpret(&run_ctx);
			free(code);
	}
}
