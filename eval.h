#ifndef EVAL_H
#define EVAL_H

#include "ppc.h"

void realloc_codesize(void);
void interpret(struct PPC_Ctx *ctx);

#endif /* EVAL_H */
