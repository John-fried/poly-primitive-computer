#ifndef INSTR_DEF_H
#define INSTR_DEF_H

#include "ppc.h"

typedef void (*instruction_handler)(struct PPC_Ctx *context);

struct PPC_Instr {
	char name[64];
	instruction_handler handler;
};

#define MKINSTR(name) void name ## _handler(struct PPC_Ctx *ctx) // will be replaced as: void NAME_handler(...)
#define MKINSTR_L(name) {#name, name ## _handler}  // will be replaced as: {NAME, NAME_handler}

// _MAKE_INSTR_USES_ - to avoid include issues in instr/*.c
#ifdef _MAKE_INSTR_USES_
#define _MAKE_INSTR_USES_MACRO_

MKINSTR(RUN);
MKINSTR(LIST);
MKINSTR(HOME);
MKINSTR(MOV);
MKINSTR(EXP);
MKINSTR(PUT);
MKINSTR(PRINT);
MKINSTR(TRANS);

struct PPC_Instr instr_list[] = {
	MKINSTR_L(RUN),
	MKINSTR_L(LIST),
	MKINSTR_L(HOME),
	MKINSTR_L(MOV),
	MKINSTR_L(EXP),
	MKINSTR_L(PUT),
	MKINSTR_L(PRINT),
	MKINSTR_L(TRANS),
};
#define INST_COUNT ((int)(sizeof(instr_list) / sizeof(instr_list[0])))
#endif /* _MAKE_INSTR_USES_MACRO_ */


#endif /* INSTR_DEF_H */
