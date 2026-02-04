#include "ppc.h"
#include "eval.h"
#include "parser.h"
#include "color.h"
#include "console.h"
#include "instr.def.h"
#include "register.def.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

// init
struct PPC_Runtime ppc_runtime;

void init_ctx(struct PPC_Ctx *ctx)
{
	ctx->runtime = &ppc_runtime;
	ctx->argv[0] = NULL;
	ctx->argc = 0;
	ctx->full_string = NULL;
	ctx->state.pipeline = 0;
}

/* Utility to free context, avoiding the memory leak */
void free_ctx(struct PPC_Ctx *ctx)
{
	if (ctx->full_string != NULL)
		free(ctx->full_string);
}

void ppc_init(void)
{
	ppc_runtime.pointer = 0;
	ppc_runtime.slots_capacity = INITIAL_SLOTSIZE;
	ppc_runtime.slots = malloc(ppc_runtime.slots_capacity * sizeof(MemorySlot));
	ppc_runtime.mode = MODE_DIRECT;
	ppc_runtime.code.max_line = 0;
	ppc_runtime.code.size = INITIAL_CODESIZE;
	ppc_runtime.code.code = (char **)calloc(ppc_runtime.code.size, sizeof(char *));
}

/* Utility to free an array, using looping for size_t n */
void free_array(char **arr, size_t n)
{
	for (size_t i = 0; i <= n; i++) {
		if (arr[i])
			free(arr[i]);
	}
	free(arr);
}

void ppc_loop(void)
{
	struct PPC_Ctx loop_ctx;
	char line[LINESIZE];
	init_ctx(&loop_ctx);

	while (1) {
		putchar(']');
		putchar(' ');

		if (fgets(line, sizeof(line), stdin) == NULL)
			break;

		if (line[1]) {
			ppc_runtime.mode = MODE_DIRECT;
			parse_line(line, &loop_ctx);
			eval(&loop_ctx);
		}
	}

	free_ctx(&loop_ctx);
}

void ppc_exit(void)
{
	putchar('\n');
	free(ppc_runtime.slots);
	free_array(ppc_runtime.code.code, ppc_runtime.code.max_line);
}

void *ppc_get_register(char *alias)
{
	for (int i = 0; i < REG_COUNT; i++) {
		if (strcmp(ppc_registers[i].alias, alias) == 0)
			return ppc_registers[i].setter;
	}

	return NULL;
}
