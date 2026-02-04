/* eval.c - evaluate instruction or any operation */

#include "ppc.h"
#include "eval.h"
#include "instr.def.h"
#include "console.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Instruction */
extern const struct PPC_Instr __start_ppc_instr;
extern const struct PPC_Instr __stop_ppc_instr;

/* Utility to realloc code without deleting the data*/
int realloc_codesize(void)
{
	if (ppc_runtime.code.max_line < ppc_runtime.code.size)
		return 0;

	int old_line = ppc_runtime.code.size;
	int new_line = ppc_runtime.code.max_line + 1;
	int new_byte_size = new_line * sizeof(char *);

	void *tmp = realloc(ppc_runtime.code.code, new_byte_size);

	if (unlikely(!tmp)) {
		console_errno();
		return -1;
	}

	ppc_runtime.code.code = (char **)tmp;
	ppc_runtime.code.size = new_line;

	for (int i = old_line; i < new_line; i++)
		ppc_runtime.code.code[i] = NULL;

	return 0;
}

int insert_code(int line, char *code)
{
	int old_line = ppc_runtime.code.max_line;

	if (line > old_line)
		ppc_runtime.code.max_line = line;

	if (realloc_codesize() < 0) {
		ppc_runtime.code.max_line = old_line;
		return -1;
	}

	if (ppc_runtime.code.code[line] != NULL)
		free(ppc_runtime.code.code[line]);

	ppc_runtime.code.code[line] = strdup(code);
	return 0;
}

PPC_Value eval(struct PPC_Ctx *ctx)
{
	if (ctx->runtime->mode == MODE_DIRECT) {
		if (hasdigit(ctx->argv[0])) {
			int line = atoi(ctx->argv[0]);
			char code[LINESIZE];

			/* copy code with length of (argv[0] + 2) OR (argv[0] + 1 + 1)
			 * (for space: "10 " and for newline in the end) */
			int len = strlen(ctx->full_string) - (strlen(ctx->argv[0]) + 2);
			if (len > 0) {
			    memcpy(code, ctx->full_string + (strlen(ctx->argv[0]) + 1), len);
			    code[len] = '\0';
			}

			insert_code(line, code);
			return VAL_SUCCESS;
		}
	}

	char *line = strdup(ctx->full_string);
	preprocess_line(line, ctx);

	const struct PPC_Instr *it = &__start_ppc_instr;
	for (; it < &__stop_ppc_instr; it++) {
		if (strcmp(it->name, ctx->argv[0]) == 0) {
			PPC_Value ret = it->handler(ctx);
			free(line);
			return ret;
		}
	}

	console_err("%s not found", ctx->argv[0]);

	free(line);
	return VAL_ERROR;
}
