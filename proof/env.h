

// env.h

#ifndef ENV_H
#define ENV_H

#include <stddef.h> // PARA LA  FUTURA TABLA HASH

// #include "ast.h"

struct ASTNode;
typedef struct ASTNode ASTNode;

typedef struct EnvEntry 
{
    // define una variable del entorno y su valor
    char * name;
    ASTNode* value;
    struct EnvEntry* next;
}EnvEntry;


typedef struct Env
{
    // define un entorno de ejecucion
    EnvEntry* entries;
    struct Env* parent;
}Env;

Env* create_env(Env* parent);   
void env_add(Env* env, char* name, ASTNode* value);
ASTNode* env_lookup (Env* env,const char* name);
void free_env(Env* env);
void free_env_shallow(Env* env);
void print_env(Env* env);

#endif