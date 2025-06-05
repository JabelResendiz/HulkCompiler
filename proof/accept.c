
// accept.c
#include "ast.h"
#include "visitor.h"
#include "types.h"

ValueType accept(ASTNode* node, ASTVisitor* visitor) {
    switch (node->type) {
        case AST_NUM:    return visitor->visit_num(visitor, node);
        case AST_STRING: return visitor->visit_string(visitor, node);
        case AST_VAR:    return visitor->visit_var(visitor, node);
        case AST_ADD:    return visitor->visit_add(visitor, node);
        case AST_SUB:    return visitor->visit_sub(visitor, node);
        case AST_MUL:    return visitor->visit_mul(visitor, node);
        case AST_DIV:    return visitor->visit_div(visitor, node);
        case AST_CONCAT: return visitor->visit_concat(visitor, node);
        case AST_PRINT:  return visitor->visit_print(visitor, node);
        case AST_IF:     return visitor->visit_if(visitor, node);
        case AST_LET:    return visitor->visit_let(visitor, node);
        case AST_SEQ:    return visitor->visit_seq(visitor, node);
        default:         return TYPE_UNKNOWN;
    }
}
