// #include "ast_factory.h"

// void free_ast(ASTNode *node)
// {
//     //fprintf(stderr, "Vamos a liberar el AST\n");

//     // if (!node)
//     // {
//     //     return;
//     // }

//     // switch (node->type)
//     // {
//     // case NODE_BINARY_OP:
//     // case NODE_UNARY_OP:
//     // case NODE_ASSIGNMENT:
//     // case NODE_D_ASSIGNMENT:
//     // case NODE_LOOP:
//     // case NODE_TYPE_GET_ATTR:
//     //     free_ast(node->data.op_node.left);
//     //     free_ast(node->data.op_node.right);
//     //     break;
//     // case NODE_PROGRAM:
//     // case NODE_BLOCK:
//     //     for (int i = 0; i < node->data.program_node.count; i++)
//     //     {
//     //         free_ast(node->data.program_node.statements[i]);
//     //     }
//     //     free(node->data.program_node.statements);
//     //     break;
//     // case NODE_FUNC_CALL:
//     //     fprintf(stderr, "Estamos liberando una llamada a funcion con %d\n", node->data.func_node.arg_count);
//     //     for (int i = 0; i < node->data.func_node.arg_count; i++)
//     //     {
//     //         free_ast(node->data.func_node.args[i]);
//     //     }
//     //     break;
//     // case NODE_BASE_FUNC:
//     //     fprintf(stderr, "Estamos liberando una llamada a base funcion %d\n", node->data.func_node.arg_count);
//     //     for (int i = 0; i < node->data.func_node.arg_count; i++)
//     //     {
//     //         //fprintf(stderr,"aqui no hay nada\n");
//     //         free_ast(node->data.func_node.args[i]);
//     //     }
//     //     break;
//     // case NODE_FUNC_DEC:
//     // case NODE_LET_IN:
//     //     for (int i = 0; i < node->data.func_node.arg_count; i++)
//     //     {
//     //         free_ast(node->data.func_node.args[i]);
//     //     }
//     //     free_ast(node->data.func_node.body);
//     //     break;
//     // case NODE_CONDITIONAL:
//     // case NODE_TYPE_SET_ATTR:
//     //     free_ast(node->data.cond_node.body_true);
//     //     free_ast(node->data.cond_node.body_false);
//     //     free_ast(node->data.cond_node.cond);
//     //     break;
//     // // case NODE_TEST_TYPE:
//     // // case NODE_CAST_TYPE:
//     // //     free_ast(node->data.cast_test.exp);
//     // //     free(node->data.cast_test.type);
//     // //     break;
//     // case NODE_TYPE_DEC:
//     //     for (int i = 0; i < node->data.type_node.arg_count; i++)
//     //     {
//     //         free_ast(node->data.type_node.args[i]);
//     //     }
//     //     for (int i = 0; i < node->data.type_node.def_count; i++)
//     //     {
//     //         free_ast(node->data.type_node.definitions[i]);
//     //     }
//     //     for (int i = 0; i < node->data.type_node.p_arg_count; i++)
//     //     {
//     //         free_ast(node->data.type_node.p_args[i]);
//     //     }
//     //     break;
//     // case NODE_TYPE_INST:
//     //     for (int i = 0; i < node->data.type_node.arg_count; i++)
//     //     {
//     //         free_ast(node->data.type_node.args[i]);
//     //     }
//     //     break;
//     // default:
//     //     break;
//     // }
//     // destroy_scope(node->scope);
//     // destroy_context(node->context);
//     // // free(node);
//     // node = NULL;
// }
