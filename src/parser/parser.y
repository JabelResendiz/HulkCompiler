

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <math.h>
    #include <string.h>
    #include "ast/ast.h"

    int yylex(void);
    int yyparse(void);
    void yyerror(const char *s);

    ASTNode* root;
    int error_count =0 ;
    int max_errors = 1;
    
    #define RED "\x1B[31m"
    #define RESET "x1B[0m"

    const char* token_to_str(int token);

    ASTNode** statement = NULL;

    int statement_count = 0;
    int statement_capacity = 0;

    void add_statement(ASTNode* stmt) {
        if (stmt == NULL)
            return;
        if (statement_count >= statement_capacity) {
            statement_capacity = statement_capacity ? statement_capacity * 2 : 16;
            statement = realloc(statement, sizeof(ASTNode*) * statement_capacity);
        }
        statement[statement_count++] = stmt;
    }
%}


%union
{
    double val;
    char* str;
    char* var;
    struct ASTNode* node;
    struct
    {
        struct ASTNode** args;
        int arg_count;
    } *arg_list;
}


%token <val> NUMBER
%token <var> ID
%token <str> STRING
%token <str> BOOLEAN
%token ERROR LET IN IF ELSE ELIF
%token LPAREN RPAREN SEMICOLON COMMA LBRACKET RBRACKET COLON EQUALS
%token EQUALS
%token DOT

%left CONCAT
%left AND
%left OR
%left NOT
%left GE GT LE LT EQ
%left PLUS MINUS
%left MULT DIVIDE MOD
%left POWER


%type <node> expr statement let_in_expr
%type <node> var


%type <arg_list> assignments args




%% 

program :
    input {
        if(error_count == 0)
        {
            root = create_program_node(statement, statement_count,AST_PROGRAM);
        }    
        else{ root = NULL;}
    }
;


input :
    /* empty */
    | input statement {if ($2 != NULL) add_statement($2);}
    | input error
    {
        if(++error_count >= max_errors)
        {
            YYABORT;
        }

        while(1)
        {
            int tok = yylex();
            if( tok == 0 || tok == SEMICOLON || tok == '\n') break;

        }

        yyerrok;
    }
;


statement:
    SEMICOLON                            {$$ = NULL;}
    | expr SEMICOLON                     {$$ = $1;}
;

expr:
    NUMBER                        {$$ = create_num_node($1);}
    | STRING                      {$$ = create_string_node($1);}
    | BOOLEAN                     {$$ = create_boolean_node($1);}
    | let_in_expr                 {$$ = $1;}
    | ID                          {$$ = create_var_node($1,"");}
    | expr CONCAT expr            {$$ = create_binary_op_node(OP_CONCAT,"@",$1,$3,TYPE_STRING);}
    | expr GE expr                {$$ = create_binary_op_node(OP_GE,">=",$1,$3,TYPE_BOOLEAN);}
    | expr EQ expr                {$$ = create_binary_op_node(OP_EQ,"==",$1,$3,TYPE_BOOLEAN);} 
    | expr GT expr                {$$ = create_binary_op_node(OP_GT,">",$1,$3,TYPE_BOOLEAN);}
    | expr LE expr                {$$ = create_binary_op_node(OP_LE,"<=",$1,$3,TYPE_BOOLEAN);}
    | expr LT expr                {$$ = create_binary_op_node(OP_LT,"<",$1,$3,TYPE_BOOLEAN);}
    | expr PLUS expr              {$$ = create_binary_op_node(OP_ADD,"+",$1,$3,TYPE_NUM);}
    | expr MINUS expr             {$$ = create_binary_op_node(OP_SUB,"-",$1,$3,TYPE_NUM);}
    | expr MULT expr              {$$ = create_binary_op_node(OP_MULT,"*",$1,$3,TYPE_NUM);}
    | expr DIVIDE expr            {$$ = create_binary_op_node(OP_DIV,"/",$1,$3,TYPE_NUM);}
    | expr MOD expr               {$$ = create_binary_op_node(OP_MOD,"%",$1,$3,TYPE_NUM);}
    | expr POWER expr             {$$ = create_binary_op_node(OP_POW,"^",$1,$3,TYPE_NUM);}
    | LPAREN expr RPAREN          {$$ = $2;}
    | ERROR
    {
        yyerrok;
        YYABORT;
    }
;


let_in_expr:
    LET assignments IN expr     {$$ = create_let_in_node($2->args,$2->arg_count,$4);}
;

assignments:
    var
    {
        $$ = malloc(sizeof(*$$));
        $$-> args = malloc(sizeof(ASTNode*) * 1);
        $$-> args[0] = $1;
        $$-> arg_count = 1;
    }
    | var COMMA assignments 
    {
        $$ = malloc(sizeof(*$$));
        $$->args = malloc(sizeof(ASTNode*) * ($3->arg_count + 1));
        $$-> args[0]= $1;
        memcpy($$-> args + 1,$3->args,sizeof(ASTNode*) * $3->arg_count);
        $$ ->arg_count = $3 ->arg_count +1;
        free($3->args);
    }
;

var :
    ID COLON ID EQUALS expr     {$$ = create_assignment_node($1,$5,$3,AST_ASSIGNMENT);}
    | ID EQUALS expr            {$$ = create_assignment_node($1,$3,"",AST_ASSIGNMENT);}
;



args:
    expr 
    {
        $$ = malloc(sizeof(*$$));
        $$->args = malloc(sizeof(ASTNode*) * 1);
        $$-> args[0] = $1;
        $$->arg_count = 1;
    }
;


%%




const char* token_to_str(int token) {
    switch(token) {
        case NUMBER:       return "'number'" ; case ID:       return "'identifier'"; case STRING:     return "'string'";
        case LPAREN:       return "'('"      ; case RPAREN:   return "')'"         ; case COLON:      return "':'"     ;
        case LBRACKET:     return "'{'"      ; case RBRACKET: return "'}'"         ; case EQUALS:     return "'='"     ;
        case SEMICOLON:    return "';'"      ; case PLUS:     return "'+'"         ; case MINUS:      return "'-'"     ;
        case MULT :        return "'*'"      ; case DIVIDE:   return "'/'"         ; case MOD:        return "'%'"     ;
        case POWER:        return "'^'"      ; case CONCAT:   return "'@'"         ;
        case AND:          return "'&'"      ; case OR:       return "'|'"         ; case NOT:        return "'!'"     ;
        case EQ:           return "'=='"     ; case GE:       return "'>='"        ; case GT:         return "'>'"     ;
        case LE:           return "'<='"     ; case LT:       return "'<'"         ; 
        default: return "";
    }
}

void yyerror(const char *s) {
    extern int yychar;
    extern char *yytext;
    
    if (error_count >= max_errors) return;
        
    if (yychar == ERROR) {
        return;
    } else {
        fprintf(stderr, RED"!! SYNTAX ERROR: ");
        
        switch(yychar) {
            case ';' : fprintf(stderr, "Missing expression before ';'"); break;
            case ')' : fprintf(stderr, "Missing expression or parenthesis"); break;
            case '(' : fprintf(stderr, "Missing closing parenthesis"); break;
            default:
                if (!yychar) {
                    fprintf(stderr, "Missing ';' at the end of the statement");
                }
                else {
                    fprintf(stderr, "Unexpected token %s", token_to_str(yychar));
                }
        }

        fprintf(stderr, RED". Line: %d. \n"RESET, line_num);
    }
    
    error_count++;
}