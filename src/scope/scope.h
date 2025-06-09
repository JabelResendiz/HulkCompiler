

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
    ValueType type;
    Symbol *next;
} Symbol;

// //Representa una funcion del lenguaje
// typedef struct Function
// {
//     char* name;
//     int count_args;
//     ValueType* args_types;
//     ValueType* result_types;
//     Function* next;
// }Function;

// //Tabla de funcionaes para ver todas las funciones de un entorno
// typedef struct FuncTable
// {
//     Function* first;
//     int count;
// }FuncTable;

// TIEMPO DE EJECUCION
typedef struct Scope
{
    int s_count;
    // int t_count;
    Symbol *symbols;
    // FuncTable* functions;
    // Symbol* defined_types;
    Scope *parent;
} Scope;

// Un elemento del contexto de compilacion
typedef struct ContextItem
{
    struct ASTNode *declaration;
    ValueType *return_type;
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
               ValueType type,
               struct ASTNode *value);

Symbol* find_symbol_in_scope(Scope* scope,const char* name);
Symbol* scope_lookup(Scope* scope,const char* name);

void free_scope(Scope* scope);
// void free_symbol(Symbol* symbol);

// void init(Scope* scope);


// void resolve_type_symbol(Scope* scope,ValueType type);

#endif
