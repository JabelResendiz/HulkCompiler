
// scope.c

#include "scope.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include "../ast/ast.h"



static FunctionComparisonState *init_state(int matched, int arg1_count, int arg2_count)
{
    FunctionComparisonState *state = malloc(sizeof(*state));
    *state = (FunctionComparisonState){
        .name_matches = 1,
        .first_function_arity = arg1_count,
        .second_function_arity = arg2_count,
        .is_match = matched,
        .parameters_matched = matched};

    return state;
}

void free_unified_index(UnifiedIndex *u)
{
    if (u && u->next)
        free_unified_index(u->next);

    free(u);
}

Scope *create_scope(Scope *parent)
{
    Scope *scope = (Scope *)malloc(sizeof(Scope));

    scope->symbols = NULL;
    scope->functions = NULL;
    scope->types = NULL;
    scope->parent = parent;
    scope->functions = (FuncTable *)malloc(sizeof(FuncTable));
    scope->functions->count = 0;
    scope->functions->first = NULL;
    scope->s_count = 0;
    scope->t_count = 0;

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

/// @brief buscar una variable en el scope de forma recursiva
/// @param scope el scope por donde empieza
/// @param name el nombre de la variable a buscar
/// @return
Symbol *scope_lookup(Scope *scope, const char *name)
{
    // es el find_symbol
    // busca en el actual y en todos los padres

    if (!scope)
    {
        fprintf(stderr, "\n77778888887777\n");
        return NULL;
    }

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

Function *find_function_by_name(Scope *scope, char *name)
{
    if (!scope)
        return NULL;

    Function *actual = scope->functions->first;

    for (; actual != NULL; actual = actual->next)
    {
        if (!strcmp(actual->name, name))
            return actual;
    }

    if (scope->parent)
    {
        return find_function_by_name(scope->parent, name);
    }

    return NULL;
}

// agrega un simbolo a un scope o actualiza si ya existe el symbolo
void scope_add_symbol(Scope *scope,
                      const char *name,
                      TypeValue *type,
                      struct ASTNode *value,
                      int param)
{
    Symbol *s = find_symbol_in_scope(scope, name);

    if (s)
    {
        fprintf(stderr, "Jabel\n");
        s->type = type;
        s->param = param;
        return;
    }

    Symbol *symbol = (Symbol *)malloc(sizeof(Symbol));
    symbol->name = strdup(name);
    symbol->type = type;
    symbol->param = param;
    symbol->next = scope->symbols;
    scope->symbols = symbol;
    scope->s_count++;
}

void scope_add_function(Scope *scope,
                        int arg_count,
                        TypeValue **args_types,
                        TypeValue *result_tpyes,
                        char *name)
{
    Function *func = malloc(sizeof(Function));
    func->name = name;
    func->count_args = arg_count;
    func->next = NULL;
    func->result_types = result_tpyes;

    if (arg_count > 0)
    {
        func->args_types = malloc(arg_count * sizeof(TypeValue *));
        for (int i = 0; i < arg_count; i++)
        {
            func->args_types[i] = args_types[i];
        }
    }
    else
    {
        func->args_types = NULL;
    }

    func->next = scope->functions->first;
    scope->functions->first = func;
    scope->functions->count++;
}

/// @brief Agregar un tipo al Scope dado
/// @param scope  Scopa a agregar el tipo
/// @param type El tipo que se agregar al Scope
void scope_add_type(Scope *scope, TypeValue *type)
{
    Symbol *def_type = malloc(sizeof(Symbol));
    def_type->name = type->name;
    def_type->type = type;
    def_type->next = scope->types;

    scope->types = def_type;
    scope->t_count++;
}

void init(Scope *scope)
{

    scope_add_type(scope, &TYPE_NUM);
    scope_add_type(scope, &TYPE_STRING);
    scope_add_type(scope, &TYPE_BOOLEAN);
    scope_add_type(scope, &TYPE_OBJ);
    scope_add_type(scope, &TYPE_VOID);
    scope_add_type(scope, &TYPE_ERROR);

    scope_add_function(
        scope, 0, NULL, &TYPE_VOID, "print");
    scope_add_function(
        scope, 1, (TypeValue *[]){&TYPE_NUM}, &TYPE_VOID, "print");
    scope_add_function(
        scope, 1, (TypeValue *[]){&TYPE_BOOLEAN}, &TYPE_VOID, "print");
    scope_add_function(
        scope, 1, (TypeValue *[]){&TYPE_STRING}, &TYPE_VOID, "print");
    scope_add_function(
        scope, 1, (TypeValue *[]){&TYPE_NUM}, &TYPE_NUM, "sqrt");

    scope_add_function(
        scope, 1, (TypeValue *[]){&TYPE_NUM}, &TYPE_NUM, "sin");
    scope_add_function(
        scope, 1, (TypeValue *[]){&TYPE_NUM}, &TYPE_NUM, "cos");
    scope_add_function(
        scope, 1, (TypeValue *[]){&TYPE_NUM}, &TYPE_NUM, "exp");

    scope_add_function(
        scope, 1, (TypeValue *[]){&TYPE_NUM}, &TYPE_NUM, "log");

    scope_add_function(
        scope, 2, (TypeValue *[]){&TYPE_NUM, &TYPE_NUM}, &TYPE_NUM, "log");
    scope_add_function(
        scope, 0, NULL, &TYPE_NUM, "rand");
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
    free_symbol(scope->types, scope->t_count);
    free_func_table(scope->functions);
    free(scope);
}

void free_func_table(FuncTable *table)
{
    if (!table)
        return;

    Function *current = table->first;
    int i = 0;
    while (i < table->count)
    {
        Function *next = current->next;
        free(current);
        current = next;
        i++;
    }

    free(table);
}

/// @brief (find_defined_type)Busca un tipo de dato definido por su nombre dentro de una jerarquia de ambito
/// @param scope
/// @param name
/// @return El symbol que coincide con el nombre en el Scope (recursivo)
Symbol *find_type_scopes(Scope *scope, const char *type_name)
{
    if (!scope || !type_name)
        return NULL;

    Symbol *current = scope->types;

    for (; current; current = current->next)
    {
        if (!strcmp(current->name, type_name))
            return current;
    }
    // Si no esta en el scope actual buscar en el padre

    if (scope->parent)
    {
        return find_type_scopes(scope->parent, type_name);
    }

    return NULL;
}

static FunctionComparisonState *func_equals(Function *f1, Function *f2)
{

    if (strcmp(f1->name, f2->name))
    {
        // si los nombres no son iguales, error
        FunctionComparisonState *state = init_state(0, -1, -1);
        state->name_matches = 0;
        return state;
    }

    // si le numero de argumentos es diferntes, error
    if (f1->count_args != f2->count_args)
        return init_state(0, f1->count_args, f2->count_args);

    // comprobar que los tipos de los argumentos sean iguales
    return compare_argument_types(f1->args_types, f2->args_types, f1->count_args);
}

// Busca una funcion f dentro de un Scope jerarquico, tratando de encontrar una coincidencia con una funcion existente en ese ambito o alguno de sus ancestros
FuncStructure *match_function_scope(Scope *scope, Function *f, Function *second)
{

    if (!second)
        fprintf(stderr, "Sceond es null\n");

    if (!scope)
        return NULL;
    
    int x = 1;

    FuncStructure *result = malloc(sizeof(FuncStructure));

    Function *current = scope->functions->first;

    for (int i = 0; i < scope->functions->count; ++i)
    {
        FunctionComparisonState *aux = func_equals(current, f);

        // se encontro una funcion que matcheaba bien
        if (aux->is_match)
        {
            result->function = current;
            result->state = aux;
            return result;
        }

        // si tiene el mismo nombre
        if (aux->name_matches)
        {
            x = 0;
            if ((!result->state && !aux->parameters_matched ) ||
                 aux->parameters_matched)
            {
                // si no coinciden los argumentos
                // marca que encontro al menos una y guarda ka mejor coincidencia
                result->state = aux;
                result->function = current;
            }
        }

        current = current->next;
    }

    // si no fue en el ambito actual se busca en el padre
    if (scope->parent)
    {
        FuncStructure *data = match_function_scope(scope->parent, f, second);

        // si encontro una coincidencia exacta arriba o not_found , prefiere el ersutlado del padre
        if (x || data->state->is_match)
            return data;
        
        return result;
    }

    // si no encontro nada , pero hay una declaracion de dec
    if (x && second) {
        // se compara con f
        result->state = func_equals(second, f);
        result->function = second;
    } 
    
    else if (x) {
        // si no hay dec , devuelve una tupla error
        result->state = init_state(0, -1, -1);
        result->state->name_matches = 0;
    }

    fprintf(stderr,"JABEL RESENDIZ");
    
    return result;
    
}

// Compara los arguemntos de arg1 y de arg2 para ver si son de tipos compatibles
FunctionComparisonState *compare_argument_types(TypeValue **args1, TypeValue **args2, int number_counts)
{
    FunctionComparisonState *state = malloc(sizeof(FunctionComparisonState));

    for (int i = 0; i < number_counts; ++i)
    {
        if (!compare_types(args2[i], &TYPE_ERROR) &&
            !compare_types(args2[i], &TYPE_GENERIC) &&
            !ancestor_type(args1[i], args2[i]) &&
            !compare_types(args1[i], &TYPE_GENERIC))
        {
            *state = (FunctionComparisonState){
                .is_match = 0,
                .name_matches = 1,
                .parameters_matched = 1,
                .current_parameter_index = i + 1,
                .first_type_name = args1[i]->name,
                .second_type_name = args2[i]->name};

            return state;
        }
    }

    // exito
    *state = (FunctionComparisonState){
        .is_match = 1,
        .name_matches = 1,
        .parameters_matched = 1,
        .current_parameter_index = -1,
        .first_type_name = "",
        .second_type_name = ""};
    return state;
}

/// @brief Busca un parametro en el scope actual y sus ancestros
/// @param scope El scope donde empieza la busqueda
/// @param name El nombre del parametro
/// @return El Symbol encontrado o NULL (eoc)
Symbol *lookup_parameter(Scope *scope, const char *name)
{

    for (Scope *s = scope; s; s = s->parent)
    {

        for (Symbol *current = s->symbols; current; current = current->next)
        {
            if (current->param && !strcmp(current->name, name))
            {
                return current;
            }
        }
    }

    return NULL;
}

Env *create_env(Env *parent)
{
    Env *env = malloc(sizeof(Env));
    env->start = NULL;
    env->parent = parent;
    env->env_count = 0;

    return env;
}

void free_env(Env *env)
{
    if (env)
    {
        EnvItem *curr = env->start;

        while (curr)
        {
            EnvItem *next = curr->next;
            free(curr);
            curr = next;
        }

        free(env);
    }
}

Usage *add_usages(struct ASTNode *node, Usage *list)
{
    if (!list)
    {
        list = malloc(sizeof(Usage));
        list->first = NULL;
        list->count = 0;
    }

    UsageElemental *element = malloc(sizeof(UsageElemental));

    element->node = node;
    element->next = list->first;

    list->first = element;
    list->count++;

    return list;
}

// guarda un item dentro de un entorno asociado a un tipo (save_context_fr_tyep)
int register_type_member_in_env(Env *env, struct ASTNode *node, char *type_name)
{

    if (!env || !node || !type_name)
    {
        return 0;
    }

    // Detect if the node represents a function or variable
    int is_function = node->type == AST_DECL_FUNC;

    // Extract original member name
    char *member_name = is_function ? node->data.func_node.name : node->data.binary_op.left->data.var_name;

    // Build qualified name: _<type_name>_<member_name>
    char *qualified_name = generate_underscored_name(type_name, member_name);

    // Check if an item with this name and kind already exists
    EnvItem *existing = find_env_item_by_kind(env, qualified_name, is_function);
    if (existing)
    {
        existing->computed_type = is_function ? &TYPE_GENERIC : &TYPE_VOID;
        free(qualified_name); // avoid memory leak
        return 0;
    }

    // Create new environment entry
    EnvItem *new_item = malloc(sizeof(EnvItem));
    new_item->usages = node;

    // Rename the node in AST to the qualified name
    if (is_function)
        node->data.func_node.name = qualified_name;
    else
        node->data.binary_op.left->data.var_name = qualified_name;

    // Try to determine its declared type
    Symbol *known_type = find_type_scopes(node->scope, node->static_type);
    if (known_type)
        new_item->computed_type = known_type->type;
    else
        new_item->computed_type = NULL;

    // Insert at the head of the environment
    new_item->next = env->start;
    env->start = new_item;
    env->env_count++;

    return 1;
}

/// @brief Toma dos cadena A y B retorna una nuvea cadena en el formato _A_B
/// @param prefix
/// @param base
/// @return
char *generate_underscored_name(const char *prefix, const char *base)
{
    if (!prefix || !base)
        return NULL;

    if (base[0] == '_')
    {
        // Devuelve una copia de base para evitar efectos colaterales si se libera después
        char *copy = malloc(strlen(base) + 1);
        if (copy)
            strcpy(copy, base);
        return copy;
    }

    size_t total_length = strlen(prefix) + strlen(base) + 3; // "_", "_" y '\0'
    char *result = malloc(total_length);
    if (!result)
        return NULL;

    snprintf(result, total_length, "_%s_%s", prefix, base);
    return result;
}

/// @brief Busca un EnvItem* dentro de un ENv que contenga un node (usage) con cierto nombre y luego como se puede mejorar y renombrar 
/// @param env
/// @param name
/// @param is_function
/// @return
EnvItem *find_env_item_by_kind(Env *env, const char *name, int is_function)
{
    if (!env)
        return NULL;

    EnvItem *curr = env->start;

    while (curr)
    {
        ASTNode *node = curr->usages;

        if (is_function && node->type == AST_DECL_FUNC &&
            strcmp(node->data.func_node.name, name) == 0)
        {
            return curr;
        }

        if (!is_function && node->type == AST_ASSIGNMENT &&
            strcmp(node->data.binary_op.left->data.var_name, name) == 0)
        {
            return curr;
        }

        curr = curr->next;
    }

    return NULL;
}

/// @brief Implementa una busqueda recursiva jerarquica de un miembro dentro de un entorno asociado a un tipo
/// @param context El entorno actual
/// @param full_name EL nombre del miembro
/// @param type TIpo en el que se esta buscando el miembro
/// @param is_function  Indica si se busca una funcion (1) o una variable (0)
/// @return
EnvItem *lookup_type_member_recursive(Env *context, const char *full_name, TypeValue *type, int is_function)
{
    if (!context || !type || !full_name)
        return NULL;

    // Intentar encontrar directamente en este contexto
    EnvItem *found = find_env_item_by_kind(context, full_name, is_function);
    if (found)
        return found;

    // Si no se encuentra, buscar en la clase padre
    if (type->super_type && type->super_type->def_node && type->super_type->def_node->env)
    {
        // Quitar el prefijo del tipo actual
        char *base_name = remove_type_prefix(full_name, type->name);
        if (!base_name)
            return NULL;

        // Crear nuevo nombre con el prefijo del padre
        char *parent_prefixed = generate_underscored_name(type->super_type->name, base_name);
        free(base_name);

        // Búsqueda recursiva
        EnvItem *parent_result = lookup_type_member_recursive(
            type->super_type->def_node->env, parent_prefixed, type->super_type, is_function);
        free(parent_prefixed);
        return parent_result;
    }

    return NULL;
}

/// @brief Toma un string que empieza con un prefijo y guiones basjo y elimina el prefijo ,devolvieno el sufijo
/// @param full_name
/// @param type_name
/// @return
char *remove_type_prefix(const char *full_name, const char *type_name)
{
    size_t prefix_len = strlen(type_name) + 2; // +2 for the leading and trailing underscores
    if (strlen(full_name) <= prefix_len)
        return NULL; // Invalid input

    // Verifica que el formato empiece como debe
    if (full_name[0] != '_' || strncmp(full_name + 1, type_name, strlen(type_name)) != 0 || full_name[strlen(type_name) + 1] != '_')
        return NULL;

    return strdup(full_name + prefix_len);
}

/// @brief Busca un atributo en un type , incluyendo sus padres
/// @param type El tipo asociado
/// @param attr_name El nombre del atributo
/// @return El simbolo que representa el atributo
Symbol *lookup_type_attr(TypeValue *type, char *attr_name)
{
    if (!type->def_node)
        return NULL;

    Symbol *s = find_symbol_in_scope(type->def_node->scope, attr_name);

    if (!s && type->super_type)
    {
        char *name = remove_type_prefix(attr_name, type->name);
        name = generate_underscored_name(type->super_type->name, name);
        return lookup_type_attr(type->super_type, name);
    }

    return s;
}

// Busca una funcion en una jeraquia de tipos, con manejo especial de nombres y herencia
FuncStructure *find_function_in_hierarchy(TypeValue *type, Function *f, Function *dec)
{

    if (!type->def_node)
    {
        FuncStructure *structure = malloc(sizeof(*structure));
        *structure = (FuncStructure){
            .function = NULL,
            .state = init_state(0, -1, -1)};

        structure->state->name_matches = 0;
        return structure;
    }

    FuncStructure *structure = match_function_scope(type->def_node->scope, f, dec);

    if (structure && (structure->state->is_match) || structure->state->name_matches)
    {
        return structure;
    }

    if (type->super_type)
    {
        f->name = remove_type_prefix(f->name, type->name);
        f->name = generate_underscored_name(type->super_type->name, f->name);

        return find_function_in_hierarchy(type->super_type, f, dec);
    }

    return structure;
}
