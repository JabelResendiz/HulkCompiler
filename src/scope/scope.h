

#ifndef SCOPE_H
#define SCOPE_H

#include "../ast/type.h"

typedef struct Symbol Symbol;
typedef struct Function Function;
typedef struct Scope Scope;
typedef struct EnvItem EnvItem;
typedef struct Env Env;
typedef struct UsageElemental UsageElemental;
typedef struct Usage Usage;

// Representa una variable o tipo definido el lenguaje
typedef struct Symbol
{
    char *name;
    int param;
    TypeValue* type;
    Symbol *next;
    Usage* usage;
} Symbol;

// //Representa una funcion del lenguaje
typedef struct Function
{
    char* name;
    int count_args;
    TypeValue** args_types;
    TypeValue* result_types;
    Function* next;
}Function;

// //Tabla de funcionaes para ver todas las funciones de un entorno
typedef struct FuncTable
{
    Function* first;
    int count;
}FuncTable;

typedef struct FunctionComparisonState {
    int is_match;                // Indica si hay coincidencia total
    int name_matches;            // Coincidencia de nombres
    int parameters_matched;      // Número de parámetros que coinciden
    int first_function_arity;    // Aridad de la primera función
    int second_function_arity;   // Aridad de la segunda función
    char* first_type_name;       // Nombre del tipo principal de la primera función
    char* second_type_name;      // Nombre del tipo principal de la segunda función
    int current_parameter_index; // Posición del parámetro siendo comparado
} FunctionComparisonState;

typedef struct FuncStructure
{
    Function* function;
    FunctionComparisonState * state;
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
typedef struct EnvItem
{
    struct ASTNode *usages;
    TypeValue *computed_type;
    EnvItem *next;
} EnvItem;

typedef struct Env
{
    int env_count;
    EnvItem * start;
    Env *parent;
} Env;


typedef struct UsageElemental
{
    struct ASTNode* node;
    struct UsageElemental* next;
}UsageElemental;

typedef struct Usage {
    UsageElemental* first;   // una lista de astnodes
    UsageElemental* last;
    int count;              // Contador de referencias
} Usage;


typedef struct UnifiedIndex
{
    int value;
    struct UnifiedIndex* next;
}UnifiedIndex;

void free_unified_index(UnifiedIndex* u);

Scope* create_scope(Scope *parent);

void free_scope(Scope *scope);
void scope_add_symbol(Scope *scope,
               const char *name,
               TypeValue* type,
               struct ASTNode *value , int param);

void scope_add_function (Scope* scope,
                         int arg_count,
                         TypeValue** args_types,
                         TypeValue* result_tpyes,
                         char* name);

void scope_add_type(Scope * scope, TypeValue* type);

Symbol* find_symbol_in_scope(Scope* scope,const char* name);
Symbol* scope_lookup(Scope* scope,const char* name);

Function* find_function_by_name(Scope* scope,char* name);

void init(Scope* scope);

void free_scope(Scope* scope);

void free_func_table(FuncTable* table);
// void free_symbol(Symbol* symbol);

// void init(Scope* scope);


Symbol* find_type_scopes(Scope* scope, const char* type_name);

Symbol* lookup_parameter (Scope* scope, const char * name);

FuncStructure* match_function_scope(Scope *scope,Function* f,Function* second);

int compare_functions_signature(Function* f1, Function* f2);

FunctionComparisonState* compare_argument_types(TypeValue** args1, TypeValue** args2,int number_counts);


Env * create_env(Env* parent);
void free_env(Env* env);


Usage* add_usages(struct ASTNode* node , Usage* list);


int register_type_member_in_env(Env *env, struct ASTNode *node, char *type_name);

EnvItem* find_env_item_by_kind(Env* env, const char* name, int is_function);

char* generate_underscored_name(const char* prefix, const char* base);
char* remove_type_prefix(const char* full_name,const char * type_name);

EnvItem* lookup_type_member_recursive(Env* context, const char* full_name, TypeValue* type, int is_function) ;

Symbol* lookup_type_attr(TypeValue* type,char* attr_name);



FuncStructure* find_function_in_hierarchy(TypeValue* type, Function* f, Function* dec);

#endif
