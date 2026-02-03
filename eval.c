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
	if (ppc_runtime.code.max_line < ppc_runtime.code.size) return 0;

	int old_line = ppc_runtime.code.size;
	int new_line = ppc_runtime.code.max_line + 1;
	int new_byte_size =  new_line * sizeof(char *);

	void *tmp = realloc(ppc_runtime.code.code, new_byte_size);

	if (unlikely(!tmp)) {
		console_errno();
		return -1;
	}

	ppc_runtime.code.code = (char **) tmp;
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

void interpret(struct PPC_Ctx *ctx)
{
	if (ctx->runtime->mode == MODE_DIRECT) {
		if (hasdigit(ctx->argv[0])) {
			int line = atoi(ctx->argv[0]);
			char code[LINESIZE];

			memset(code, 0, sizeof(code));
			if (ctx->argc > 1) {
				merge_array(ctx->argv + 1, ctx->argc - 1, code);
			}

			insert_code(line, code);
			return;
		}
	}

	for (int i = 0; i < INST_COUNT; i++) {
		if (strcmp(instr_list[i].name, ctx->argv[0]) == 0) {
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

