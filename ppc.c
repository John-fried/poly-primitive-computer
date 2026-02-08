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
	ctx->argv[0] = VAL_NULL;
	ctx->argc = 0;
	ctx->state.pipeline = 0;
}

void ppc_init(void)
{
	ppc_runtime.line = 0;
	ppc_runtime.pointer = 0;
}

void ppc_halt(void)
{
	exit(0);
}

void *ppc_get_register(char *alias)
{
	for (int i = 0; i < REG_COUNT; i++) {
		if (strcmp(ppc_registers[i].alias, alias) == 0)
			return ppc_registers[i].setter;
	}

	return NULL;
}
