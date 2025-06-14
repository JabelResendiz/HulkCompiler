
// error.c

#include "error.h"

ERROR *add_error_structure(ERROR *e, char *s)
{
    ERROR *error = malloc(sizeof(ERROR));
    error->value = s;
    error->next = e;
    error->index = e ? (e->index + 1) : 1;
    error->len_value = strlen(s);

    return e;
}

ERROR *error_to_string(char **list, int len_list)
{
    ERROR *result = NULL;

    for (int i = 0; i < len_list; i++)
    {
        result = add_error_structure(result, list[i]);
    }

    return result;
}

void print_error_structure(ERROR *e)
{
    // int count_errors= e ?  e->index : 0;

    ERROR *errors = e;

    while (errors)
    {
        printf(RED "!!ERROR SEMANTICO: %d -> %s\n" RESET, e->index, e->value);
        errors = errors->next;
    }

    
    //return count_errors;
}

void add_error(char ***array, int *count, const char *str)
{
    *array = realloc(*array, (*count + 1) * sizeof(char *));
    (*array)[*count] = strdup(str);
    (*count)++;
}
void message_semantic_error(ASTVisitor *v, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char *str = NULL;
    vasprintf(&str, fmt, args);
    va_end(args);
    add_error(&(v->errors), &(v->error_count), str);
}

// void free_semantic_error(char **array, int count)
// {
//     for (int i = 0; i < count; i++)
//     {
//         free(array[i]);
//     }

//     free(array);
// }

void free_semantic_error(ERROR *e)
{
    if(!e) return ;

    free_semantic_error(e->next);

    free(e->value);
    free(e);
}
