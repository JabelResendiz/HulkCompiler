// #include "ast_factory.h"


// // method to print an AST node
// void print_ast(ASTNode *node, int indent)
// {
//     if (!node)
//         return;

//     for (int i = 0; i < indent; i++)
//         printf("  ");

//     switch (node->type)
//     {
//     case NODE_PROGRAM:
//         printf("Program:\n");
//         for (int i = 0; i < node->data.program_node.count; i++)
//         {
//             print_ast(node->data.program_node.statements[i], indent + 1);
//         }
//         break;
//     case NODE_BLOCK:
//         printf("Block:\n");
//         for (int i = 0; i < node->data.program_node.count; i++)
//         {
//             print_ast(node->data.program_node.statements[i], indent + 1);
//         }
//         break;
//     case NODE_FUNC_CALL:
//         printf("Function_call: %s, receives:\n", node->data.func_node.name);
//         int arg_count = node->data.func_node.arg_count;
//         for (int i = 0; i < arg_count; i++)
//         {
//             print_ast(node->data.func_node.args[i], indent + 1);
//         }
//         break;
//     case NODE_FUNC_DEC:
//         printf("Function_Declaration: %s, returns:\n", node->data.func_node.name);
//         print_ast(node->data.func_node.body, indent + 1);
//         break;
//     case NODE_LET_IN:
//         printf("Let-in: %s\n", node->data.func_node.name);
//         print_ast(node->data.func_node.body, indent + 1);
//         break;
//     case NODE_NUMBER:
//         printf("Number: %g\n", node->data.number_value);
//         break;
//     case NODE_STRING:
//         printf("String: %s\n", node->data.string_value);
//         break;
//     case NODE_BOOLEAN:
//         printf("Boolean: %s\n", node->data.string_value);
//         break;
//     case NODE_VARIABLE:
//         printf("Variable: %s\n", node->data.variable_name);
//         break;
//     case NODE_BINARY_OP:
//     {
//         const char *op_str;
//         switch (node->data.op_node.op)
//         {
//         case OP_ADD:
//             op_str = "+";
//             break;
//         case OP_SUB:
//             op_str = "-";
//             break;
//         case OP_MUL:
//             op_str = "*";
//             break;
//         case OP_DIV:
//             op_str = "/";
//             break;
//         case OP_MOD:
//             op_str = "%";
//             break;
//         case OP_POW:
//             op_str = "^";
//             break;
//         case OP_AND:
//             op_str = "&";
//             break;
//         case OP_OR:
//             op_str = "|";
//             break;
//         case OP_CONCAT:
//             op_str = "@";
//             break;
//         case OP_DCONCAT:
//             op_str = "@@";
//             break;
//         case OP_EQ:
//             op_str = "==";
//             break;
//         case OP_NEQ:
//             op_str = "!=";
//             break;
//         case OP_GRE:
//             op_str = ">=";
//             break;
//         case OP_GR:
//             op_str = ">";
//             break;
//         case OP_LSE:
//             op_str = "<=";
//             break;
//         case OP_LS:
//             op_str = "<";
//             break;
//         default:
//             op_str = "?";
//             break;
//         }
//         printf("Binary Op: %s\n", op_str);
//         print_ast(node->data.op_node.left, indent + 1);
//         print_ast(node->data.op_node.right, indent + 1);
//         break;
//     }
//     case NODE_UNARY_OP:
//         printf("Unary Op: %s\n", node->data.op_node.op_name);
//         print_ast(node->data.op_node.left, indent + 1);
//         break;
//     case NODE_ASSIGNMENT:
//     case NODE_D_ASSIGNMENT:
//         printf("Assignment:\n");
//         print_ast(node->data.op_node.left, indent + 1);
//         print_ast(node->data.op_node.right, indent + 1);
//         break;
//     case NODE_CONDITIONAL:
//         printf("Conditional:\n");
//         for (int i = 0; i < indent + 1; i++)
//             printf("  ");
//         printf("Condition:\n");
//         print_ast(node->data.cond_node.cond, indent + 2);
//         for (int i = 0; i < indent + 1; i++)
//             printf("  ");
//         printf("If part:\n");
//         print_ast(node->data.cond_node.body_true, indent + 2);
//         for (int i = 0; i < indent + 1; i++)
//             printf("  ");
//         printf("else part:\n");
//         print_ast(node->data.cond_node.body_false, indent + 2);
//         break;
//     case NODE_LOOP:
//         printf("Loop:\n");
//         for (int i = 0; i < indent + 1; i++)
//             printf("  ");
//         printf("Condition:\n");
//         print_ast(node->data.op_node.left, indent + 2);
//         for (int i = 0; i < indent + 1; i++)
//             printf("  ");
//         printf("Body:\n");
//         print_ast(node->data.op_node.right, indent + 2);
//         break;
//     case NODE_TEST_TYPE:
//         printf("IS %s\n", node->data.cast_test.type_name);
//         print_ast(node->data.cast_test.exp, indent + 1);
//         break;
//     case NODE_CAST_TYPE:
//         printf("AS %s\n", node->data.cast_test.type_name);
//         print_ast(node->data.cast_test.exp, indent + 1);
//         break;
//     case NODE_TYPE_DEC:
//         printf("Type_Declaration: %s, inherits %s\n",
//                node->data.type_node.name,
//                node->data.type_node.parent_name);

//         for (int i = 0; i < node->data.type_node.def_count; i++)
//         {
//             print_ast(node->data.type_node.definitions[i], indent + 1);
//         }

//         break;
//     case NODE_TYPE_INST:
//         printf("Type_instance: %s, receives:\n", node->data.type_node.name);
//         arg_count = node->data.type_node.arg_count;
//         for (int i = 0; i < arg_count; i++)
//         {
//             print_ast(node->data.type_node.args[i], indent + 1);
//         }
//         break;
//     case NODE_TYPE_GET_ATTR:
//         printf("Type member: \n");
//         for (int i = 0; i < indent + 1; i++)
//             printf("  ");
//         printf(" Instance:\n");
//         print_ast(node->data.op_node.left, indent + 2);
//         for (int i = 0; i < indent + 1; i++)
//             printf("  ");
//         printf(" Member:\n");
//         print_ast(node->data.op_node.right, indent + 2);
//         break;
//     case NODE_TYPE_SET_ATTR:
//         printf("Assignment:\n");
//         print_ast(node->data.cond_node.body_true, indent + 1);
//         print_ast(node->data.cond_node.body_false, indent + 1);
//         break;
//     case NODE_BASE_FUNC:
//         printf("Base call to %s:\n", node->data.func_node.name);
//         arg_count = node->data.func_node.arg_count;
//         for (int i = 0; i < arg_count; i++)
//         {
//             print_ast(node->data.func_node.args[i], indent + 1);
//         }
//         break;
//     }
// }