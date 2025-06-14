/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "parser/parser.y"

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

#line 107 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
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

#line 272 "y.tab.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_NUMBER = 3,                     /* NUMBER  */
  YYSYMBOL_PI = 4,                         /* PI  */
  YYSYMBOL_E = 5,                          /* E  */
  YYSYMBOL_ID = 6,                         /* ID  */
  YYSYMBOL_STRING = 7,                     /* STRING  */
  YYSYMBOL_BOOLEAN = 8,                    /* BOOLEAN  */
  YYSYMBOL_ERROR = 9,                      /* ERROR  */
  YYSYMBOL_LET = 10,                       /* LET  */
  YYSYMBOL_IN = 11,                        /* IN  */
  YYSYMBOL_IF = 12,                        /* IF  */
  YYSYMBOL_ELSE = 13,                      /* ELSE  */
  YYSYMBOL_ELIF = 14,                      /* ELIF  */
  YYSYMBOL_WHILE = 15,                     /* WHILE  */
  YYSYMBOL_LPAREN = 16,                    /* LPAREN  */
  YYSYMBOL_RPAREN = 17,                    /* RPAREN  */
  YYSYMBOL_SEMICOLON = 18,                 /* SEMICOLON  */
  YYSYMBOL_COMMA = 19,                     /* COMMA  */
  YYSYMBOL_LBRACKET = 20,                  /* LBRACKET  */
  YYSYMBOL_RBRACKET = 21,                  /* RBRACKET  */
  YYSYMBOL_COLON = 22,                     /* COLON  */
  YYSYMBOL_EQUALS = 23,                    /* EQUALS  */
  YYSYMBOL_DESTRUCTOR = 24,                /* DESTRUCTOR  */
  YYSYMBOL_NEW = 25,                       /* NEW  */
  YYSYMBOL_BASE = 26,                      /* BASE  */
  YYSYMBOL_FUNCTION = 27,                  /* FUNCTION  */
  YYSYMBOL_DOT = 28,                       /* DOT  */
  YYSYMBOL_TYPE = 29,                      /* TYPE  */
  YYSYMBOL_INHERITS = 30,                  /* INHERITS  */
  YYSYMBOL_ARROW = 31,                     /* ARROW  */
  YYSYMBOL_IS = 32,                        /* IS  */
  YYSYMBOL_AS = 33,                        /* AS  */
  YYSYMBOL_DCONCAT = 34,                   /* DCONCAT  */
  YYSYMBOL_CONCAT = 35,                    /* CONCAT  */
  YYSYMBOL_AND = 36,                       /* AND  */
  YYSYMBOL_OR = 37,                        /* OR  */
  YYSYMBOL_NOT = 38,                       /* NOT  */
  YYSYMBOL_NEQUALS = 39,                   /* NEQUALS  */
  YYSYMBOL_GE = 40,                        /* GE  */
  YYSYMBOL_GT = 41,                        /* GT  */
  YYSYMBOL_LE = 42,                        /* LE  */
  YYSYMBOL_LT = 43,                        /* LT  */
  YYSYMBOL_EQ = 44,                        /* EQ  */
  YYSYMBOL_PLUS = 45,                      /* PLUS  */
  YYSYMBOL_MINUS = 46,                     /* MINUS  */
  YYSYMBOL_MULT = 47,                      /* MULT  */
  YYSYMBOL_DIVIDE = 48,                    /* DIVIDE  */
  YYSYMBOL_MOD = 49,                       /* MOD  */
  YYSYMBOL_POWER = 50,                     /* POWER  */
  YYSYMBOL_YYACCEPT = 51,                  /* $accept  */
  YYSYMBOL_program = 52,                   /* program  */
  YYSYMBOL_input = 53,                     /* input  */
  YYSYMBOL_statement = 54,                 /* statement  */
  YYSYMBOL_expr = 55,                      /* expr  */
  YYSYMBOL_let_in_expr = 56,               /* let_in_expr  */
  YYSYMBOL_assignments = 57,               /* assignments  */
  YYSYMBOL_var = 58,                       /* var  */
  YYSYMBOL_call_function = 59,             /* call_function  */
  YYSYMBOL_args = 60,                      /* args  */
  YYSYMBOL_args_not_empty = 61,            /* args_not_empty  */
  YYSYMBOL_decl_function = 62,             /* decl_function  */
  YYSYMBOL_list_params = 63,               /* list_params  */
  YYSYMBOL_param = 64,                     /* param  */
  YYSYMBOL_list_params_not_empty = 65,     /* list_params_not_empty  */
  YYSYMBOL_conditional = 66,               /* conditional  */
  YYSYMBOL_elif_part = 67,                 /* elif_part  */
  YYSYMBOL_while = 68,                     /* while  */
  YYSYMBOL_decl_tpye = 69,                 /* decl_tpye  */
  YYSYMBOL_type_body = 70,                 /* type_body  */
  YYSYMBOL_type_expr = 71,                 /* type_expr  */
  YYSYMBOL_type_member = 72,               /* type_member  */
  YYSYMBOL_member_invocation = 73,         /* member_invocation  */
  YYSYMBOL_member_assignment = 74,         /* member_assignment  */
  YYSYMBOL_destructive_var_decl = 75,      /* destructive_var_decl  */
  YYSYMBOL_block_expr = 76,                /* block_expr  */
  YYSYMBOL_type_instance = 77,             /* type_instance  */
  YYSYMBOL_block_expr_list = 78            /* block_expr_list  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  3
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   830

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  51
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  28
/* YYNRULES -- Number of rules.  */
#define YYNRULES  97
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  194

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   305


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    91,    91,   101,   103,   104,   124,   125,   126,   127,
     128,   129,   130,   131,   135,   136,   137,   138,   139,   140,
     141,   142,   143,   144,   145,   146,   147,   148,   149,   150,
     151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
     161,   162,   163,   164,   165,   166,   167,   176,   180,   187,
     199,   200,   207,   211,   218,   228,   236,   243,   255,   259,
     263,   267,   274,   280,   288,   297,   298,   302,   308,   320,
     321,   322,   327,   328,   329,   336,   343,   347,   351,   355,
     362,   369,   379,   389,   390,   394,   398,   402,   406,   414,
     419,   426,   434,   442,   446,   451,   463,   480
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "NUMBER", "PI", "E",
  "ID", "STRING", "BOOLEAN", "ERROR", "LET", "IN", "IF", "ELSE", "ELIF",
  "WHILE", "LPAREN", "RPAREN", "SEMICOLON", "COMMA", "LBRACKET",
  "RBRACKET", "COLON", "EQUALS", "DESTRUCTOR", "NEW", "BASE", "FUNCTION",
  "DOT", "TYPE", "INHERITS", "ARROW", "IS", "AS", "DCONCAT", "CONCAT",
  "AND", "OR", "NOT", "NEQUALS", "GE", "GT", "LE", "LT", "EQ", "PLUS",
  "MINUS", "MULT", "DIVIDE", "MOD", "POWER", "$accept", "program", "input",
  "statement", "expr", "let_in_expr", "assignments", "var",
  "call_function", "args", "args_not_empty", "decl_function",
  "list_params", "param", "list_params_not_empty", "conditional",
  "elif_part", "while", "decl_tpye", "type_body", "type_expr",
  "type_member", "member_invocation", "member_assignment",
  "destructive_var_decl", "block_expr", "type_instance", "block_expr_list", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-123)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-41)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
    -123,    13,   600,  -123,  -123,  -123,  -123,  -123,   103,  -123,
    -123,  -123,     8,     0,     1,   101,  -123,    72,    29,    31,
      33,  -123,   353,  -123,  -123,    24,   596,   619,  -123,  -123,
    -123,  -123,   642,  -123,   101,   101,   -11,    56,    50,   101,
     101,   218,  -123,  -123,  -123,    72,    53,    55,    70,   -12,
    -123,    83,   101,   101,   101,   101,   101,   101,   101,   101,
     101,   101,   101,   101,   101,   101,   101,   101,  -123,   517,
      76,   665,    89,   101,   101,     8,   252,   286,  -123,  -123,
    -123,   101,    94,    94,   119,   127,   104,  -123,   688,   711,
     734,   757,   780,    95,    95,    95,    95,    95,   -25,   -25,
     -22,   -22,   -22,    86,   101,  -123,    75,   665,   665,  -123,
     101,   101,   118,   114,   120,   128,   121,   108,   130,   125,
     119,  -123,   131,   101,   549,  -123,   101,   146,   665,  -123,
     144,    41,    94,    92,    94,  -123,  -123,  -123,   119,   665,
     101,   665,   101,   136,  -123,  -123,   147,   101,  -123,   135,
    -123,   119,   149,   140,   141,  -123,   665,   101,     9,   386,
      94,   143,   151,    63,  -123,   320,   101,  -123,  -123,  -123,
    -123,   101,   160,   101,  -123,   101,   419,   153,    10,   452,
     184,  -123,   150,   101,  -123,  -123,   101,  -123,   119,   485,
     665,   152,  -123,  -123
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     1,     5,    14,    42,    43,    20,    15,
      16,    46,     0,     0,     0,     0,     6,    97,     0,     0,
       0,     4,     0,    17,    18,     7,     8,     9,    12,    41,
      44,    38,    11,    45,    55,     0,     0,     0,    48,     0,
       0,     0,    39,    40,    19,    95,     0,     0,     0,     0,
      13,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    10,    53,
       0,    92,     0,     0,     0,     0,     0,     0,    37,    96,
      93,    55,    64,    64,    82,     0,    89,    90,    22,    21,
      28,    29,    30,    23,    25,    26,    27,    24,    31,    32,
      33,    34,    35,    36,     0,    52,     0,    51,    47,    49,
       0,     0,     0,    65,     0,    62,     0,     0,     0,     0,
      80,    84,     0,     0,    56,    54,     0,    69,    75,    94,
       0,     0,     0,     0,    64,    83,    77,    81,    82,    91,
       0,    50,     0,     0,    70,    66,     0,     0,    59,    67,
      63,    82,     0,     0,     0,    57,    71,     0,     0,     0,
       0,     0,     0,     0,    78,     0,     0,    61,    58,    68,
      76,     0,     0,     0,    87,     0,     0,     0,     0,     0,
      72,    60,     0,     0,    88,    85,     0,    74,    82,     0,
      73,     0,    86,    79
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -123,  -123,  -123,   169,    -8,  -123,    97,    -7,   126,   -80,
      39,  -123,   -74,  -122,    40,    17,     4,    19,  -123,  -118,
    -123,  -123,  -123,  -123,  -123,    -2,  -123,   154
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     1,     2,    45,    22,    23,    37,   118,    24,    70,
     125,    25,   114,   115,   150,    42,   144,    43,    28,   119,
     120,   121,    29,    30,    31,    44,    33,    46
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      32,   112,   137,    51,    83,    38,    51,    41,    84,   116,
     149,    72,    73,     3,    36,    32,    39,    40,    85,    26,
     154,    27,    64,    65,    66,    67,    69,    71,    67,    17,
      17,    76,    77,   161,    26,    47,    27,    48,   149,    49,
     166,   183,    68,    32,    88,    89,    90,    91,    92,    93,
      94,    95,    96,    97,    98,    99,   100,   101,   102,   103,
     153,    17,    26,   146,    27,   107,   108,    74,    38,    75,
     191,    81,   147,    69,    80,     5,     6,     7,     8,     9,
      10,    11,    12,    17,    13,   172,    82,    14,    15,    86,
      16,   177,    17,   105,   173,   106,   124,    18,   126,    19,
     113,    20,   127,   128,     5,     6,     7,     8,     9,    10,
      11,    12,   151,    13,    51,   139,    14,    15,   141,    34,
      34,    17,   152,    51,   134,   117,    18,    35,   123,   148,
      72,    73,   124,   122,   156,   129,   130,   131,   133,   159,
      62,    63,    64,    65,    66,    67,   136,   132,   135,   165,
     145,   138,   157,   158,   160,   162,   167,   163,   176,   142,
     143,   174,   164,    69,   170,   179,   178,   180,   171,   182,
     188,    21,   109,   193,    51,   189,   184,    87,   190,   155,
      52,    53,    54,    55,   187,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,   186,   143,    79,
     169,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    51,     0,     0,     0,     0,     0,    52,    53,
      54,    55,     0,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    78,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    51,     0,     0,     0,
       0,     0,    52,    53,    54,    55,     0,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,   110,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,     0,     0,     0,     0,     0,    52,    53,    54,    55,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,   111,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,     0,     0,     0,     0,     0,
      52,    53,    54,    55,     0,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,   175,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    51,     0,
       0,     0,     0,     0,    52,    53,    54,    55,     0,    56,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    51,     0,     0,     0,     0,     0,    52,    53,    54,
      55,     0,    56,    57,    58,    59,    60,    61,    62,    63,
      64,    65,    66,    67,   168,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    51,     0,     0,     0,     0,     0,
      52,    53,    54,    55,     0,    56,    57,    58,    59,    60,
      61,    62,    63,    64,    65,    66,    67,   181,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    51,     0,     0,
       0,     0,     0,    52,    53,    54,    55,     0,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
     185,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,     0,     0,     0,     0,     0,    52,    53,    54,    55,
       0,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,   192,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    51,     0,     0,     0,     0,     0,    52,
      53,    54,    55,     0,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,   104,     0,     0,     0,
       0,     0,     0,     0,     0,    51,     0,     0,     0,     0,
       0,    52,    53,    54,    55,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,   140,     0,
       0,     0,     0,     0,     0,     0,     0,    51,     0,     0,
       0,     0,     0,    52,    53,    54,    55,     0,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
      -2,     4,     0,     5,     6,     7,     8,     9,    10,    11,
      12,     0,    13,     0,     0,    14,    15,     0,    16,     0,
      17,     0,     0,     0,   -39,    18,     0,    19,     0,    20,
     -39,   -39,   -39,   -39,     0,   -39,   -39,   -39,   -39,   -39,
     -39,   -39,   -39,   -39,   -39,   -39,   -39,   -40,     0,     0,
       0,     0,     0,   -40,   -40,   -40,   -40,     0,   -40,   -40,
     -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,   -40,
     -19,     0,     0,     0,     0,     0,   -19,   -19,   -19,   -19,
       0,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,   -19,
     -19,   -19,   -19,    51,     0,     0,     0,     0,     0,    52,
      53,    54,    55,     0,    56,    57,    58,    59,    60,    61,
      62,    63,    64,    65,    66,    67,    51,     0,     0,     0,
       0,     0,     0,    53,    54,    55,     0,    56,    57,    58,
      59,    60,    61,    62,    63,    64,    65,    66,    67,    51,
       0,     0,     0,     0,     0,     0,     0,    54,    55,     0,
      56,    57,    58,    59,    60,    61,    62,    63,    64,    65,
      66,    67,    51,     0,     0,     0,     0,     0,     0,     0,
       0,    55,     0,    56,    57,    58,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    51,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    56,    57,    58,    59,
      60,    61,    62,    63,    64,    65,    66,    67,    51,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
      67
};

static const yytype_int16 yycheck[] =
{
       2,    81,   120,    28,    16,    12,    28,    15,    20,    83,
     132,    22,    23,     0,     6,    17,    16,    16,    30,     2,
     138,     2,    47,    48,    49,    50,    34,    35,    50,    20,
      20,    39,    40,   151,    17,     6,    17,     6,   160,     6,
      31,    31,    18,    45,    52,    53,    54,    55,    56,    57,
      58,    59,    60,    61,    62,    63,    64,    65,    66,    67,
     134,    20,    45,    22,    45,    73,    74,    11,    75,    19,
     188,    16,    31,    81,    21,     3,     4,     5,     6,     7,
       8,     9,    10,    20,    12,    22,    16,    15,    16,     6,
      18,   171,    20,    17,    31,     6,   104,    25,    23,    27,
       6,    29,   110,   111,     3,     4,     5,     6,     7,     8,
       9,    10,    20,    12,    28,   123,    15,    16,   126,    16,
      16,    20,    30,    28,    16,     6,    25,    24,    24,   131,
      22,    23,   140,     6,   142,    17,    22,    17,    17,   147,
      45,    46,    47,    48,    49,    50,    21,    19,    18,   157,
       6,    20,    16,     6,    19,     6,   158,    17,   166,    13,
      14,   163,    21,   171,    21,   173,     6,   175,    17,    16,
      20,     2,    75,    21,    28,   183,   178,    51,   186,   140,
      34,    35,    36,    37,   180,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    13,    14,    45,
     160,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    35,
      36,    37,    -1,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    17,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,
      -1,    -1,    34,    35,    36,    37,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    17,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    17,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    -1,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    17,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,
      -1,    -1,    -1,    -1,    34,    35,    36,    37,    -1,    39,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50,    18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    28,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    -1,    39,    40,    41,    42,    43,    44,    45,    46,
      47,    48,    49,    50,    18,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    -1,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    18,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      18,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      28,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    18,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    -1,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    19,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,    -1,    -1,
      -1,    34,    35,    36,    37,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    19,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    28,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
       0,     1,    -1,     3,     4,     5,     6,     7,     8,     9,
      10,    -1,    12,    -1,    -1,    15,    16,    -1,    18,    -1,
      20,    -1,    -1,    -1,    28,    25,    -1,    27,    -1,    29,
      34,    35,    36,    37,    -1,    39,    40,    41,    42,    43,
      44,    45,    46,    47,    48,    49,    50,    28,    -1,    -1,
      -1,    -1,    -1,    34,    35,    36,    37,    -1,    39,    40,
      41,    42,    43,    44,    45,    46,    47,    48,    49,    50,
      28,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      -1,    39,    40,    41,    42,    43,    44,    45,    46,    47,
      48,    49,    50,    28,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    -1,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    28,    -1,    -1,    -1,
      -1,    -1,    -1,    35,    36,    37,    -1,    39,    40,    41,
      42,    43,    44,    45,    46,    47,    48,    49,    50,    28,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    36,    37,    -1,
      39,    40,    41,    42,    43,    44,    45,    46,    47,    48,
      49,    50,    28,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    -1,    39,    40,    41,    42,    43,    44,    45,
      46,    47,    48,    49,    50,    28,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    28,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      40,    41,    42,    43,    44,    45,    46,    47,    48,    49,
      50
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    52,    53,     0,     1,     3,     4,     5,     6,     7,
       8,     9,    10,    12,    15,    16,    18,    20,    25,    27,
      29,    54,    55,    56,    59,    62,    66,    68,    69,    73,
      74,    75,    76,    77,    16,    24,     6,    57,    58,    16,
      16,    55,    66,    68,    76,    54,    78,     6,     6,     6,
      18,    28,    34,    35,    36,    37,    39,    40,    41,    42,
      43,    44,    45,    46,    47,    48,    49,    50,    18,    55,
      60,    55,    22,    23,    11,    19,    55,    55,    17,    78,
      21,    16,    16,    16,    20,    30,     6,    59,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    19,    17,     6,    55,    55,    57,
      17,    17,    60,     6,    63,    64,    63,     6,    58,    70,
      71,    72,     6,    24,    55,    61,    23,    55,    55,    17,
      22,    17,    19,    17,    16,    18,    21,    70,    20,    55,
      19,    55,    13,    14,    67,     6,    22,    31,    76,    64,
      65,    20,    30,    63,    70,    61,    55,    16,     6,    55,
      19,    70,     6,    17,    21,    55,    31,    76,    18,    65,
      21,    17,    22,    31,    76,    17,    55,    60,     6,    55,
      55,    18,    16,    31,    76,    18,    13,    67,    20,    55,
      55,    70,    18,    21
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    51,    52,    53,    53,    53,    54,    54,    54,    54,
      54,    54,    54,    54,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    55,    55,    55,
      55,    55,    55,    55,    55,    55,    55,    56,    57,    57,
      58,    58,    59,    60,    60,    60,    61,    61,    62,    62,
      62,    62,    63,    63,    63,    64,    64,    65,    65,    66,
      66,    66,    67,    67,    67,    68,    69,    69,    69,    69,
      70,    70,    70,    71,    71,    72,    72,    72,    72,    73,
      73,    74,    75,    76,    77,    78,    78,    78
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     0,     2,     2,     1,     1,     1,     1,
       2,     1,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     1,     1,     1,     4,     1,     3,
       5,     3,     4,     1,     3,     0,     1,     3,     8,     6,
      10,     8,     1,     3,     0,     1,     3,     1,     3,     5,
       6,     7,     5,     7,     6,     5,     8,     5,     7,    13,
       1,     2,     0,     2,     1,     7,     9,     5,     7,     3,
       3,     5,     3,     3,     5,     1,     2,     0
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* program: input  */
#line 91 "parser/parser.y"
          {
        if(error_count == 0)
        {
            root = create_program_node(statement, statement_count,AST_PROGRAM);
        }    
        else{ root = NULL;}
    }
#line 1591 "y.tab.c"
    break;

  case 4: /* input: input statement  */
#line 103 "parser/parser.y"
                      {if ((yyvsp[0].node) != NULL) add_statement((yyvsp[0].node));}
#line 1597 "y.tab.c"
    break;

  case 5: /* input: input error  */
#line 105 "parser/parser.y"
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
#line 1617 "y.tab.c"
    break;

  case 6: /* statement: SEMICOLON  */
#line 124 "parser/parser.y"
                                         {(yyval.node) = NULL;}
#line 1623 "y.tab.c"
    break;

  case 7: /* statement: decl_function  */
#line 125 "parser/parser.y"
                                         {(yyval.node) = (yyvsp[0].node);}
#line 1629 "y.tab.c"
    break;

  case 8: /* statement: conditional  */
#line 126 "parser/parser.y"
                                         {(yyval.node) = (yyvsp[0].node);}
#line 1635 "y.tab.c"
    break;

  case 9: /* statement: while  */
#line 127 "parser/parser.y"
                                         {(yyval.node) = (yyvsp[0].node);}
#line 1641 "y.tab.c"
    break;

  case 10: /* statement: decl_function SEMICOLON  */
#line 128 "parser/parser.y"
                                         {(yyval.node) = (yyvsp[-1].node);}
#line 1647 "y.tab.c"
    break;

  case 11: /* statement: block_expr  */
#line 129 "parser/parser.y"
                                         {(yyval.node) = (yyvsp[0].node);}
#line 1653 "y.tab.c"
    break;

  case 12: /* statement: decl_tpye  */
#line 130 "parser/parser.y"
                                         {(yyval.node) = (yyvsp[0].node);}
#line 1659 "y.tab.c"
    break;

  case 13: /* statement: expr SEMICOLON  */
#line 131 "parser/parser.y"
                                         {(yyval.node) = (yyvsp[-1].node);}
#line 1665 "y.tab.c"
    break;

  case 14: /* expr: NUMBER  */
#line 135 "parser/parser.y"
                                  {(yyval.node) = create_num_node((yyvsp[0].val));}
#line 1671 "y.tab.c"
    break;

  case 15: /* expr: STRING  */
#line 136 "parser/parser.y"
                                  {(yyval.node) = create_string_node((yyvsp[0].str));}
#line 1677 "y.tab.c"
    break;

  case 16: /* expr: BOOLEAN  */
#line 137 "parser/parser.y"
                                  {(yyval.node) = create_boolean_node((yyvsp[0].str));}
#line 1683 "y.tab.c"
    break;

  case 17: /* expr: let_in_expr  */
#line 138 "parser/parser.y"
                                  {(yyval.node) = (yyvsp[0].node);}
#line 1689 "y.tab.c"
    break;

  case 18: /* expr: call_function  */
#line 139 "parser/parser.y"
                                  {(yyval.node) = (yyvsp[0].node);}
#line 1695 "y.tab.c"
    break;

  case 19: /* expr: block_expr  */
#line 140 "parser/parser.y"
                                  {(yyval.node) = (yyvsp[0].node);}
#line 1701 "y.tab.c"
    break;

  case 20: /* expr: ID  */
#line 141 "parser/parser.y"
                                  {(yyval.node) = create_var_node((yyvsp[0].var),"",0);}
#line 1707 "y.tab.c"
    break;

  case 21: /* expr: expr CONCAT expr  */
#line 142 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_CONCAT,"@",(yyvsp[-2].node),(yyvsp[0].node),&TYPE_STRING);}
#line 1713 "y.tab.c"
    break;

  case 22: /* expr: expr DCONCAT expr  */
#line 143 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_DCONCAT,"@@",(yyvsp[-2].node),(yyvsp[0].node),&TYPE_STRING);}
#line 1719 "y.tab.c"
    break;

  case 23: /* expr: expr GE expr  */
#line 144 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_GE,">=",(yyvsp[-2].node),(yyvsp[0].node),&TYPE_BOOLEAN);}
#line 1725 "y.tab.c"
    break;

  case 24: /* expr: expr EQ expr  */
#line 145 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_EQ,"==",(yyvsp[-2].node),(yyvsp[0].node),&TYPE_BOOLEAN);}
#line 1731 "y.tab.c"
    break;

  case 25: /* expr: expr GT expr  */
#line 146 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_GT,">",(yyvsp[-2].node),(yyvsp[0].node),&TYPE_BOOLEAN);}
#line 1737 "y.tab.c"
    break;

  case 26: /* expr: expr LE expr  */
#line 147 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_LE,"<=",(yyvsp[-2].node),(yyvsp[0].node),&TYPE_BOOLEAN);}
#line 1743 "y.tab.c"
    break;

  case 27: /* expr: expr LT expr  */
#line 148 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_LT,"<",(yyvsp[-2].node),(yyvsp[0].node),&TYPE_BOOLEAN);}
#line 1749 "y.tab.c"
    break;

  case 28: /* expr: expr AND expr  */
#line 149 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_AND, "&", (yyvsp[-2].node), (yyvsp[0].node), &TYPE_BOOLEAN); }
#line 1755 "y.tab.c"
    break;

  case 29: /* expr: expr OR expr  */
#line 150 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_OR, "|", (yyvsp[-2].node), (yyvsp[0].node), &TYPE_BOOLEAN); }
#line 1761 "y.tab.c"
    break;

  case 30: /* expr: expr NEQUALS expr  */
#line 151 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_NEQ, "!=", (yyvsp[-2].node), (yyvsp[0].node), &TYPE_BOOLEAN); }
#line 1767 "y.tab.c"
    break;

  case 31: /* expr: expr PLUS expr  */
#line 152 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_ADD,"+",(yyvsp[-2].node),(yyvsp[0].node),&TYPE_NUM);}
#line 1773 "y.tab.c"
    break;

  case 32: /* expr: expr MINUS expr  */
#line 153 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_SUB,"-",(yyvsp[-2].node),(yyvsp[0].node),&TYPE_NUM);}
#line 1779 "y.tab.c"
    break;

  case 33: /* expr: expr MULT expr  */
#line 154 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_MULT,"*",(yyvsp[-2].node),(yyvsp[0].node),&TYPE_NUM);}
#line 1785 "y.tab.c"
    break;

  case 34: /* expr: expr DIVIDE expr  */
#line 155 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_DIV,"/",(yyvsp[-2].node),(yyvsp[0].node),&TYPE_NUM);}
#line 1791 "y.tab.c"
    break;

  case 35: /* expr: expr MOD expr  */
#line 156 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_MOD,"%",(yyvsp[-2].node),(yyvsp[0].node),&TYPE_NUM);}
#line 1797 "y.tab.c"
    break;

  case 36: /* expr: expr POWER expr  */
#line 157 "parser/parser.y"
                                  {(yyval.node) = create_binary_op_node(OP_POW,"^",(yyvsp[-2].node),(yyvsp[0].node),&TYPE_NUM);}
#line 1803 "y.tab.c"
    break;

  case 37: /* expr: LPAREN expr RPAREN  */
#line 158 "parser/parser.y"
                                  {(yyval.node) = (yyvsp[-1].node);}
#line 1809 "y.tab.c"
    break;

  case 38: /* expr: destructive_var_decl  */
#line 159 "parser/parser.y"
                                  {(yyval.node) = (yyvsp[0].node);}
#line 1815 "y.tab.c"
    break;

  case 39: /* expr: conditional  */
#line 160 "parser/parser.y"
                                  {(yyval.node) = (yyvsp[0].node);}
#line 1821 "y.tab.c"
    break;

  case 40: /* expr: while  */
#line 161 "parser/parser.y"
                                  {(yyval.node) = (yyvsp[0].node);}
#line 1827 "y.tab.c"
    break;

  case 41: /* expr: member_invocation  */
#line 162 "parser/parser.y"
                                  {(yyval.node) = (yyvsp[0].node);}
#line 1833 "y.tab.c"
    break;

  case 42: /* expr: PI  */
#line 163 "parser/parser.y"
                                  {(yyval.node) = create_num_node(M_PI);}
#line 1839 "y.tab.c"
    break;

  case 43: /* expr: E  */
#line 164 "parser/parser.y"
                                  {(yyval.node) = create_num_node(M_E);}
#line 1845 "y.tab.c"
    break;

  case 44: /* expr: member_assignment  */
#line 165 "parser/parser.y"
                                  {(yyval.node) = (yyvsp[0].node);}
#line 1851 "y.tab.c"
    break;

  case 45: /* expr: type_instance  */
#line 166 "parser/parser.y"
                                  {(yyval.node) = (yyvsp[0].node);}
#line 1857 "y.tab.c"
    break;

  case 46: /* expr: ERROR  */
#line 168 "parser/parser.y"
    {
        yyerrok;
        YYABORT;
    }
#line 1866 "y.tab.c"
    break;

  case 47: /* let_in_expr: LET assignments IN expr  */
#line 176 "parser/parser.y"
                                {(yyval.node) = create_let_in_node((yyvsp[-2].arg_list)->args,(yyvsp[-2].arg_list)->arg_count,(yyvsp[0].node));}
#line 1872 "y.tab.c"
    break;

  case 48: /* assignments: var  */
#line 181 "parser/parser.y"
    {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = malloc(sizeof(ASTNode*) * 1);
        (yyval.arg_list)->args[0] = (yyvsp[0].node);
        (yyval.arg_list)->arg_count = 1;
    }
#line 1883 "y.tab.c"
    break;

  case 49: /* assignments: var COMMA assignments  */
#line 188 "parser/parser.y"
    {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = malloc(sizeof(ASTNode*) * ((yyvsp[0].arg_list)->arg_count + 1));
        (yyval.arg_list)-> args[0]= (yyvsp[-2].node);
        memcpy((yyval.arg_list)->args + 1,(yyvsp[0].arg_list)->args,sizeof(ASTNode*) * (yyvsp[0].arg_list)->arg_count);
        (yyval.arg_list) ->arg_count = (yyvsp[0].arg_list)->arg_count +1;
        free((yyvsp[0].arg_list)->args);
    }
#line 1896 "y.tab.c"
    break;

  case 50: /* var: ID COLON ID EQUALS expr  */
#line 199 "parser/parser.y"
                                {(yyval.node) = create_assignment_node((yyvsp[-4].var),(yyvsp[0].node),(yyvsp[-2].var),AST_ASSIGNMENT);}
#line 1902 "y.tab.c"
    break;

  case 51: /* var: ID EQUALS expr  */
#line 200 "parser/parser.y"
                                {(yyval.node) = create_assignment_node((yyvsp[-2].var),(yyvsp[0].node),"",AST_ASSIGNMENT);}
#line 1908 "y.tab.c"
    break;

  case 52: /* call_function: ID LPAREN args RPAREN  */
#line 207 "parser/parser.y"
                                    {(yyval.node) = create_call_function_node((yyvsp[-3].var),(yyvsp[-1].arg_list)->args,(yyvsp[-1].arg_list)->arg_count);}
#line 1914 "y.tab.c"
    break;

  case 53: /* args: expr  */
#line 212 "parser/parser.y"
    {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = malloc(sizeof(ASTNode*) * 1);
        (yyval.arg_list)->args[0] = (yyvsp[0].node);
        (yyval.arg_list)->arg_count = 1;
    }
#line 1925 "y.tab.c"
    break;

  case 54: /* args: expr COMMA args_not_empty  */
#line 219 "parser/parser.y"
    {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = malloc(sizeof(ASTNode*)*((yyvsp[0].arg_list)->arg_count+1));
        (yyval.arg_list)->args[0]= (yyvsp[-2].node);
        memcpy((yyval.arg_list)->args + 1,(yyvsp[0].arg_list)->args,sizeof(ASTNode*) * (yyvsp[0].arg_list)->arg_count);
        (yyval.arg_list)->arg_count = (yyvsp[0].arg_list)->arg_count +1;
        free((yyvsp[0].arg_list)->args);
    }
#line 1938 "y.tab.c"
    break;

  case 55: /* args: %empty  */
#line 228 "parser/parser.y"
    {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = NULL;
        (yyval.arg_list)->arg_count = 0;
    }
#line 1948 "y.tab.c"
    break;

  case 56: /* args_not_empty: expr  */
#line 237 "parser/parser.y"
    {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = malloc(sizeof(ASTNode*) * 1);
        (yyval.arg_list)->args[0] = (yyvsp[0].node);
        (yyval.arg_list)->arg_count = 1;
    }
#line 1959 "y.tab.c"
    break;

  case 57: /* args_not_empty: expr COMMA args_not_empty  */
#line 244 "parser/parser.y"
    {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = malloc(sizeof(ASTNode*)*((yyvsp[0].arg_list)->arg_count+1));
        (yyval.arg_list)->args[0]= (yyvsp[-2].node);
        memcpy((yyval.arg_list)->args + 1,(yyvsp[0].arg_list)->args,sizeof(ASTNode*) * (yyvsp[0].arg_list)->arg_count);
        (yyval.arg_list)->arg_count = (yyvsp[0].arg_list)->arg_count +1;
        free((yyvsp[0].arg_list)->args);
    }
#line 1972 "y.tab.c"
    break;

  case 58: /* decl_function: FUNCTION ID LPAREN list_params RPAREN ARROW expr SEMICOLON  */
#line 256 "parser/parser.y"
    {
        (yyval.node) = create_decl_function_node((yyvsp[-6].var),(yyvsp[-4].arg_list)->args,(yyvsp[-4].arg_list)->arg_count,(yyvsp[-1].node),"");
    }
#line 1980 "y.tab.c"
    break;

  case 59: /* decl_function: FUNCTION ID LPAREN list_params RPAREN block_expr  */
#line 260 "parser/parser.y"
    {
        (yyval.node) = create_decl_function_node((yyvsp[-4].var),(yyvsp[-2].arg_list)->args,(yyvsp[-2].arg_list)->arg_count,(yyvsp[0].node),"");
    }
#line 1988 "y.tab.c"
    break;

  case 60: /* decl_function: FUNCTION ID LPAREN list_params RPAREN COLON ID ARROW expr SEMICOLON  */
#line 264 "parser/parser.y"
    {
        (yyval.node) = create_decl_function_node((yyvsp[-8].var),(yyvsp[-6].arg_list)->args,(yyvsp[-6].arg_list)->arg_count,(yyvsp[-1].node),(yyvsp[-3].var));
    }
#line 1996 "y.tab.c"
    break;

  case 61: /* decl_function: FUNCTION ID LPAREN list_params RPAREN COLON ID block_expr  */
#line 268 "parser/parser.y"
    {
        (yyval.node) = create_decl_function_node((yyvsp[-6].var),(yyvsp[-4].arg_list)->args,(yyvsp[-4].arg_list)->arg_count,(yyvsp[0].node),(yyvsp[-1].var));
    }
#line 2004 "y.tab.c"
    break;

  case 62: /* list_params: param  */
#line 274 "parser/parser.y"
          {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = malloc(sizeof(ASTNode *) * 1);
        (yyval.arg_list)->args[0] = (yyvsp[0].arg_list);
        (yyval.arg_list)->arg_count = 1;
    }
#line 2015 "y.tab.c"
    break;

  case 63: /* list_params: param COMMA list_params_not_empty  */
#line 280 "parser/parser.y"
                                        {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = malloc(sizeof(ASTNode *) * ((yyvsp[0].arg_list)->arg_count + 1));
        (yyval.arg_list)->args[0] = (yyvsp[-2].arg_list);
        memcpy((yyval.arg_list)->args + 1, (yyvsp[0].arg_list)->args, sizeof(ASTNode *) * (yyvsp[0].arg_list)->arg_count);
        (yyval.arg_list)->arg_count = (yyvsp[0].arg_list)->arg_count + 1;
        free((yyvsp[0].arg_list)->args);
    }
#line 2028 "y.tab.c"
    break;

  case 64: /* list_params: %empty  */
#line 288 "parser/parser.y"
                  {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = NULL;
        (yyval.arg_list)->arg_count = 0;
    }
#line 2038 "y.tab.c"
    break;

  case 65: /* param: ID  */
#line 297 "parser/parser.y"
                         {(yyval.arg_list) = create_var_node((yyvsp[0].var),"",1);}
#line 2044 "y.tab.c"
    break;

  case 66: /* param: ID COLON ID  */
#line 298 "parser/parser.y"
                         {(yyval.arg_list) = create_var_node((yyvsp[-2].var),(yyvsp[0].var),1);}
#line 2050 "y.tab.c"
    break;

  case 67: /* list_params_not_empty: param  */
#line 302 "parser/parser.y"
          {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = malloc(sizeof(ASTNode *) * 1);
        (yyval.arg_list)->args[0] = (yyvsp[0].arg_list);
        (yyval.arg_list)->arg_count = 1;
    }
#line 2061 "y.tab.c"
    break;

  case 68: /* list_params_not_empty: param COMMA list_params_not_empty  */
#line 308 "parser/parser.y"
                                        {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = malloc(sizeof(ASTNode *) * ((yyvsp[0].arg_list)->arg_count + 1));
        (yyval.arg_list)->args[0] = (yyvsp[-2].arg_list);
        memcpy((yyval.arg_list)->args + 1, (yyvsp[0].arg_list)->args, sizeof(ASTNode *) * (yyvsp[0].arg_list)->arg_count);
        (yyval.arg_list)->arg_count = (yyvsp[0].arg_list)->arg_count + 1;
        free((yyvsp[0].arg_list)->args);
    }
#line 2074 "y.tab.c"
    break;

  case 69: /* conditional: IF LPAREN expr RPAREN expr  */
#line 320 "parser/parser.y"
                                             {(yyval.node)= create_conditional_node((yyvsp[-2].node),(yyvsp[0].node),NULL);}
#line 2080 "y.tab.c"
    break;

  case 70: /* conditional: IF LPAREN expr RPAREN expr elif_part  */
#line 321 "parser/parser.y"
                                             {(yyval.node)= create_conditional_node((yyvsp[-3].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 2086 "y.tab.c"
    break;

  case 71: /* conditional: IF LPAREN expr RPAREN expr ELSE expr  */
#line 322 "parser/parser.y"
                                             {(yyval.node)= create_conditional_node((yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].node));}
#line 2092 "y.tab.c"
    break;

  case 72: /* elif_part: ELIF LPAREN expr RPAREN expr  */
#line 327 "parser/parser.y"
                                             {(yyval.node) = create_conditional_node((yyvsp[-2].node),(yyvsp[0].node),NULL);}
#line 2098 "y.tab.c"
    break;

  case 73: /* elif_part: ELIF LPAREN expr RPAREN expr ELSE expr  */
#line 328 "parser/parser.y"
                                             {(yyval.node) = create_conditional_node((yyvsp[-4].node),(yyvsp[-2].node),(yyvsp[0].node));}
#line 2104 "y.tab.c"
    break;

  case 74: /* elif_part: ELIF LPAREN expr RPAREN expr elif_part  */
#line 329 "parser/parser.y"
                                             {(yyval.node) = create_conditional_node((yyvsp[-3].node),(yyvsp[-1].node),(yyvsp[0].node));}
#line 2110 "y.tab.c"
    break;

  case 75: /* while: WHILE LPAREN expr RPAREN expr  */
#line 336 "parser/parser.y"
                                        {(yyval.node) = create_while_node((yyvsp[-2].node),(yyvsp[0].node));}
#line 2116 "y.tab.c"
    break;

  case 76: /* decl_tpye: TYPE ID LPAREN list_params RPAREN LBRACKET type_body RBRACKET  */
#line 344 "parser/parser.y"
    {
        (yyval.node) = create_type_node((yyvsp[-6].var),"", (yyvsp[-4].arg_list)->args,(yyvsp[-4].arg_list)->arg_count,NULL,0,(yyvsp[-1].arg_list)->args,(yyvsp[-1].arg_list)->arg_count);
    }
#line 2124 "y.tab.c"
    break;

  case 77: /* decl_tpye: TYPE ID LBRACKET type_body RBRACKET  */
#line 348 "parser/parser.y"
    {
        (yyval.node) = create_type_node((yyvsp[-3].var),"",NULL,0,NULL,0,(yyvsp[-1].arg_list)->args,(yyvsp[-1].arg_list)->arg_count);
    }
#line 2132 "y.tab.c"
    break;

  case 78: /* decl_tpye: TYPE ID INHERITS ID LBRACKET type_body RBRACKET  */
#line 352 "parser/parser.y"
    {
        (yyval.node) = create_type_node((yyvsp[-5].var),(yyvsp[-3].var),NULL,0,NULL,0,(yyvsp[-1].arg_list)->args,(yyvsp[-1].arg_list)->arg_count);
    }
#line 2140 "y.tab.c"
    break;

  case 79: /* decl_tpye: TYPE ID LPAREN list_params RPAREN INHERITS ID RPAREN args LPAREN LBRACKET type_body RBRACKET  */
#line 356 "parser/parser.y"
    {
        (yyval.node) = create_type_node((yyvsp[-11].var),(yyvsp[-6].var),(yyvsp[-9].arg_list)->args,(yyvsp[-9].arg_list)->arg_count,(yyvsp[-4].arg_list)->args,(yyvsp[-4].arg_list)->arg_count,(yyvsp[-1].arg_list)->args,(yyvsp[-1].arg_list)->arg_count);
    }
#line 2148 "y.tab.c"
    break;

  case 80: /* type_body: type_expr  */
#line 363 "parser/parser.y"
    {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = malloc(sizeof(ASTNode*) *1);
        (yyval.arg_list)->args[0]= (yyvsp[0].node);
        (yyval.arg_list)->arg_count = 1;
    }
#line 2159 "y.tab.c"
    break;

  case 81: /* type_body: type_expr type_body  */
#line 370 "parser/parser.y"
    {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = malloc(sizeof(ASTNode*) * ((yyvsp[0].arg_list)->arg_count+1));
        (yyval.arg_list)->args[0]= (yyvsp[-1].node);
        memcpy((yyval.arg_list)->args + 1,(yyvsp[0].arg_list)->args, sizeof(ASTNode*) * (yyvsp[0].arg_list)->arg_count);
        (yyval.arg_list)->arg_count = (yyvsp[0].arg_list)->arg_count +1;
        free((yyvsp[0].arg_list)->args);
    }
#line 2172 "y.tab.c"
    break;

  case 82: /* type_body: %empty  */
#line 379 "parser/parser.y"
    {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = NULL;
        (yyval.arg_list)->arg_count = 0;

    }
#line 2183 "y.tab.c"
    break;

  case 83: /* type_expr: var SEMICOLON  */
#line 389 "parser/parser.y"
                            {(yyval.node)=(yyvsp[-1].node);}
#line 2189 "y.tab.c"
    break;

  case 84: /* type_expr: type_member  */
#line 390 "parser/parser.y"
                            {(yyval.node) = (yyvsp[0].node);}
#line 2195 "y.tab.c"
    break;

  case 85: /* type_member: ID LPAREN list_params RPAREN ARROW expr SEMICOLON  */
#line 395 "parser/parser.y"
    {
        (yyval.node) = create_decl_function_node((yyvsp[-6].var),(yyvsp[-4].arg_list)->args,(yyvsp[-4].arg_list)->arg_count,(yyvsp[-1].node),"");
    }
#line 2203 "y.tab.c"
    break;

  case 86: /* type_member: ID LPAREN list_params RPAREN COLON ID ARROW expr SEMICOLON  */
#line 399 "parser/parser.y"
    {
        (yyval.node) = create_decl_function_node((yyvsp[-8].var),(yyvsp[-6].arg_list)->args,(yyvsp[-6].arg_list)->arg_count,(yyvsp[-1].node),(yyvsp[-3].var));
    }
#line 2211 "y.tab.c"
    break;

  case 87: /* type_member: ID LPAREN list_params RPAREN block_expr  */
#line 403 "parser/parser.y"
    {
        (yyval.node) = create_decl_function_node((yyvsp[-4].var),(yyvsp[-2].arg_list)->args,(yyvsp[-2].arg_list)->arg_count,(yyvsp[0].node),"");
    }
#line 2219 "y.tab.c"
    break;

  case 88: /* type_member: ID LPAREN list_params RPAREN COLON ID block_expr  */
#line 407 "parser/parser.y"
    {
        (yyval.node) = create_decl_function_node((yyvsp[-6].var),(yyvsp[-4].arg_list)->args,(yyvsp[-4].arg_list)->arg_count,(yyvsp[0].node),(yyvsp[-1].var));
    }
#line 2227 "y.tab.c"
    break;

  case 89: /* member_invocation: expr DOT ID  */
#line 415 "parser/parser.y"
    {
        ASTNode* attr = create_var_node((yyvsp[0].var), "",0);
        (yyval.node) = create_property_access_node((yyvsp[-2].node),attr);
    }
#line 2236 "y.tab.c"
    break;

  case 90: /* member_invocation: expr DOT call_function  */
#line 420 "parser/parser.y"
    {
        (yyval.node) = create_property_access_node((yyvsp[-2].node),(yyvsp[0].node));
    }
#line 2244 "y.tab.c"
    break;

  case 91: /* member_assignment: expr DOT ID DESTRUCTOR expr  */
#line 427 "parser/parser.y"
    {
        (yyval.node) = create_property_assignment_node((yyvsp[-4].node),create_var_node((yyvsp[-2].var), "",0),(yyvsp[0].node));
    }
#line 2252 "y.tab.c"
    break;

  case 92: /* destructive_var_decl: ID DESTRUCTOR expr  */
#line 435 "parser/parser.y"
    {
        (yyval.node) = create_assignment_node((yyvsp[-2].var),(yyvsp[0].node),"",AST_DESTRUCTOR);
    }
#line 2260 "y.tab.c"
    break;

  case 93: /* block_expr: LBRACKET block_expr_list RBRACKET  */
#line 442 "parser/parser.y"
                                        {(yyval.node) = create_program_node((yyvsp[-1].arg_list)->args,(yyvsp[-1].arg_list)->arg_count,AST_BLOCK);}
#line 2266 "y.tab.c"
    break;

  case 94: /* type_instance: NEW ID LPAREN args RPAREN  */
#line 446 "parser/parser.y"
                                        { (yyval.node) = create_struct_instance_node((yyvsp[-3].var), (yyvsp[-1].arg_list)->args, (yyvsp[-1].arg_list)->arg_count); }
#line 2272 "y.tab.c"
    break;

  case 95: /* block_expr_list: statement  */
#line 451 "parser/parser.y"
              {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));

        if ((yyvsp[0].node) == NULL) {
            (yyval.arg_list)->args = NULL;
            (yyval.arg_list)->arg_count = 0;
        } else {
            (yyval.arg_list)->args = malloc(sizeof(ASTNode *) * 1);
            (yyval.arg_list)->args[0] = (yyvsp[0].node);
            (yyval.arg_list)->arg_count = 1;
        }
    }
#line 2289 "y.tab.c"
    break;

  case 96: /* block_expr_list: statement block_expr_list  */
#line 463 "parser/parser.y"
                                {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));

        if ((yyvsp[-1].node) == NULL) {
            (yyval.arg_list)->args = malloc(sizeof(ASTNode *) * ((yyvsp[0].arg_list)->arg_count));
            memcpy((yyval.arg_list)->args, (yyvsp[0].arg_list)->args, sizeof(ASTNode *) * (yyvsp[0].arg_list)->arg_count);
            (yyval.arg_list)->arg_count = (yyvsp[0].arg_list)->arg_count;
            free((yyvsp[0].arg_list)->args);
        } else {
            (yyval.arg_list)->args = malloc(sizeof(ASTNode *) * ((yyvsp[0].arg_list)->arg_count + 1));
            (yyval.arg_list)->args[0] = (yyvsp[-1].node);
            memcpy((yyval.arg_list)->args + 1, (yyvsp[0].arg_list)->args, sizeof(ASTNode *) * (yyvsp[0].arg_list)->arg_count);
            (yyval.arg_list)->arg_count = (yyvsp[0].arg_list)->arg_count + 1;
            free((yyvsp[0].arg_list)->args);
        }
    }
#line 2310 "y.tab.c"
    break;

  case 97: /* block_expr_list: %empty  */
#line 480 "parser/parser.y"
                  {
        (yyval.arg_list) = malloc(sizeof(*(yyval.arg_list)));
        (yyval.arg_list)->args = NULL;
        (yyval.arg_list)->arg_count = 0;
    }
#line 2320 "y.tab.c"
    break;


#line 2324 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 490 "parser/parser.y"





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
