#include "ppc.h"
#include "color.h"
#include "console.h"
#include "instr.def.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

// init struct
struct PPC_Runtime ppc_runtime;
struct PPC_Ctx ppc_context;

void init(void)
{
	ppc_runtime.pointer = 0;
	ppc_runtime.slots_count = 0;
	ppc_runtime.slots_capacity = 1;
	ppc_runtime.slots = malloc(ppc_runtime.slots_capacity);

	ppc_context.runtime = &ppc_runtime;
}

void interpret(struct PPC_Ctx *ctx)
{
	ctx->runtime->mode = MODE_DIRECT;

	for (int i = 0; i < INST_COUNT; i++) {
		if (strcmp(instr_list[i].name, ctx->argv[0]) == 0) {
			instr_list[i].handler(ctx);
			return;
		}
	}
	
	console_err("Unknown instr %s.", ctx->argv[0]);
}

void readtoken(char *line, struct PPC_Ctx *ctx)
{
	int i = 0;
	ctx->argc = 0;
	char *token;

	while ((token = strsep(&line, " ,\n\t\r")) != NULL && i < ARGSSIZE) {
		if (*token == '\0') continue;

		ctx->argv[i++] = token;
		ctx->argc++;
	}
}

void interpreter_loop(void)
{
	char line[LINESIZE];

	while (1) {
		printf("%s]", BRIGHT_GREEN);
		if (fgets(line, sizeof(line), stdin) == NULL)
			break;

		if (strlen(line) > 1) {
			readtoken(line, &ppc_context);
			interpret(&ppc_context);
		}
	}
}

int main()
{
	init();
	interpreter_loop();
	return 0;
}
