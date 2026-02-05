#ifndef EVAL_H
#define EVAL_H

#include "ppc.h"

/* the core of the program to evaluate an instruction */
PPC_Value eval(struct PPC_Ctx *ctx);

#endif /* EVAL_H */
