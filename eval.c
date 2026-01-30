/* eval.c - evaluate instruction or any operation */

#include "eval.h"
#define _MAKE_INSTR_USES_
#include "instr.def.h"
#include "console.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Utility to realloc code without deleting the data*/
void realloc_codesize(void)
{
	//dont realloc if its was still smaller/lower
	if (ppc_runtime.code.max_line <= ppc_runtime.code.size) return;

	int old_size = ppc_runtime.code.size;
	int new_size =  (ppc_runtime.code.max_line + 1) * sizeof(char *);

	void *tmp = realloc(ppc_runtime.code.code, new_size);

	if (!tmp) {
		console_err("Failed to realloc");
		return;
	}

	ppc_runtime.code.code = (char **) tmp;
	ppc_runtime.code.size = new_size;

	for (int i = old_size; i < ppc_runtime.code.max_line; i++) {
		ppc_runtime.code.code[i] = NULL;
	}
}

void interpret(struct PPC_Ctx *ctx)
{
	if (ctx->runtime->mode == MODE_DIRECT) {
		if (isdigit(ctx->argv[0][0]) != 0) {
			int line = atoi(ctx->argv[0]);
			char code[LINESIZE];
			char *ptr = code;

			if (ctx->runtime->code.max_line < line)
				ctx->runtime->code.max_line = line;

			// clear code & realloc
			memset(code, 0, sizeof(code));
			realloc_codesize();

			if (ctx->argc > 1) {
				for (int i = 1; i < ctx->argc; i++) {
					strcpy(ptr, ctx->argv[i]);
					ptr += strlen(ctx->argv[i]);
					if (i < ctx->argc - 1) strcpy(ptr++, " ");
				}

			}

			ctx->runtime->code.code[line] = strdup(code);
			return;
		}
	}

	for (int i = 0; i < INST_COUNT; i++) {
		if (strcmp(instr_list[i].name, ctx->argv[0]) == 0) {
			//if (!should_execute_instr(instr_list[i])) return;

			instr_list[i].handler(ctx);
			return;
		}
	}

	console_err("Unknown instr %s.", ctx->argv[0]);
}

