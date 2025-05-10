%code requires {
    #include "ast.h"
}

%{
#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

int yylex();
void yyerror(const char *s);
ASTNode* root;
%}

%union {
    int num;
    ASTNode* node;
}

%token <num> NUMBER
%type <node> expr

%left '+' '-'
%left '*' '/'

%%

input:
    expr { root = $1; }
    ;

expr:
      expr '+' expr   { $$ = create_op_node(AST_ADD, $1, $3); }
    | expr '-' expr   { $$ = create_op_node(AST_SUB, $1, $3); }
    | expr '*' expr   { $$ = create_op_node(AST_MUL, $1, $3); }
    | expr '/' expr   { $$ = create_op_node(AST_DIV, $1, $3); }
    | '(' expr ')'    { $$ = $2; }
    | NUMBER          { $$ = create_num_node($1); }
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}
