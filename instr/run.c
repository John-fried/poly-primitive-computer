#include "parser.h"
#include "ppc.h"
#include "instr.def.h"

#include <stdint.h>
#include <string.h>
#include <stdlib.h>

MKINSTR(run)
{
	if (ppc_runtime.mode == MODE_CODE) return (void *)(intptr_t)1;

	struct PPC_Ctx run_ctx;
	char *code;

	for (int i = 0; i <= ctx->runtime->code.max_line; i++) {
			if (!ctx->runtime->code.code[i]) continue;

			code = strdup(ctx->runtime->code.code[i]);

			if (strlen(code) <= 1) {
				free(code);
				continue;
			}

			init_ctx(&run_ctx);
			run_ctx.runtime->mode = MODE_CODE;
			ppc_context.line = i;//accurate error line tracking

			parse_line(code, &run_ctx);
			interpret(&run_ctx);

			free_ctx(&run_ctx);
			free(code);
	}

	return NULL;
}
