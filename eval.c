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

PPC_Value eval(struct PPC_Ctx *ctx)
{
	const struct PPC_Instr *it = &__start_ppc_instr;
	for (; it < &__stop_ppc_instr; it++) {
		if (strcmp(it->name, ctx->argv[0]) == 0) {
			PPC_Value ret = it->handler(ctx);
			return ret;
		}
	}

	console_err("unknown %s", ctx->argv[0]);
	return VAL_ERROR;
}
