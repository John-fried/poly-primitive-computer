#ifndef PPC_INSTR_DEF_H
#define PPC_INSTR_DEF_H

#include "ppc.h"

typedef struct PPC_Value (*instruction_handler)(struct PPC_Ctx *context);

struct PPC_Instr {
	uint16_t opcode;
	instruction_handler handler;
} __attribute__((aligned(8)));

/* Macro for instruction parameter */
#define INSTR_PARAM 		struct PPC_Ctx *ctx

#define MKOPCODE(s) (uint16_t)( \
	((((uint16_t)s[0]) << 8) | ((s[0] && s[1]) ? (uint8_t)s[1] : 0)) ^ \
	(uint16_t)(sizeof(s) - 1) \
)

/* Macro to create a function */
#define MKINSTR(name) \
	PPC_Value name##_handler(INSTR_PARAM); \
	__attribute__((used, retain, section("ppc_instr"))) \
	static const struct PPC_Instr _entry_##name = { \
		MKOPCODE(#name), \
		name##_handler \
	}; \
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

#endif /* PPC_INSTR_DEF_H */
