
// scope.c

#include "scope.h"
#include <stdlib.h>
#include <string.h>
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

    Symbol* current = scope->symbols;

    for (int i=0;i< scope->s_count;i++)
    {
        if(!strcmp(current->name,name))
            return current;
        
        current = current->next;
    }

    return NULL;

    
}

Symbol* scope_lookup(Scope* scope,const char* name)
{
    // es el find_symbol
    // busca en el actual y en todos los padres

    Scope *current = scope;

    while(current)
    {
        for(Symbol* s = current->symbols;s; s=s->next)
        {
            if(!strcmp(s->name,name))return s;
        }

        current = current->parent;
    }

    return NULL;
}


void scope_add_symbol(Scope *scope,
                      const char *name,
                      ValueType type,
                      struct ASTNode *value)
{
    Symbol* s = scope_lookup(scope,name);

    if(s)
    {
        s->type = type;

    }


    Symbol* symbol = (Symbol*) malloc(sizeof(Symbol));
    symbol->name= strdup(name);
    symbol->type = type;
    symbol->next = scope->symbols;
    scope->symbols = symbol;
    scope->s_count ++;
    
}

void free_symbol(Symbol* symbol, int count)
{
    for(int i=0;i<count;i++)
    {
        Symbol* next = symbol->next;
        free(symbol);
        symbol = next;
    }
}

void free_scope(Scope* scope) {
    if (scope == NULL) {
        return;
    }

    free_symbol(scope->symbols, scope->s_count);

    free(scope);
}

