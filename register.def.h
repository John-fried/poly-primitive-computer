/* register.def.h - Definition for register alias for PPC */


#ifndef PPC_REGISTER_DEF_H
#define PPC_REGISTER_DEF_H

#include "ppc.h"

struct PPC_Reg ppc_registers[] = {
	{"sp",		&ppc_runtime.pointer},
	{"gpr0",	&ppc_runtime.registers.gpr[0]},
	{"gpr1",	&ppc_runtime.registers.gpr[1]},
	{"gpr2",	&ppc_runtime.registers.gpr[2]},
};
#define REG_COUNT ((int)(sizeof(ppc_registers) / sizeof(ppc_registers[0])))

#endif /* PPC_REGISTER_DEF_H */
