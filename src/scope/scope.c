
// scope.c

#include "scope.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../ast/ast.h"

Scope *create_scope(Scope *parent)
{
    Scope *scope = malloc(sizeof(Scope));

    scope->symbols = NULL;
    scope->parent = parent;

    return scope;
}

Symbol *find_symbol_in_scope(Scope *scope, const char *name)
{
    // solo busca en el entorno actual, no accede a los padres de ese entorno

    Symbol *current = scope->symbols;

    for (int i = 0; i < scope->s_count; i++)
    {
        if (!strcmp(current->name, name))
            return current;

        current = current->next;
    }

    return NULL;
}

Symbol *scope_lookup(Scope *scope, const char *name)
{
    // es el find_symbol
    // busca en el actual y en todos los padres

    Scope *current = scope;

    while (current)
    {
        for (Symbol *s = current->symbols; s; s = s->next)
        {
            if (!strcmp(s->name, name))
                return s;
        }

        current = current->parent;
    }

    return NULL;
}

Function* find_function_by_name(Scope* scope,char* name)
{
    if(!scope)return NULL;

    Function* actual = scope->functions->first;

    for(;actual != NULL;actual = actual->next)
    {
        if(!strcmp(actual->name,name))
            return actual;
        
    }

    if(scope->parent)
    {
        return find_function_by_name(scope->parent,name);
    }

    return NULL;


}

void scope_add_symbol(Scope *scope,
                      const char *name,
                      TypeValue* type,
                      struct ASTNode *value)
{
    Symbol *s = scope_lookup(scope, name);

    if (s)
    {
        s->type = type;
    }

    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
    symbol->name = strdup(name);
    symbol->type = type;
    symbol->next = scope->symbols;
    scope->symbols = symbol;
    scope->s_count++;
}

void scope_add_function(Scope *scope,
                        int arg_count,
                        TypeValue* args_types,
                        TypeValue* result_tpyes,
                        char *name)
{
    Function* func = (Function*)malloc(sizeof(Function));
    func->name = name;
    func->count_args = arg_count;
    func->next = NULL;
    func->result_types = result_tpyes;

    if(arg_count > 0)
    {
        func->args_types = malloc(arg_count * sizeof(TypeValue*));
        for(int i=0;i<arg_count;i++)
        {
            func->args_types[i]= args_types[i];
        }

    }
    else
    {
        func->args_types = NULL;
    }


    func->next = scope->functions->first;
    scope->functions->first = func;
    scope->functions->count ++;


}

void scope_add_type(Scope * scope, TypeValue* type)
{
    Symbol* def_type = malloc(sizeof(Symbol*));
    def_type->name = type->name;
    def_type->type = type;
    def_type->next = scope->types;

    scope->types = def_type;
    scope->t_count ++;

}

void init(Scope * scope)
{
    scope_add_type(scope,&TYPE_NUM);
    scope_add_type(scope,&TYPE_STRING);
    scope_add_type(scope,&TYPE_BOOLEAN);
    scope_add_type(scope,&TYPE_OBJ);
    scope_add_type(scope,&TYPE_VOID);
    scope_add_type(scope,&TYPE_ERROR);


    scope_add_function(
        scope,0,NULL,&TYPE_VOID,"print"
    );
    scope_add_function(
        scope, 1, (TypeValue*[]){ &TYPE_NUM }, &TYPE_VOID, "print"
    );
    scope_add_function(
        scope, 1, (TypeValue*[]){ &TYPE_BOOLEAN }, &TYPE_VOID, "print"
    );
    scope_add_function(
        scope, 1, (TypeValue*[]){ &TYPE_STRING }, &TYPE_VOID, "print"
    );

    scope_add_function(
        scope,1, (TypeValue*[]){&TYPE_NUM},&TYPE_NUM,"sqrt"
    );
    
    scope_add_function(
        scope,1, (TypeValue*[]){&TYPE_NUM},&TYPE_NUM,"sin"
    );
    scope_add_function
    (
        scope,1, (TypeValue*[]){&TYPE_NUM},&TYPE_NUM,"cos"
    );

    scope_add_function
    (
        scope,1, (TypeValue*[]){&TYPE_NUM},&TYPE_NUM,"exp"
    );

    scope_add_function
    (
        scope,1, (TypeValue*[]){&TYPE_NUM},&TYPE_NUM,"log"
    );

    scope_add_function
    (
        scope,2, (TypeValue*[]){&TYPE_NUM,&TYPE_NUM},&TYPE_NUM,"log"
    );

    scope_add_function(
        scope, 0, NULL, &TYPE_NUM, "rand"
    );

}

void free_symbol(Symbol *symbol, int count)
{
    for (int i = 0; i < count; i++)
    {
        Symbol *next = symbol->next;
        free(symbol);
        symbol = next;
    }
}

void free_scope(Scope *scope)
{
    if (scope == NULL)
    {
        return;
    }

    free_symbol(scope->symbols, scope->s_count);

    free(scope);
}




Symbol* find_type_scopes(Scope* scope, const char* type_name)
{
    if(!scope || ! type_name) return NULL;


    Symbol* current = scope->types;

    for(;current != NULL ; current = current->next)
    {
        if(!strcmp(current->name, type_name))
            return current;
    }
    // Si no esta en el scope actual buscar en el padre

    if(scope->parent)
    {
        return find_type_scopes(scope->parent,type_name);
    }

    return NULL;
}



// Busca una funcion f dentro de un Scope jerarquico, tratando de encontrar una coincidencia con una funcion existente en ese ambito o alguno de sus ancestros
FuncStructure* match_function_scope(Scope *scope,Function* f,Function* second)
{

    if(!second) fprintf(stderr,"Sceond es null\n");

    if(!scope) return NULL;

    FuncStructure* result = malloc(sizeof(FuncStructure*));


    Function* current = scope->functions->first;

    for(int i=0;i<scope->functions->count; ++ i)
    {
        int result_compare = compare_functions_signature(current,f);
        // se encontro una funcion que matcheaba bien
        if(result_compare)
        {
            result->function = current;
            return result;
        }

        
        current = current->next;

    }


    // si no fue en el ambito actual se busca en el padre
    if(scope->parent)
    {
        FuncStructure* data =  match_function_scope(scope->parent,f,second);

        return data;
    }

    return result;
}


// compara dos funciones(f1 y f2) devuelve 1 si son iguales en nombre, #argumento y tipos de sus args
int compare_functions_signature(Function* f1, Function* f2)
{
    if(strcmp(f1->name,f2->name))
    {
        // si tiene nombres diferentes , error
        return 0;
    }

    if(f1->count_args != f2->count_args)
    {
        // si la cantidad de arguemntos es diferentes
        return 0;
    }

    return compare_argument_types(f1->args_types,f2->args_types,f1->count_args);
}


// Compara los arguemntos de arg1 y de arg2 para ver si son de tipos compatibles
int compare_argument_types(TypeValue** args1, TypeValue** args2,int number_counts)
{
    for(int i =0;i<number_counts; ++i)
    {
        if(!compare_types(args2[i],&TYPE_ERROR)&&
            !compare_types(args1[i],&TYPE_ERROR) &&
            !ancestor_type(args1[i],args2[i])
        )
            {
                return 0;
            }
    }

    // exito
    return 1;
}