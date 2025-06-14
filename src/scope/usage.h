


#ifndef USAGE_H
#define USAGE_H

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



Usage* add_usages(struct ASTNode* node , Usage* list);


#endif