
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

%token <node> STRING IDENT
%token <num> NUMBER
%token PRINT IF ELSE
%token GT LT EQ GE LE
%token LET IN CONCAT


%type <node> expr
%type <node> statement statement_list input
%type <node> binding binding_list

%left EQ
%left GT LT GE LE
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
    | expr GT expr    { $$ = create_op_node(AST_GT,  $1, $3); }
    | expr LT expr    { $$ = create_op_node(AST_LT,  $1, $3); }
    | expr EQ expr    { $$ = create_op_node(AST_EQ,  $1, $3); }
    | expr GE expr    { $$ = create_op_node(AST_GE,  $1, $3); }
    | expr LE expr    { $$ = create_op_node(AST_LE,  $1, $3); }
    | '(' expr ')'    { $$ = $2; }
    | NUMBER          { $$ = create_num_node($1); }
    | STRING          { $$ = $1;}
    | IDENT           { $$ = $1;}
    | expr CONCAT expr {$$ = create_concat_node($1,$3);}
    | LET binding_list IN expr   {$$ = create_let_node($2,$4);}
    ;

binding_list:
    binding                     {$$ = $1; }
    | binding_list ',' binding  {$$ = append_binding($1, $3);}
    ;

binding :
    IDENT '=' expr {$$ = create_binding($1-> varname , $3); free($1);}
    ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Syntax error: %s\n", s);
}
