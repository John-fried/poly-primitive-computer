#ifndef EVAL_H
#define EVAL_H

#include "ppc.h"

int realloc_codesize(void);

/* the core of the program to evaluate instruction */
PPC_Value eval(struct PPC_Ctx *ctx);

#endif /* EVAL_H */
