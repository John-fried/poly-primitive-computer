/* register.def.h - Definition for register alias for PPC */


#ifndef REGISTER_DEF_H
#define REGISTER_DEF_H

#include "ppc.h"

struct PPC_Reg ppc_registers[] = {
	{"sp",		&ppc_runtime.pointer},
	{"gpr0",	&ppc_runtime.gpr[0]},
	{"gpr1",	&ppc_runtime.gpr[1]},
	{"gpr2",	&ppc_runtime.gpr[2]},
};
#define REG_COUNT ((int)(sizeof(ppc_registers) / sizeof(ppc_registers[0])))

#endif /* REGISTER_DEF_H */
