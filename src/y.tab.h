/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    NUMBER = 258,                  /* NUMBER  */
    PI = 259,                      /* PI  */
    E = 260,                       /* E  */
    ID = 261,                      /* ID  */
    STRING = 262,                  /* STRING  */
    BOOLEAN = 263,                 /* BOOLEAN  */
    ERROR = 264,                   /* ERROR  */
    LET = 265,                     /* LET  */
    IN = 266,                      /* IN  */
    IF = 267,                      /* IF  */
    ELSE = 268,                    /* ELSE  */
    ELIF = 269,                    /* ELIF  */
    WHILE = 270,                   /* WHILE  */
    LPAREN = 271,                  /* LPAREN  */
    RPAREN = 272,                  /* RPAREN  */
    SEMICOLON = 273,               /* SEMICOLON  */
    COMMA = 274,                   /* COMMA  */
    LBRACKET = 275,                /* LBRACKET  */
    RBRACKET = 276,                /* RBRACKET  */
    COLON = 277,                   /* COLON  */
    EQUALS = 278,                  /* EQUALS  */
    DESTRUCTOR = 279,              /* DESTRUCTOR  */
    NEW = 280,                     /* NEW  */
    BASE = 281,                    /* BASE  */
    FUNCTION = 282,                /* FUNCTION  */
    DOT = 283,                     /* DOT  */
    TYPE = 284,                    /* TYPE  */
    INHERITS = 285,                /* INHERITS  */
    ARROW = 286,                   /* ARROW  */
    IS = 287,                      /* IS  */
    AS = 288,                      /* AS  */
    DCONCAT = 289,                 /* DCONCAT  */
    CONCAT = 290,                  /* CONCAT  */
    AND = 291,                     /* AND  */
    OR = 292,                      /* OR  */
    NOT = 293,                     /* NOT  */
    NEQUALS = 294,                 /* NEQUALS  */
    GE = 295,                      /* GE  */
    GT = 296,                      /* GT  */
    LE = 297,                      /* LE  */
    LT = 298,                      /* LT  */
    EQ = 299,                      /* EQ  */
    PLUS = 300,                    /* PLUS  */
    MINUS = 301,                   /* MINUS  */
    MULT = 302,                    /* MULT  */
    DIVIDE = 303,                  /* DIVIDE  */
    MOD = 304,                     /* MOD  */
    POWER = 305                    /* POWER  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif
/* Token kinds.  */
#define YYEMPTY -2
#define YYEOF 0
#define YYerror 256
#define YYUNDEF 257
#define NUMBER 258
#define PI 259
#define E 260
#define ID 261
#define STRING 262
#define BOOLEAN 263
#define ERROR 264
#define LET 265
#define IN 266
#define IF 267
#define ELSE 268
#define ELIF 269
#define WHILE 270
#define LPAREN 271
#define RPAREN 272
#define SEMICOLON 273
#define COMMA 274
#define LBRACKET 275
#define RBRACKET 276
#define COLON 277
#define EQUALS 278
#define DESTRUCTOR 279
#define NEW 280
#define BASE 281
#define FUNCTION 282
#define DOT 283
#define TYPE 284
#define INHERITS 285
#define ARROW 286
#define IS 287
#define AS 288
#define DCONCAT 289
#define CONCAT 290
#define AND 291
#define OR 292
#define NOT 293
#define NEQUALS 294
#define GE 295
#define GT 296
#define LE 297
#define LT 298
#define EQ 299
#define PLUS 300
#define MINUS 301
#define MULT 302
#define DIVIDE 303
#define MOD 304
#define POWER 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 41 "parser/parser.y"

    double val;
    char* str;
    char* var;
    struct ASTNode* node;
    struct
    {
        struct ASTNode** args;
        int arg_count;
    } *arg_list;

#line 179 "y.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
