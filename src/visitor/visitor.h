
// visitor.h

#ifndef VISITOR_H
#define VISITOR_H

#include "../ast/ast.h"
#include "../ast/type.h"
#include "../scope/scope.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

// Predeclara Visitor
typedef struct ASTVisitor ASTVisitor;

// --- Funciones de visita agrupadas por tipo ---
typedef struct {
    void (*program)(ASTVisitor*, ASTNode*);
    void (*number)(ASTVisitor*, ASTNode*);
    void (*string)(ASTVisitor*, ASTNode*);
    void (*boolean)(ASTVisitor*, ASTNode*);
    void (*variable)(ASTVisitor*, ASTNode*);
} BasicVisitors;

typedef struct {
    void (*binary)(ASTVisitor*, ASTNode*);
    //void (*unary)(ASTVisitor*, ASTNode*);
    void (*assignment)(ASTVisitor*, ASTNode*);
    void (*call_function)(ASTVisitor*, ASTNode*);
} ExpressionVisitors;

typedef struct {
    void (*block)(ASTVisitor*, ASTNode*);
    //void (*function_dec)(Visitor*, ASTNode*);
    void (*let_in)(ASTVisitor*, ASTNode*);
    void (*conditional)(ASTVisitor*, ASTNode*);
    //void (*loop)(Visitor*, ASTNode*);
} ControlVisitors;

// typedef struct {
//     void (*type_dec)(Visitor*, ASTNode*);
//     void (*type_instance)(Visitor*, ASTNode*);
//     void (*casting)(Visitor*, ASTNode*);
//     void (*test_type)(Visitor*, ASTNode*);
// } TypeVisitors;

// typedef struct {
//     void (*attr_getter)(Visitor*, ASTNode*);
//     void (*attr_setter)(Visitor*, ASTNode*);
//     void (*base_func)(Visitor*, ASTNode*);
// } AttributeVisitors;

// --- Estructura del visitor ---
struct ASTVisitor {
    int error_count;
    char** errors;

    // Contexto
    char* current_function;
    TypeValue* current_type;

    // Visitadores
    BasicVisitors basic;
    ExpressionVisitors expr;
    ControlVisitors control;
    // TypeVisitors types;
    // AttributeVisitors attrs;
};

// --- Funciones de utilidades ---


// Reecibe un nodo y despacha su analisis al metodo del visitante
void accept(ASTVisitor* visitor, ASTNode* node);

// //asigna el contexto y ambito a funciones y tipo dentro del prgorama
// void get_context(ASTVisitor* visitor, ASTNode* node);

// //construye un mensaje de error y lo agrega a la lista de erores del visitor
// void report_error(ASTVisitor* v, const char* fmt, ...);

// //libera la memoria ocuapada por todos los mensjae de error
// void free_error(char** array, int count);


#endif