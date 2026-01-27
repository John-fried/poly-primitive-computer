#include "ppc.h"
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

// init struct
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
	ppc_runtime.code.code = (char **) calloc(300, sizeof(char *));
	
	init_ctx(&ppc_context);
}

/* Utility to free an array, using looping for size_t n */
void free_array(char **arr, size_t n)
{
	for (size_t i = 0; i <= n; i++) {
		if (arr[i])
			free(arr[i]);
	}
}

void interpret(struct PPC_Ctx *ctx)
{
	if (ctx->runtime->mode == MODE_DIRECT) {	
		/* HANDLE RUN COMMAND */
		if (strcmp(ctx->argv[0], "RUN") == 0) {
			struct PPC_Ctx run_ctx;
			char *code;

			for (int i = 0; i <= ctx->runtime->code.max_line; i++) {
					if (!ctx->runtime->code.code[i]) continue;

					code = strdup(ctx->runtime->code.code[i]);

					if (strlen(code) <= 1) continue;

					init_ctx(&run_ctx);

					readtoken(code, &run_ctx);
					interpret(&run_ctx);
					free(code);
			}
			return;
		}

		/* HANDLE CODE LINE */
		if (isdigit(ctx->argv[0][0]) != 0) {
			int line = atoi(ctx->argv[0]);
			char code[LINESIZE];
			char *ptr = code;
		
			// clear code
			memset(code, 0, sizeof(code));
	
			if (ctx->argc > 1) {
				for (int i = 1; i < ctx->argc; i++) {
					strcpy(ptr, ctx->argv[i]);
					ptr += strlen(ptr);
					strcpy(ptr++, " ");
				}

			}

			ctx->runtime->code.code[line] = strdup(code);
			if (ctx->runtime->code.max_line < line) 
				ctx->runtime->code.max_line = line;

			return;
		}
	}

	for (int i = 0; i < INST_COUNT; i++) {
		if (strcmp(instr_list[i].name, ctx->argv[0]) == 0) {
			instr_list[i].handler(ctx);
			return;
		}
	}
	
	console_err("Unknown instr %s.", ctx->argv[0]);
}

void interpreter_loop(void)
{
	char line[LINESIZE];

	while (1) {
		printf("%s]", BRIGHT_GREEN);
		if (fgets(line, sizeof(line), stdin) == NULL)
			break;

		if (strlen(line) <= 1) continue;

		ppc_context.runtime->mode = MODE_DIRECT;
		readtoken(line, &ppc_context);
		interpret(&ppc_context);
	}
}

void interpreter_exit(void)
{
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
