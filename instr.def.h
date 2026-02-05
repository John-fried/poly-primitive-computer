#ifndef INSTR_DEF_H
#define INSTR_DEF_H

#include "ppc.h"

typedef struct PPC_Value (*instruction_handler)(struct PPC_Ctx *context);

struct PPC_Instr {
	char *name;
	instruction_handler handler;
} __attribute__((aligned(8)));

/* Macro for instruction parameter */
#define INSTR_PARAM 		struct PPC_Ctx *ctx

/* Macro to create a function */
#define MKINSTR(name) \
    PPC_Value name##_handler(INSTR_PARAM); \
    __attribute__((used, section("ppc_instr"))) \
    static const struct PPC_Instr _entry_##name = { #name, name##_handler }; \
    PPC_Value name##_handler(INSTR_PARAM)

/* Macro for return value */
#define VAL_ERROR 		(PPC_Value){VAL_INTEGRER, "", 1}
#define VAL_SUCCESS 		(PPC_Value){VAL_INTEGRER, "", 0}
#define VAL_STR(x)		(PPC_Value){VAL_STRING, x, 0}
#define VAL_INT(x)		(PPC_Value){VAL_INTEGRER, "", x}

/* Macro for conditional things */
#define IFPIPE			if (ctx->state.pipeline)	/* if in pipeline */
#define IFNPIPE			if (!ctx->state.pipeline)	/* if not in pipeline */

/* Macro for fast return - attribute prerequire */
#define _ARGC_MIN(x)		if (ctx->argc < x) return VAL_ERROR;

#endif /* INSTR_DEF_H */
