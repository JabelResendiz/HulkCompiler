

#ifndef SCOPE_H
#define SCOPE_H

#include "../ast/type.h"

typedef struct Symbol Symbol;
typedef struct Function Function;
typedef struct Scope Scope;
typedef struct ContextItem ContextItem;
typedef struct Context Context;

// Representa una variable o tipo definido el lenguaje
typedef struct Symbol
{
    char *name;
    TypeValue* type;
    Symbol *next;
} Symbol;

// //Representa una funcion del lenguaje
typedef struct Function
{
    char* name;
    int count_args;
    TypeValue* args_types;
    TypeValue* result_types;
    Function* next;
}Function;

// //Tabla de funcionaes para ver todas las funciones de un entorno
typedef struct FuncTable
{
    Function* first;
    int count;
}FuncTable;


typedef struct FuncStructure
{
    Function* function;
    //struct Tuple* tuple_state;
}FuncStructure;

// TIEMPO DE EJECUCION
typedef struct Scope
{
    int s_count;
    int t_count;
    Symbol *symbols;
    FuncTable* functions;
    Symbol* types;  // para los tipos del scope
    Scope *parent;
} Scope;

// Un elemento del contexto de compilacion
typedef struct ContextItem
{
    struct ASTNode *declaration;
    TypeValue *return_type;
    ContextItem *next;
} ContextItem;

typedef struct Context
{
    int count;
    ContextItem *first;
    Context *parent;
} Context;

Scope* create_scope(Scope *parent);
void free_scope(Scope *scope);
void scope_add_symbol(Scope *scope,
               const char *name,
               TypeValue* type,
               struct ASTNode *value);

void scope_add_function (Scope* scope,
                         int arg_count,
                         TypeValue* args_types,
                         TypeValue* result_tpyes,
                         char* name);

void scope_add_type(Scope * scope, TypeValue* type);

Symbol* find_symbol_in_scope(Scope* scope,const char* name);
Symbol* scope_lookup(Scope* scope,const char* name);

Function* find_function_by_name(Scope* scope,char* name);

void init(Scope* scope);

void free_scope(Scope* scope);
// void free_symbol(Symbol* symbol);

// void init(Scope* scope);


Symbol* find_type_scopes(Scope* scope, const char* type_name);

FuncStructure* match_function_scope(Scope *scope,Function* f,Function* second);

int compare_functions_signature(Function* f1, Function* f2);

int compare_argument_types(TypeValue** args1, TypeValue** args2,int number_counts);


#endif
