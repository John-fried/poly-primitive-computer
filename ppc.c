#include "ppc.h"
#include "parser.h"
#include "color.h"
#include "console.h"
#define MAKE_INSTR
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
	ppc_runtime.code.size = 16;
	ppc_runtime.code.code = (char **) calloc(ppc_runtime.code.size, sizeof(char *));

	init_ctx(&ppc_context);
}

/* Utility to realloc code without deleting the data*/
void realloc_codesize(void)
{
	//dont realloc if its was still smaller/lower
	if (ppc_runtime.code.max_line <= ppc_runtime.code.size) return;

	int old_size = ppc_runtime.code.size;
	int new_size =  (ppc_runtime.code.max_line + 1) * sizeof(char *);

	void *tmp = realloc(ppc_runtime.code.code, new_size);

	if (!tmp) {
		console_err("Realloc failed for code size");
		return;
	}

	ppc_runtime.code.code = (char **) tmp;
	ppc_runtime.code.size = new_size;

	for (int i = old_size; i < ppc_runtime.code.max_line; i++) {
		ppc_runtime.code.code[i] = NULL;
	}
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

void interpret(struct PPC_Ctx *ctx)
{
	if (ctx->runtime->mode == MODE_DIRECT) {
		/* HANDLE CODE LINE */
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
