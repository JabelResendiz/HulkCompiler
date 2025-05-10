
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
%token PRINT IF ELSE


%type <node> expr statement statement_list input

%left '+' '-'
%left '*' '/'

%%

input:
    statement_list { root = $1; }
    ;

statement_list:
    statement                    {$$ = $1; }
    | statement_list statement   {$$ = create_seq_node($1,$2); }
    ;

statement:
    PRINT expr ';'               {$$ = create_print_node($2); }
    | IF '(' expr ')' statement ELSE statement  {$$ = create_if_node($3,$5,$7); }
    | expr ';'                   {$$ = $1; }
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
