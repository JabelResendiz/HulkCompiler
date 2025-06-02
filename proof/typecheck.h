

#ifndef TYPECHECK_H
#define TYPECHECK_H

#include "ast.h"
#include "env.h"
#include "visitor.h"

ASTVisitor make_typechecker(Env* env, void (*log)(const char*));

#endif
