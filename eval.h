#ifndef EVAL_H
#define EVAL_H

#include "ppc.h"
#include "ast.h"

/* the core of the program to evaluate an instruction */
PPC_Value eval_ast(struct ASTNode *node);

#endif /* EVAL_H */
