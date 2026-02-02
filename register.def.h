/* register.def.h - Definition for register alias for PPC */


#ifndef REGISTER_DEF_H
#define REGISTER_DEF_H

#include "ppc.h"

struct PPC_Reg ppc_registers[] = {
	{"mpr", &ppc_runtime.pointer},
};
#define REG_COUNT ((int)(sizeof(ppc_registers) / sizeof(ppc_registers[0])))

#endif /* REGISTER_DEF_H */
