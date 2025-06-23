

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
%token <val> PI
%token <val> E
%token <var> ID
%token <str> STRING
%token <str> BOOLEAN
%token ERROR LET IN IF ELSE ELIF WHILE
%token LPAREN RPAREN SEMICOLON COMMA LBRACKET RBRACKET COLON EQUALS
%token DESTRUCTOR NEW BASE FUNCTION
%token DOT TYPE INHERITS ARROW

%left IS AS
%left DCONCAT
%left CONCAT
%left AND
%left OR
%left NOT
%left NEQUALS
%left GE GT LE LT EQ
%left PLUS MINUS
%left MULT DIVIDE MOD
%left POWER


%type <node> expr statement let_in_expr block_expr 
%type <node> var conditional elif_part while
%type <node> decl_function call_function destructive_var_decl
%type <node> decl_tpye type_expr type_member member_invocation type_instance member_assignment

%type <arg_list> assignments args args_not_empty
%type <arg_list> param list_params list_params_not_empty
%type <arg_list> type_body block_expr_list 


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
    | decl_function                      {$$ = $1;}
    | conditional                        {$$ = $1;}
    | while                              {$$ = $1;}
    | decl_function SEMICOLON            {$$ = $1;}
    | block_expr                         {$$ = $1;}
    | decl_tpye                          {$$ = $1;}
    | expr SEMICOLON                     {$$ = $1;}
;

expr:
    NUMBER                        {$$ = create_num_node($1);}
    | STRING                      {$$ = create_string_node($1);}
    | BOOLEAN                     {$$ = create_boolean_node($1);}
    | let_in_expr                 {$$ = $1;}
    | call_function               {$$ = $1;}
    | block_expr                  {$$ = $1;}
    | ID                          {$$ = create_var_node($1,"",0);}
    | expr CONCAT expr            {$$ = create_binary_op_node(OP_CONCAT,"@",$1,$3,&TYPE_STRING);}
    | expr DCONCAT expr           {$$ = create_binary_op_node(OP_DCONCAT,"@@",$1,$3,&TYPE_STRING);}
    | expr GE expr                {$$ = create_binary_op_node(OP_GE,">=",$1,$3,&TYPE_BOOLEAN);}
    | expr EQ expr                {$$ = create_binary_op_node(OP_EQ,"==",$1,$3,&TYPE_BOOLEAN);} 
    | expr GT expr                {$$ = create_binary_op_node(OP_GT,">",$1,$3,&TYPE_BOOLEAN);}
    | expr LE expr                {$$ = create_binary_op_node(OP_LE,"<=",$1,$3,&TYPE_BOOLEAN);}
    | expr LT expr                {$$ = create_binary_op_node(OP_LT,"<",$1,$3,&TYPE_BOOLEAN);}
    | expr AND expr               {$$ = create_binary_op_node(OP_AND, "&", $1, $3, &TYPE_BOOLEAN); }
    | expr OR expr                {$$ = create_binary_op_node(OP_OR, "|", $1, $3, &TYPE_BOOLEAN); }
    | expr NEQUALS expr           {$$ = create_binary_op_node(OP_NEQ, "!=", $1, $3, &TYPE_BOOLEAN); }
    | expr PLUS expr              {$$ = create_binary_op_node(OP_ADD,"+",$1,$3,&TYPE_NUM);}
    | expr MINUS expr             {$$ = create_binary_op_node(OP_SUB,"-",$1,$3,&TYPE_NUM);}
    | expr MULT expr              {$$ = create_binary_op_node(OP_MULT,"*",$1,$3,&TYPE_NUM);}
    | expr DIVIDE expr            {$$ = create_binary_op_node(OP_DIV,"/",$1,$3,&TYPE_NUM);}
    | expr MOD expr               {$$ = create_binary_op_node(OP_MOD,"%",$1,$3,&TYPE_NUM);}
    | expr POWER expr             {$$ = create_binary_op_node(OP_POW,"^",$1,$3,&TYPE_NUM);}
    | LPAREN expr RPAREN          {$$ = $2;}
    | destructive_var_decl        {$$ = $1;}
    | conditional                 {$$ = $1;}
    | while                       {$$ = $1;}
    | member_invocation           {$$ = $1;}
    | PI                          {$$ = create_num_node(M_PI);}
    | E                           {$$ = create_num_node(M_E);}
    | member_assignment           {$$ = $1;}
    | type_instance               {$$ = $1;}
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
        $$->args = malloc(sizeof(ASTNode*) * 1);
        $$->args[0] = $1;
        $$->arg_count = 1;
    }
    | var COMMA assignments 
    {
        $$ = malloc(sizeof(*$$));
        $$->args = malloc(sizeof(ASTNode*) * ($3->arg_count + 1));
        $$-> args[0]= $1;
        memcpy($$->args + 1,$3->args,sizeof(ASTNode*) * $3->arg_count);
        $$ ->arg_count = $3->arg_count +1;
        free($3->args);
    }
;

var :
    ID COLON ID EQUALS expr     {$$ = create_assignment_node($1,$5,$3,AST_ASSIGNMENT);}
    | ID EQUALS expr            {$$ = create_assignment_node($1,$3,"",AST_ASSIGNMENT);}
;




call_function:
    ID LPAREN args RPAREN           {$$ = create_call_function_node($1,$3->args,$3->arg_count);}
;

args:
    expr 
    {
        $$ = malloc(sizeof(*$$));
        $$->args = malloc(sizeof(ASTNode*) * 1);
        $$->args[0] = $1;
        $$->arg_count = 1;
    }
    | expr COMMA args_not_empty
    {
        $$ = malloc(sizeof(*$$));
        $$->args = malloc(sizeof(ASTNode*)*($3->arg_count+1));
        $$->args[0]= $1;
        memcpy($$->args + 1,$3->args,sizeof(ASTNode*) * $3->arg_count);
        $$->arg_count = $3->arg_count +1;
        free($3->args);
    }
    | /* empty */
    {
        $$ = malloc(sizeof(*$$));
        $$->args = NULL;
        $$->arg_count = 0;
    }
;

args_not_empty:
    expr 
    {
        $$ = malloc(sizeof(*$$));
        $$->args = malloc(sizeof(ASTNode*) * 1);
        $$->args[0] = $1;
        $$->arg_count = 1;
    }
    | expr COMMA args_not_empty
    {
        $$ = malloc(sizeof(*$$));
        $$->args = malloc(sizeof(ASTNode*)*($3->arg_count+1));
        $$->args[0]= $1;
        memcpy($$->args + 1,$3->args,sizeof(ASTNode*) * $3->arg_count);
        $$->arg_count = $3->arg_count +1;
        free($3->args);
    }
;

decl_function:
    FUNCTION ID LPAREN list_params RPAREN ARROW expr SEMICOLON
    {
        $$ = create_decl_function_node($2,$4->args,$4->arg_count,$7,"");
    }
    | FUNCTION ID LPAREN list_params RPAREN block_expr
    {
        $$ = create_decl_function_node($2,$4->args,$4->arg_count,$6,"");
    }
    | FUNCTION ID LPAREN list_params RPAREN COLON ID ARROW expr SEMICOLON
    {
        $$ = create_decl_function_node($2,$4->args,$4->arg_count,$9,$7);
    }
    | FUNCTION ID LPAREN list_params RPAREN COLON ID block_expr
    {
        $$ = create_decl_function_node($2,$4->args,$4->arg_count,$8,$7);
    }
;

list_params:
    param {
        $$ = malloc(sizeof(*$$));
        $$->args = malloc(sizeof(ASTNode *) * 1);
        $$->args[0] = $1;
        $$->arg_count = 1;
    }
    | param COMMA list_params_not_empty {
        $$ = malloc(sizeof(*$$));
        $$->args = malloc(sizeof(ASTNode *) * ($3->arg_count + 1));
        $$->args[0] = $1;
        memcpy($$->args + 1, $3->args, sizeof(ASTNode *) * $3->arg_count);
        $$->arg_count = $3->arg_count + 1;
        free($3->args);
    }
    | /* empty */ {
        $$ = malloc(sizeof(*$$));
        $$->args = NULL;
        $$->arg_count = 0;
    }
;


param:
    ID                   {$$ = create_var_node($1,"",1);}
    | ID COLON ID        {$$ = create_var_node($1,$3,1);}
;

list_params_not_empty:
    param {
        $$ = malloc(sizeof(*$$));
        $$->args = malloc(sizeof(ASTNode *) * 1);
        $$->args[0] = $1;
        $$->arg_count = 1;
    }
    | param COMMA list_params_not_empty {
        $$ = malloc(sizeof(*$$));
        $$->args = malloc(sizeof(ASTNode *) * ($3->arg_count + 1));
        $$->args[0] = $1;
        memcpy($$->args + 1, $3->args, sizeof(ASTNode *) * $3->arg_count);
        $$->arg_count = $3->arg_count + 1;
        free($3->args);
    }
;


conditional:
    IF LPAREN expr RPAREN expr               {$$= create_conditional_node($3,$5,NULL);}
    | IF LPAREN expr RPAREN expr elif_part   {$$= create_conditional_node($3,$5,$6);}
    | IF LPAREN expr RPAREN expr ELSE expr   {$$= create_conditional_node($3,$5,$7);}
;


elif_part:
    ELIF LPAREN expr RPAREN expr             {$$ = create_conditional_node($3,$5,NULL);}
    | ELIF LPAREN expr RPAREN expr ELSE expr {$$ = create_conditional_node($3,$5,$7);}
    | ELIF LPAREN expr RPAREN expr elif_part {$$ = create_conditional_node($3,$5,$6);}
;
 



while:
    WHILE LPAREN expr RPAREN expr       {$$ = create_while_node($3,$5);}
;




decl_tpye:
    TYPE ID LPAREN list_params RPAREN LBRACKET type_body RBRACKET
    {
        $$ = create_type_node($2,"", $4->args,$4->arg_count,NULL,0,$7->args,$7->arg_count,0);
    }
    | TYPE ID LBRACKET type_body RBRACKET
    {
        $$ = create_type_node($2,"",NULL,0,NULL,0,$4->args,$4->arg_count,0);
    }
    | TYPE ID INHERITS ID LBRACKET type_body RBRACKET
    {
        $$ = create_type_node($2,$4,NULL,0,NULL,0,$6->args,$6->arg_count,0);
    }
    | TYPE ID LPAREN list_params RPAREN INHERITS ID RPAREN args LPAREN LBRACKET type_body RBRACKET
    {
        $$ = create_type_node($2,$7,$4->args,$4->arg_count,$9->args,$9->arg_count,$12->args,$12->arg_count,1);
    }
;

type_body:
    type_expr 
    {
        $$ = malloc(sizeof(*$$));
        $$->args = malloc(sizeof(ASTNode*) *1);
        $$->args[0]= $1;
        $$->arg_count = 1;
    }
    | type_expr type_body
    {
        $$ = malloc(sizeof(*$$));
        $$->args = malloc(sizeof(ASTNode*) * ($2->arg_count+1));
        $$->args[0]= $1;
        memcpy($$->args + 1,$2->args, sizeof(ASTNode*) * $2->arg_count);
        $$->arg_count = $2->arg_count +1;
        free($2->args);
    }
    | /* empty */
    {
        $$ = malloc(sizeof(*$$));
        $$->args = NULL;
        $$->arg_count = 0;

    }
;


type_expr:
    var SEMICOLON           {$$=$1;}
    | type_member           {$$ = $1;}
;

type_member:
    ID LPAREN list_params RPAREN ARROW expr SEMICOLON
    {
        $$ = create_decl_function_node($1,$3->args,$3->arg_count,$6,"");
    }
    | ID LPAREN list_params RPAREN COLON ID ARROW expr SEMICOLON
    {
        $$ = create_decl_function_node($1,$3->args,$3->arg_count,$8,$6);
    }
    | ID LPAREN list_params RPAREN block_expr
    {
        $$ = create_decl_function_node($1,$3->args,$3->arg_count,$5,"");
    }
    | ID LPAREN list_params RPAREN COLON ID block_expr
    {
        $$ = create_decl_function_node($1,$3->args,$3->arg_count,$7,$6);
    }
;


member_invocation:
    expr DOT ID
    {
        ASTNode* attr = create_var_node($3, "",0);
        $$ = create_property_access_node($1,attr);
    }
    | expr DOT call_function
    {
        $$ = create_property_access_node($1,$3);
    }
;

member_assignment:
    expr DOT ID DESTRUCTOR expr           
    {
        $$ = create_property_assignment_node($1,create_var_node($3, "",0),$5);
    }
;

destructive_var_decl:
    /* ID COLON ID DESTRUCTOR expr  { $$ = create_assignment_node($1, $5, $3, NODE_D_ASSIGNMENT); } */
    ID DESTRUCTOR expr
    {
        $$ = create_assignment_node($1,$3,"",AST_DESTRUCTOR);
    }
;


block_expr:
    LBRACKET block_expr_list RBRACKET   {$$ = create_program_node($2->args,$2->arg_count,AST_BLOCK);}
;

type_instance:
    NEW ID LPAREN args RPAREN           { $$ = create_struct_instance_node($2, $4->args, $4->arg_count); }
;


block_expr_list:
    statement {
        $$ = malloc(sizeof(*$$));

        if ($1 == NULL) {
            $$->args = NULL;
            $$->arg_count = 0;
        } else {
            $$->args = malloc(sizeof(ASTNode *) * 1);
            $$->args[0] = $1;
            $$->arg_count = 1;
        }
    }
    | statement block_expr_list {
        $$ = malloc(sizeof(*$$));

        if ($1 == NULL) {
            $$->args = malloc(sizeof(ASTNode *) * ($2->arg_count));
            memcpy($$->args, $2->args, sizeof(ASTNode *) * $2->arg_count);
            $$->arg_count = $2->arg_count;
            free($2->args);
        } else {
            $$->args = malloc(sizeof(ASTNode *) * ($2->arg_count + 1));
            $$->args[0] = $1;
            memcpy($$->args + 1, $2->args, sizeof(ASTNode *) * $2->arg_count);
            $$->arg_count = $2->arg_count + 1;
            free($2->args);
        }
    }

    | /* empty */ {
        $$ = malloc(sizeof(*$$));
        $$->args = NULL;
        $$->arg_count = 0;
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
        case POWER:        return "'^'"      ; case CONCAT:   return "'@'"         ; case PI:         return "'PI'";
        case AND:          return "'&'"      ; case OR:       return "'|'"         ; case NOT:        return "'!'"     ;
        case EQ:           return "'=='"     ; case GE:       return "'>='"        ; case GT:         return "'>'"     ;
        case LE:           return "'<='"     ; case LT:       return "'<'"         ; case ARROW:      return "=>"      ;
        case DESTRUCTOR:    return "':='"     ; case NEQUALS: return "'!='"     ; case E:          return "'E'"; 
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