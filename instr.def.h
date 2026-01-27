#ifndef INSTR_DEF_H
#define INSTR_DEF_H

#include "ppc.h"

typedef void (*instruction_handler)(struct PPC_Ctx *context);

struct PPC_Instr {
	char name[64];
	instruction_handler handler;
};

#define MKINSTR(name) void name ## _handler(struct PPC_Ctx *ctx)
#define MKINSTR_L(name) {#name, name ## _handler},

// will be replaced as: void NAME_handler(...)
MKINSTR(RUN);
MKINSTR(HOME);
MKINSTR(MOV);
MKINSTR(CREAT);
MKINSTR(PUSH);
MKINSTR(PRINT);
MKINSTR(TRANS);

struct PPC_Instr instr_list[] = {
	// will be replaced as: {NAME, NAME_handler},
	MKINSTR_L(RUN)
	MKINSTR_L(HOME)
	MKINSTR_L(MOV)
	MKINSTR_L(CREAT)
	MKINSTR_L(PUSH)
	MKINSTR_L(PRINT)
	MKINSTR_L(TRANS)
};
#define INST_COUNT ((int)(sizeof(instr_list) / sizeof(instr_list[0])))

#endif /* INSTR_DEF_H */
