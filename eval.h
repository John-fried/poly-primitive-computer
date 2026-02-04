#ifndef EVAL_H
#define EVAL_H

#include "ppc.h"

/* to realloc code size line number, return 0 as success, return -1 as failed */
int realloc_codesize(void);

/* the core of the program to evaluate an instruction */
PPC_Value eval(struct PPC_Ctx *ctx);

#endif /* EVAL_H */
