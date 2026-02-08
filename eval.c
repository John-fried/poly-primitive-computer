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

ST_INLN uint16_t get_hash(char *s) {
	if (!s || !s[0]) return 0;
	uint16_t h = ((uint16_t)s[0]) << 8;
	if (s[1]) h |= (uint8_t)s[1];
	return h ^ (uint16_t)strlen(s);
}

PPC_Value eval_ast(struct ASTNode *node)
{
	if (!node || !node->token[0]) return VAL_ERROR;

	switch (node->type) {
		case NODE_INT:
			return VAL_INT(atoi(node->token));
		case NODE_STR:
		case NODE_ID:
			return VAL_STR(node->token);
		case NODE_ROOT:
		case NODE_EXPR:
			goto exec_expression;

		default:
			return VAL_ERROR;
	}

exec_expression: {
	char int_pool[ARGSSIZE][12];
	const struct PPC_Instr *it = &__start_ppc_instr;
	const struct PPC_Instr *found = NULL; /* Found instruction */

	struct PPC_Ctx ctx;
	init_ctx(&ctx);

	uint16_t search_hash = get_hash(node->token);
	ctx.argc = node->argc + 1;	/* +1 as instruction name */
	ctx.argv[0] = node->token;	/* instruction name */
	ctx.state.pipeline = (node->type == NODE_EXPR); /* Only mark as pipeline if type as expr */

	for (; it < &__stop_ppc_instr; it++) {
		if (it->opcode == search_hash) {
			found = it;
			break;
		}
	}

	if (!found) {
		console_err("%d: Unrecognized opcode \"%s\"", search_hash,
			node->token);
		return VAL_ERROR;
	}

	for (int i = 0; i < node->argc; i++) {
		if (unlikely(i >= ARGSSIZE)) {
			console_err("Too many arguments!");
			return VAL_ERROR;
		}

		/* Recursive call: to get the preprocessed strings */
		PPC_Value res = eval_ast(node->args[i]);

		if (res.type == VAL_INTEGRER) {
			snprintf(int_pool[i], 12, "%d", res.value);
			ctx.argv[i+1] = int_pool[i];	/* +1 to avoid overwritting the instruction name */
		} else {
			ctx.argv[i+1] = res.string;
		}
	}

	/* Root call or Final call after preprocessing */
	PPC_Value final_res = found->handler(&ctx);
	return final_res;
}
}
