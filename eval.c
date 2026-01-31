/* eval.c - evaluate instruction or any operation */

#include "ppc.h"
#include "eval.h"
#define _MAKE_INSTR_USES_
#include "instr.def.h"
#include "console.h"
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/* Utility to realloc code without deleting the data*/
int realloc_codesize(void)
{
	//dont realloc if its was still smaller/lower
	if (ppc_runtime.code.max_line < ppc_runtime.code.size) return 0;

	int old_line = ppc_runtime.code.size;
	int new_line = ppc_runtime.code.max_line + 1;
	int new_byte_size =  new_line * sizeof(char *);

	void *tmp = realloc(ppc_runtime.code.code, new_byte_size);

	if (!tmp) {
		console_errno();
		free(tmp);
		return -1;
	}

	ppc_runtime.code.code = (char **) tmp;
	ppc_runtime.code.size = new_line;

	for (int i = old_line; i < new_line; i++)
		ppc_runtime.code.code[i] = NULL;

	return 0;
}

void interpret(struct PPC_Ctx *ctx)
{
	if (ctx->runtime->mode == MODE_DIRECT) {
		if (isdigit(ctx->argv[0][0]) != 0) {
			if (hasdigit(ctx->argv[0]) != 0) goto exec_as_instr;

			int old_line = ctx->runtime->code.max_line;
			int line = atoi(ctx->argv[0]);
			char code[LINESIZE];
			char *ptr = code;
			struct PPC_Code *code_ctx = &ctx->runtime->code;

			if (old_line < line)
				code_ctx->max_line = line;

			// clear code & realloc
			memset(code, 0, sizeof(code));
			if (realloc_codesize() != 0) {
				code_ctx->max_line = old_line;
				return;
			}

			if (ctx->argc > 1) {
				for (int i = 1; i < ctx->argc; i++) {
					strcpy(ptr, ctx->argv[i]);
					ptr += strlen(ctx->argv[i]);
					if (i < ctx->argc - 1) strcpy(ptr++, " ");
				}

			}

			/* cleanup if any & fill */
			if (code_ctx->code[line] != NULL)
				free(code_ctx->code[line]);
			ctx->runtime->code.code[line] = strdup(code);
			return;
		}
	}

exec_as_instr: {

		for (int i = 0; i < INST_COUNT; i++) {
			if (strcmp(instr_list[i].name, ctx->argv[0]) == 0) {
				//TODO: "if (!should_execute_instr(instr_list[i])) return;" add check here, example for attribute checking
				char *line = strdup(ctx->full_string);
				line = remove_comment(line);
				parse_line(line, ctx);

				instr_list[i].handler(ctx);
				free(line);
				return;
			}
		}

		console_err("%s not found", ctx->argv[0]);
	}
}

