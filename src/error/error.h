
#ifndef ERROR_H
#define ERROR_H

#include "../visitor/visitor.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>


#define RED     "\x1B[31m"
#define RESET   "\x1B[0m"

typedef struct ERROR
{
    char* value;
    int len_value;
    int index;
    struct ERROR* next;
}ERROR;

// void add_error(ERROR* e);
// void message_semantic_error()

ERROR* add_error_structure(ERROR* e,char *s);
ERROR* error_to_string(char** list, int len_list);
void print_error_structure(ERROR* e);
void add_error(char*** array,int* count,const char* str);
void message_semantic_error(ASTVisitor *v, const char* fmt,...);
void free_semantic_error(ERROR* e);

#endif