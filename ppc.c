#include "ppc.h"
#include "eval.h"
#include "parser.h"
#include "color.h"
#include "console.h"
#include "instr.def.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>

// init
struct PPC_Runtime ppc_runtime;
struct PPC_Ctx ppc_context;

/* utility to initialize an empty PPC_Ctx struct,
 * prevent from garbage data from a uininitialized struct
 */
void init_ctx(struct PPC_Ctx *ctx)
{
	ctx->runtime = &ppc_runtime;
	ctx->argv[0] = NULL;
	ctx->argc = 0;
}

void init(void)
{
	ppc_runtime.pointer = 0;
	ppc_runtime.slots_capacity = 1;
	ppc_runtime.slots = malloc(ppc_runtime.slots_capacity *
				   sizeof(MemorySlot));
	ppc_runtime.mode = MODE_DIRECT;
	ppc_runtime.code.max_line = 0;
	ppc_runtime.code.size = 16;
	ppc_runtime.code.code = (char **) calloc(ppc_runtime.code.size, sizeof(char *));

	init_ctx(&ppc_context);
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

void interpreter_loop(void)
{
	char line[LINESIZE];

	while (1) {
		printf("] ");
		if (fgets(line, sizeof(line), stdin) == NULL)
			break;

		if (strlen(line) <= 1) continue;

		ppc_context.runtime->mode = MODE_DIRECT;
		parse_line(line, &ppc_context);
		interpret(&ppc_context);
	}
}

void interpreter_exit(void)
{
	putchar('\n');
	free(ppc_runtime.slots);
	free_array(ppc_runtime.code.code, ppc_runtime.code.max_line);
}

int main()
{
	init();
	interpreter_loop();
	interpreter_exit();
	return 0;
}
