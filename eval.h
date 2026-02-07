#ifndef PPC_EVAL_H
#define PPC_EVAL_H

#include "ppc.h"
#include "ast.h"

/* the core of the program to evaluate an instruction */
PPC_Value eval_ast(struct ASTNode *node);

#endif /* PPC_EVAL_H */
