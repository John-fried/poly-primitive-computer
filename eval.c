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

	char *buff_to_free[ARGSSIZE];
	PPC_Value final_res = VAL_ERROR; /* Val error for the first, will be overwritten or even still */

exec_expression: {
	const struct PPC_Instr *it = &__start_ppc_instr;
	const struct PPC_Instr *found = NULL; /* Found instruction */

	struct PPC_Ctx ctx;
	init_ctx(&ctx);

	ctx.argc = node->argc + 1;	/* +1 as instruction name */
	ctx.argv[0] = node->token;	/* instruction name */
	ctx.state.pipeline = (node->type == NODE_EXPR); /* Only mark as pipeline if type as expr */

	for (; it < &__stop_ppc_instr; it++) {
		if (strcmp(it->name, node->token) == 0) {
			found = it;
			break;
		}
	}

	if (!found) {
		console_err("unknown %s", node->token);
		return VAL_ERROR;
	}

	for (int i = 0; i < node->argc; i++) {
		/* Recursive call: to get the preprocessed strings */
		PPC_Value res = eval_ast(node->args[i]);

		if (res.type == VAL_INTEGRER) {
			char *buf = malloc(12);

			if (unlikely(!buf))
				goto err_malloc;

			sprintf(buf, "%d", res.value);
			ctx.argv[i+1] = buf;	/* +1 to avoid overwriting the instruction name */
			buff_to_free[i] = buf;	/* points buff[i] to the address of buf */
		} else {
			ctx.argv[i+1] = res.string;
			buff_to_free[i] = NULL;	/* Marks as doesn't need to be freed */
		}
	}

	/* Root call or Final call after preprocessing */
	final_res = found->handler(&ctx);
}

err_malloc:
	for (int i = 0; i< node->argc; i++) {
		if (buff_to_free[i]) free(buff_to_free[i]);
	}

	return final_res;
}
