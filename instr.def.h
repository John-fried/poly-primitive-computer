#ifndef INSTR_DEF_H
#define INSTR_DEF_H

#include "ppc.h"

typedef struct PPC_Value (*instruction_handler)(struct PPC_Ctx *context);

struct PPC_Instr {
	char name[64];
	instruction_handler handler;
};


/* Macro for return value */
#define VAL_ERROR 		(PPC_Value){VAL_INTEGRER, "", 1}
#define VAL_SUCCESS 		(PPC_Value){VAL_INTEGRER, "", 0}
#define VAL_STR(x)		(PPC_Value){VAL_STRING, #x, 0}
#define VAL_INT(x)		(PPC_Value){VAL_INTEGRER, "", x}

#define IFNPIPE			if (!ctx->state.pipeline)	/* if not in pipeline */

#define MKINSTR(name) struct PPC_Value name ## _handler(struct PPC_Ctx *ctx) /* macro to create a function */

// _MAKE_INSTR_USES_ - define this if you want to make a list/function protoytpe
#ifdef _MAKE_INSTR_USES_
#define _MAKE_INSTR_USES_MACRO_
#define MKINSTR_L(name) {#name, name ## _handler} /* make list */

/* Function-prototype */
MKINSTR(run);
MKINSTR(list);
MKINSTR(home);
MKINSTR(mov);
MKINSTR(print);
MKINSTR(trans);

/* Insturction list */
struct PPC_Instr instr_list[] = {
	MKINSTR_L(run),
	MKINSTR_L(list),
	MKINSTR_L(home),
	MKINSTR_L(mov),
	MKINSTR_L(print),
	MKINSTR_L(trans),
};
#define INST_COUNT ((int)(sizeof(instr_list) / sizeof(instr_list[0])))
#endif /* _MAKE_INSTR_USES_MACRO_ */


#endif /* INSTR_DEF_H */
