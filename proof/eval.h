#ifndef EVAL_H
#define EVAL_H

#include "ast.h"
#include "env.h"

ASTNode* eval(ASTNode* node, Env* env);

#endif
