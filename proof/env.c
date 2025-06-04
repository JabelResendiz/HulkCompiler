
// env.c

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "env.h"

Env *create_env(Env *parent)
{

    Env *env = malloc(sizeof(Env));

    // Env *a = parent;

    // while (a)
    // {
    //     fprintf(stderr, "a90909090\n ");
    //     a = a->parent;
    // }

    env->entries = NULL;

    env->parent = parent;
    return env;
}

void env_add(Env *env, char *name, ASTNode *value)
{
    EnvEntry *entry = malloc(sizeof(EnvEntry));
    entry->name = strdup(name);
    entry->value = value;
    entry->next = env->entries;
    env->entries = entry;
}

ASTNode *env_lookup(Env *env, const char *name)
{
    while (env)
    {
        for (EnvEntry *e = env->entries; e; e = e->next)
        {
            if (strcmp(e->name, name) == 0)
                return e->value;
        }

        env = env->parent;
    }

    return NULL;
}

void free_env(Env *env)
{
    while (env)
    {
        EnvEntry *entry = env->entries;

        while (entry)
        {
            EnvEntry *next = entry->next;
            free(entry->name);
            free_ast(entry->value);
            free(entry);
            entry = next;
        }

        Env *next_env = env->parent;
        free(env);
        env = next_env;
    }
}

void free_env_shallow(Env *env)
{

    while (env)
    {

        fprintf(stderr, "ESTAMOS EN AREA RESTINGIDA900909:\n");
        EnvEntry *entry = env->entries;

        fprintf(stderr, "ESTAMOS EN AREA RESTINGIDA000000000000000:\n");
        while (entry)
        {
            fprintf(stderr, "ESTAMOS EN AREA RESTINGIDA000000000000000:\n");
            EnvEntry *next = entry->next;

            if (entry->name)
            {
                fprintf(stderr, "ESTAMOS EN AREA RESTINGIDA:  %s\n", entry->name);
                free(entry->name);
            }

           free(entry);

            entry = next;
        }

        Env *next_env = env->parent;
        free(env);
        env = next_env;
    }
}

void print_env(Env *env)
{
    Env *a = env;
    int level = 0;

    while (a)
    {
        fprintf(stderr, "=== Env Level %d ===\n", level);

        EnvEntry *entry = a->entries;

        while (entry)
        {
            fprintf(stderr, "  Nombre: %s | Addr: %p | Name Ptr: %p | Value Ptr: %p\n ",
                    entry->name,
                    (void *)entry,
                    (void *)entry->name,
                    (void *)entry->value);
            entry = entry->next;
        }

        a = a->parent;
        level++;
    }
}
