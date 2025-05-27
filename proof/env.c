
// env.c

#include <stdlib.h>
#include <string.h>
#include "env.h"

Env* create_env(Env* parent)
{
    Env* env = malloc(sizeof(Env));
    env->entries = NULL;
    env->parent = parent;
    return env;
}



void env_add(Env* env, char* name, ASTNode* value)
{
    EnvEntry* entry = malloc(sizeof(EnvEntry));
    entry->name = strdup(name);
    entry->value = value;
    entry->next = env->entries;
    env->entries = entry;
}



ASTNode* env_lookup(Env* env, const char* name)
{
    while(env){
        for (EnvEntry* e = env->entries; e; e= e->next)
        {
            if(strcmp(e->name,name)==0) return e->value;
        }

        env = env->parent;
    }

    return NULL;
}


void free_env(Env* env)
{
    while(env)
    {
        EnvEntry* entry = env->entries;

        while(entry)
        {
            EnvEntry* next = entry->next;
            free(entry->name);
            free_ast(entry->value);
            free(entry);
            entry = next;
        }

        Env* next_env = env->parent;
        free(env);
        env = next_env;
    }
}