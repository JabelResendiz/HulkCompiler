

#include "usage.h"
#include <stdlib.h>

// agrega el nodo al usage y enlaza con la que esta
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

