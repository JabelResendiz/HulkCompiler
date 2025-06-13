
//function.c


#include "check_semantic.h"
#include "../scope/scope.h"

void visit_call_function(ASTVisitor* v, ASTNode* node)
{
    ASTNode** args = node->data.func_node.args;

    // 1. Verificamos los argumentos
    for(int i=0;i<node->data.func_node.arg_count;i++)
    {
        args[i]->scope->parent = node->scope;
        accept(v,args[i]);
    }

    // 2. Buscar los tipos definidos en los scopes
    Scope * scope = node->scope;

    int arg_count = node->data.func_node.arg_count;

    // crear un array de tpyes de los argumentos
    TypeValue** types = malloc((sizeof(TypeValue*) *arg_count ));

    for(int i=0;i<arg_count;i++)
    {
        TypeValue* computed_type = node->computed_type;

        // buscar el tipo del argumento en el scope
        Symbol* ret = find_type_scopes(args[i]->scope,computed_type->name);

        if(ret) types[i]= ret->type;

        else types[i]= computed_type;
    }

    //

    Function* f = malloc(sizeof(Function*));

    f->name = node->data.func_node.name;
    f->count_args = node->data.func_node.arg_count;
    f->args_types = types;

    FuncStructure* func_structure = match_function_scope(scope,f,NULL);

    if(func_structure->function)
    {
        node->computed_type = func_structure->function->result_types;

        fprintf(stderr,"\nLa funcData es %s\n", func_structure->function->name);
    }

    free(types);
    free(f);

}