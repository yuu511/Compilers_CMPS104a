/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 3 "parser.y" /* yacc.c:339  */


#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "astree.h"
#include "lyutils.h"


#line 77 "yyparse.cpp" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 1
#endif

/* In a future release of Bison, this section will be replaced
   by #include "yyparse.h".  */
#ifndef YY_YY_YYPARSE_H_INCLUDED
# define YY_YY_YYPARSE_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    TOK_VOID = 258,
    TOK_INT = 259,
    TOK_STRING = 260,
    TOK_IF = 261,
    TOK_ELSE = 262,
    TOK_WHILE = 263,
    TOK_RETURN = 264,
    TOK_STRUCT = 265,
    TOK_NULLPTR = 266,
    TOK_ARRAY = 267,
    TOK_ARROW = 268,
    TOK_ALLOC = 269,
    TOK_PTR = 270,
    TOK_EQ = 271,
    TOK_NE = 272,
    TOK_LT = 273,
    TOK_LE = 274,
    TOK_GT = 275,
    TOK_GE = 276,
    TOK_NOT = 277,
    TOK_IDENT = 278,
    TOK_INTCON = 279,
    TOK_CHARCON = 280,
    TOK_STRINGCON = 281,
    TOK_ROOT = 282,
    TOK_BLOCK = 283,
    TOK_CALL = 284,
    TOK_INITDECL = 285,
    TOK_TYPE_ID = 286,
    TOK_VARDECL = 287,
    TOK_INDEX = 288,
    U_PLUS = 289,
    U_MINUS = 290
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_YYPARSE_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 164 "yyparse.cpp" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
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
#define YYLAST   351

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  18
/* YYNRULES -- Number of rules.  */
#define YYNRULES  61
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  129

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   290

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    41,     2,     2,
      45,    49,    39,    37,    50,    38,     2,    40,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    47,
      35,    34,    36,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    44,     2,    51,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    48,     2,    46,     2,     2,     2,     2,
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
      25,    26,    27,    28,    29,    30,    31,    32,    33,    42,
      43
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    49,    49,    52,    53,    54,    56,    58,    61,    64,
      70,    74,    81,    82,    83,    86,    87,    92,    93,    94,
      95,   101,   106,   111,   112,   113,   114,   115,   116,   117,
     118,   119,   120,   121,   123,   125,   126,   127,   128,   131,
     132,   133,   136,   141,   148,   157,   159,   163,   165,   168,
     169,   172,   175,   176,   177,   178,   182,   184,   186,   189,
     190,   193
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 1
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "TOK_VOID", "TOK_INT", "TOK_STRING",
  "TOK_IF", "TOK_ELSE", "TOK_WHILE", "TOK_RETURN", "TOK_STRUCT",
  "TOK_NULLPTR", "TOK_ARRAY", "TOK_ARROW", "TOK_ALLOC", "TOK_PTR",
  "TOK_EQ", "TOK_NE", "TOK_LT", "TOK_LE", "TOK_GT", "TOK_GE", "TOK_NOT",
  "TOK_IDENT", "TOK_INTCON", "TOK_CHARCON", "TOK_STRINGCON", "TOK_ROOT",
  "TOK_BLOCK", "TOK_CALL", "TOK_INITDECL", "TOK_TYPE_ID", "TOK_VARDECL",
  "TOK_INDEX", "'='", "'<'", "'>'", "'+'", "'-'", "'*'", "'/'", "'%'",
  "U_PLUS", "U_MINUS", "'['", "'('", "'}'", "';'", "'{'", "')'", "','",
  "']'", "$accept", "start", "program", "structdef", "sargs", "statement",
  "type", "plaintype", "vardecl", "expr", "allocator", "call", "cargs",
  "variable", "constant", "block", "bargs", "while", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,    61,    60,    62,    43,    45,    42,
      47,    37,   289,   290,    91,    40,   125,    59,   123,    41,
      44,    93
};
# endif

#define YYPACT_NINF -42

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-42)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -42,    13,    36,   -42,     9,   -42,   -42,   -42,   -29,    -1,
       8,    12,   -42,    49,   -42,    76,   -42,    39,   -42,   -42,
     -42,    55,   -42,   -42,   -42,   293,    17,    89,    56,   -42,
     -42,    22,    51,   -26,   -42,   -42,   -42,    37,    30,   -42,
     -42,   -42,   293,   293,   293,   146,   -42,   -42,   -30,   -42,
     -42,    95,    40,    54,   -42,    35,   293,   -42,    61,   123,
      -2,    -2,   175,    66,   293,   293,   293,   293,   293,   293,
     293,   293,   293,   293,   293,   293,   293,     2,   -42,   293,
      59,    96,   -42,    84,   -42,   262,   100,    90,    99,   -42,
     307,   -42,   -42,    77,    77,    77,    77,   307,    77,    77,
     111,   111,    -2,    -2,    -2,    92,   -42,   307,   -42,    65,
     -42,   -42,   102,    89,    94,   -42,   -42,    97,   104,   293,
     105,   108,   204,   -42,   112,   -42,   293,   233,   -42
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       7,     0,     0,     1,     0,    18,    17,    19,     0,     0,
       0,     0,    58,     0,     3,     0,     4,     0,    15,    12,
      13,     0,    14,     5,     6,     0,     0,     0,     0,    57,
      59,     0,     0,     0,    56,    60,    55,     0,    49,    52,
      53,    54,     0,     0,     0,     0,    37,    39,     0,    40,
      41,     0,     0,     0,     8,     0,     0,    22,     0,     0,
      36,    35,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    45,     0,
       0,     0,    16,     0,    10,     0,     0,     0,     0,    46,
      47,    38,    51,    29,    30,    31,    32,    23,    33,    34,
      24,    25,    26,    27,    28,     0,    61,    48,     9,     0,
      20,    21,     0,     0,     0,    50,    11,     0,     0,     0,
       0,     0,     0,    43,     0,    42,     0,     0,    44
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -42,   -42,   -42,   -42,   -42,    -9,    -6,   -27,   -42,   -41,
     -42,   -42,   -42,   -42,   -42,   -42,   -42,   -42
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    14,    15,    16,    17,    18,    19,    45,
      46,    47,    48,    49,    50,    20,    21,    22
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      52,    60,    61,    62,    30,     5,     6,     7,    56,    32,
       8,    63,    35,     3,    10,    85,    25,    11,    90,    78,
      79,    57,    26,    93,    94,    95,    96,    97,    98,    99,
     100,   101,   102,   103,   104,   105,    -2,     4,   107,     5,
       6,     7,    76,    27,     8,    81,     9,    28,    10,    12,
      13,    11,     5,     6,     7,    23,    24,     8,     5,     6,
       7,    10,    33,     8,    11,    51,    53,    10,   106,    54,
      11,    86,    58,    87,    55,    59,    82,    83,   122,     5,
       6,     7,    84,    12,    13,   127,   118,    88,    10,    92,
      63,    11,     5,     6,     7,    29,    12,    13,     5,     6,
       7,    34,    12,    13,    11,    63,   108,    10,    64,    65,
      11,    66,   116,    67,    71,    72,    73,    74,    75,   109,
     110,    76,    31,   112,    63,   113,    68,    69,    70,    71,
      72,    73,    74,    75,    36,   114,    76,    37,   117,   119,
     121,    80,   120,   115,   124,     0,    38,    39,    40,    41,
      73,    74,    75,     0,   123,    76,     0,   126,     0,    63,
      42,    43,    64,    65,     0,    66,     0,    67,    44,     0,
       0,     0,    89,     0,     0,     0,     0,     0,     0,     0,
      68,    69,    70,    71,    72,    73,    74,    75,    63,     0,
      76,    64,    65,     0,    66,    77,    67,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    68,
      69,    70,    71,    72,    73,    74,    75,    63,     0,    76,
      64,    65,     0,    66,    91,    67,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    68,    69,
      70,    71,    72,    73,    74,    75,    63,     0,    76,    64,
      65,     0,    66,   125,    67,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    68,    69,    70,
      71,    72,    73,    74,    75,    63,     0,    76,    64,    65,
       0,    66,   128,    67,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    68,    69,    70,    71,
      72,    73,    74,    75,    36,     0,    76,    37,     0,   111,
       0,     0,     0,     0,     0,     0,    38,    39,    40,    41,
      63,     0,     0,    64,    65,     0,    66,     0,    67,     0,
      42,    43,     0,     0,     0,     0,     0,     0,    44,     0,
       0,    68,    69,    70,    71,    72,    73,    74,    75,     0,
       0,    76
};

static const yytype_int8 yycheck[] =
{
      27,    42,    43,    44,    13,     3,     4,     5,    34,    15,
       8,    13,    21,     0,    12,    56,    45,    15,    59,    49,
      50,    47,    23,    64,    65,    66,    67,    68,    69,    70,
      71,    72,    73,    74,    75,    76,     0,     1,    79,     3,
       4,     5,    44,    35,     8,    51,    10,    35,    12,    47,
      48,    15,     3,     4,     5,    46,    47,     8,     3,     4,
       5,    12,    23,     8,    15,    48,    10,    12,    77,    47,
      15,    10,    35,    12,    23,    45,    36,    23,   119,     3,
       4,     5,    47,    47,    48,   126,   113,    26,    12,    23,
      13,    15,     3,     4,     5,    46,    47,    48,     3,     4,
       5,    46,    47,    48,    15,    13,    47,    12,    16,    17,
      15,    19,    47,    21,    37,    38,    39,    40,    41,    23,
      36,    44,    46,    23,    13,    35,    34,    35,    36,    37,
      38,    39,    40,    41,    11,    36,    44,    14,    36,    45,
      36,    46,    45,    51,    36,    -1,    23,    24,    25,    26,
      39,    40,    41,    -1,    49,    44,    -1,    45,    -1,    13,
      37,    38,    16,    17,    -1,    19,    -1,    21,    45,    -1,
      -1,    -1,    49,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      34,    35,    36,    37,    38,    39,    40,    41,    13,    -1,
      44,    16,    17,    -1,    19,    49,    21,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,
      35,    36,    37,    38,    39,    40,    41,    13,    -1,    44,
      16,    17,    -1,    19,    49,    21,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,
      36,    37,    38,    39,    40,    41,    13,    -1,    44,    16,
      17,    -1,    19,    49,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,
      37,    38,    39,    40,    41,    13,    -1,    44,    16,    17,
      -1,    19,    49,    21,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    34,    35,    36,    37,
      38,    39,    40,    41,    11,    -1,    44,    14,    -1,    47,
      -1,    -1,    -1,    -1,    -1,    -1,    23,    24,    25,    26,
      13,    -1,    -1,    16,    17,    -1,    19,    -1,    21,    -1,
      37,    38,    -1,    -1,    -1,    -1,    -1,    -1,    45,    -1,
      -1,    34,    35,    36,    37,    38,    39,    40,    41,    -1,
      -1,    44
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    53,    54,     0,     1,     3,     4,     5,     8,    10,
      12,    15,    47,    48,    55,    56,    57,    58,    59,    60,
      67,    68,    69,    46,    47,    45,    23,    35,    35,    46,
      57,    46,    58,    23,    46,    57,    11,    14,    23,    24,
      25,    26,    37,    38,    45,    61,    62,    63,    64,    65,
      66,    48,    59,    10,    47,    23,    34,    47,    35,    45,
      61,    61,    61,    13,    16,    17,    19,    21,    34,    35,
      36,    37,    38,    39,    40,    41,    44,    49,    49,    50,
      46,    58,    36,    23,    47,    61,    10,    12,    26,    49,
      61,    49,    23,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    57,    61,    47,    23,
      36,    47,    23,    35,    36,    51,    47,    36,    59,    45,
      45,    36,    61,    49,    36,    49,    45,    61,    49
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    52,    53,    54,    54,    54,    54,    54,    55,    55,
      56,    56,    57,    57,    57,    58,    58,    59,    59,    59,
      59,    60,    60,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    61,    61,    61,    61,    61,    61,    61,    61,
      61,    61,    62,    62,    62,    63,    63,    64,    64,    65,
      65,    65,    66,    66,    66,    66,    67,    67,    67,    68,
      68,    69
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     3,     3,     0,     3,     5,
       4,     6,     1,     1,     1,     1,     4,     1,     1,     1,
       5,     5,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     2,     2,     1,     3,     1,
       1,     1,     7,     7,    10,     2,     3,     3,     3,     1,
       4,     3,     1,     1,     1,     1,     2,     2,     1,     2,
       2,     5
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
          case 3: /* TOK_VOID  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 785 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 4: /* TOK_INT  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 791 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 5: /* TOK_STRING  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 797 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 6: /* TOK_IF  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 803 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 7: /* TOK_ELSE  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 809 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 8: /* TOK_WHILE  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 815 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 9: /* TOK_RETURN  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 821 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 10: /* TOK_STRUCT  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 827 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 11: /* TOK_NULLPTR  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 833 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 12: /* TOK_ARRAY  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 839 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 13: /* TOK_ARROW  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 845 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 14: /* TOK_ALLOC  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 851 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 15: /* TOK_PTR  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 857 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 16: /* TOK_EQ  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 863 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 17: /* TOK_NE  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 869 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 18: /* TOK_LT  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 875 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 19: /* TOK_LE  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 881 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 20: /* TOK_GT  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 887 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 21: /* TOK_GE  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 893 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 22: /* TOK_NOT  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 899 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 23: /* TOK_IDENT  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 905 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 24: /* TOK_INTCON  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 911 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 25: /* TOK_CHARCON  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 917 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 26: /* TOK_STRINGCON  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 923 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 27: /* TOK_ROOT  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 929 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 28: /* TOK_BLOCK  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 935 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 29: /* TOK_CALL  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 941 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 30: /* TOK_INITDECL  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 947 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 31: /* TOK_TYPE_ID  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 953 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 32: /* TOK_VARDECL  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 959 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 33: /* TOK_INDEX  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 965 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 34: /* '='  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 971 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 35: /* '<'  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 977 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 36: /* '>'  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 983 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 37: /* '+'  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 989 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 38: /* '-'  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 995 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 39: /* '*'  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1001 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 40: /* '/'  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1007 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 41: /* '%'  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1013 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 42: /* U_PLUS  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1019 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 43: /* U_MINUS  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1025 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 44: /* '['  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1031 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 45: /* '('  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1037 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 46: /* '}'  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1043 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 47: /* ';'  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1049 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 48: /* '{'  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1055 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 49: /* ')'  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1061 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 50: /* ','  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1067 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 51: /* ']'  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1073 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 53: /* start  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1079 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 54: /* program  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1085 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 55: /* structdef  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1091 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 56: /* sargs  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1097 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 57: /* statement  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1103 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 58: /* type  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1109 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 59: /* plaintype  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1115 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 60: /* vardecl  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1121 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 61: /* expr  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1127 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 62: /* allocator  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1133 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 63: /* call  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1139 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 64: /* cargs  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1145 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 65: /* variable  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1151 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 66: /* constant  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1157 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 67: /* block  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1163 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 68: /* bargs  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1169 "yyparse.cpp" /* yacc.c:684  */
        break;

    case 69: /* while  */
#line 26 "parser.y" /* yacc.c:684  */
      { astree::dump (yyoutput, ((*yyvaluep))); }
#line 1175 "yyparse.cpp" /* yacc.c:684  */
        break;


      default:
        break;
    }
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  switch (yytype)
    {
          case 3: /* TOK_VOID  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1521 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 4: /* TOK_INT  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1527 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 5: /* TOK_STRING  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1533 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 6: /* TOK_IF  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1539 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 7: /* TOK_ELSE  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1545 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 8: /* TOK_WHILE  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1551 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 9: /* TOK_RETURN  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1557 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 10: /* TOK_STRUCT  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1563 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 11: /* TOK_NULLPTR  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1569 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 12: /* TOK_ARRAY  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1575 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 13: /* TOK_ARROW  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1581 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 14: /* TOK_ALLOC  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1587 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 15: /* TOK_PTR  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1593 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 16: /* TOK_EQ  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1599 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 17: /* TOK_NE  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1605 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 18: /* TOK_LT  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1611 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 19: /* TOK_LE  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1617 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 20: /* TOK_GT  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1623 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 21: /* TOK_GE  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1629 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 22: /* TOK_NOT  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1635 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 23: /* TOK_IDENT  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1641 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 24: /* TOK_INTCON  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1647 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 25: /* TOK_CHARCON  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1653 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 26: /* TOK_STRINGCON  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1659 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 27: /* TOK_ROOT  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1665 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 28: /* TOK_BLOCK  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1671 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 29: /* TOK_CALL  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1677 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 30: /* TOK_INITDECL  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1683 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 31: /* TOK_TYPE_ID  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1689 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 32: /* TOK_VARDECL  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1695 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 33: /* TOK_INDEX  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1701 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 34: /* '='  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1707 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 35: /* '<'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1713 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 36: /* '>'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1719 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 37: /* '+'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1725 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 38: /* '-'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1731 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 39: /* '*'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1737 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 40: /* '/'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1743 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 41: /* '%'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1749 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 42: /* U_PLUS  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1755 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 43: /* U_MINUS  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1761 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 44: /* '['  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1767 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 45: /* '('  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1773 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 46: /* '}'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1779 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 47: /* ';'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1785 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 48: /* '{'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1791 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 49: /* ')'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1797 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 50: /* ','  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1803 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 51: /* ']'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1809 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 53: /* start  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1815 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 54: /* program  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1821 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 55: /* structdef  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1827 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 56: /* sargs  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1833 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 57: /* statement  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1839 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 58: /* type  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1845 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 59: /* plaintype  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1851 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 60: /* vardecl  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1857 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 61: /* expr  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1863 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 62: /* allocator  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1869 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 63: /* call  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1875 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 64: /* cargs  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1881 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 65: /* variable  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1887 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 66: /* constant  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1893 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 67: /* block  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1899 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 68: /* bargs  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1905 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 69: /* while  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy (((*yyvaluep))); }
#line 1911 "yyparse.cpp" /* yacc.c:1257  */
        break;


      default:
        break;
    }
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */

/* User initialization code.  */
#line 20 "parser.y" /* yacc.c:1429  */
{
  location lloc  = {0, 0, 0 };
  parser::root = new astree (TOK_ROOT, lloc, "<<ROOT>>");
}

#line 2002 "yyparse.cpp" /* yacc.c:1429  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 2:
#line 49 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]) = nullptr; }
#line 2184 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 3:
#line 52 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 2190 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 4:
#line 53 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 2196 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 5:
#line 54 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2]); 
	                         destroy((yyvsp[0]));}
#line 2203 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 6:
#line 56 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2]); 
	                         destroy((yyvsp[0]));}
#line 2210 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 7:
#line 58 "parser.y" /* yacc.c:1646  */
    { (yyval) = parser::root; }
#line 2216 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 8:
#line 61 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2]);
                                               destroy((yyvsp[-1]));
			                       destroy((yyvsp[0])); }
#line 2224 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 9:
#line 64 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-4])->adopt((yyvsp[-3]));    
	                                       destroy((yyvsp[-2]));      
	                                       destroy((yyvsp[-1]));
					       destroy((yyvsp[0])); }
#line 2233 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 10:
#line 70 "parser.y" /* yacc.c:1646  */
    { astree* tid = new astree(TOK_TYPE_ID, (yyvsp[-2])->lloc,"");
                                                          tid->adopt((yyvsp[-2]),(yyvsp[-1]));    
							  (yyval) = (yyvsp[-3])->adopt(tid);
                                                          destroy((yyvsp[0])); }
#line 2242 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 11:
#line 74 "parser.y" /* yacc.c:1646  */
    { astree* tid = new astree(TOK_TYPE_ID, (yyvsp[-2])->lloc,"");
	                                                  tid->adopt((yyvsp[-2]),(yyvsp[-1]));
							  (yyval) = (yyvsp[-5])->adopt((yyvsp[-4]),tid);
	                                                  destroy((yyvsp[-3]));
							  destroy((yyvsp[0])); }
#line 2252 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 12:
#line 81 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2258 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 13:
#line 82 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2264 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 14:
#line 83 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2270 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 15:
#line 86 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2276 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 16:
#line 87 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-3])->adopt((yyvsp[-1])); 
	                                  destroy((yyvsp[-2]));
					  destroy((yyvsp[0])); }
#line 2284 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 17:
#line 92 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2290 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 18:
#line 93 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2296 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 19:
#line 94 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2302 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 20:
#line 95 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-4])->adopt((yyvsp[-1])); 
	                                                 destroy((yyvsp[-2]));
	                                                 destroy((yyvsp[-3])); 
							 destroy((yyvsp[0])); }
#line 2311 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 21:
#line 101 "parser.y" /* yacc.c:1646  */
    { astree* tid = new astree(TOK_TYPE_ID, (yyvsp[-4])->lloc,"");
                                         tid->adopt((yyvsp[-4]),(yyvsp[-3]));
			                 (yyvsp[-2])->adopt_sym(tid,TOK_VARDECL);
				         (yyval) = (yyvsp[-2])->adopt((yyvsp[-1]));
				         destroy((yyvsp[0])); }
#line 2321 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 22:
#line 106 "parser.y" /* yacc.c:1646  */
    { astree* tid = new astree(TOK_TYPE_ID, (yyvsp[-2])->lloc,"");
	                                (yyval) = tid->adopt((yyvsp[-2]),(yyvsp[-1]));
				        destroy((yyvsp[0])); }
#line 2329 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 23:
#line 111 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2335 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 24:
#line 112 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2341 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 25:
#line 113 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2347 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 26:
#line 114 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2353 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 27:
#line 115 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2359 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 28:
#line 116 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2365 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 29:
#line 117 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2371 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 30:
#line 118 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2377 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 31:
#line 119 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2383 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 32:
#line 120 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]), (yyvsp[0])); }
#line 2389 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 33:
#line 121 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt_sym((yyvsp[-2]),TOK_LT); 
	                               (yyvsp[-1])->adopt((yyvsp[0])); }
#line 2396 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 34:
#line 123 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt_sym((yyvsp[-2]),TOK_GT); 
	                               (yyvsp[-1])->adopt((yyvsp[0])); }
#line 2403 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 35:
#line 125 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 2409 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 36:
#line 126 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 2415 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 37:
#line 127 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2421 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 38:
#line 128 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); 
	                               destroy ((yyvsp[-2]));
				       destroy ((yyvsp[0]));}
#line 2429 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 39:
#line 131 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2435 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 40:
#line 132 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2441 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 41:
#line 133 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2447 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 42:
#line 136 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-6])->adopt((yyvsp[-4]),(yyvsp[-1]));
                                                                         destroy((yyvsp[-5]));
							                 destroy((yyvsp[-3])); 
							                 destroy((yyvsp[-2]));
							                 destroy((yyvsp[0])); }
#line 2457 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 43:
#line 141 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-6])->adopt((yyvsp[-3]));
	                                                                 destroy((yyvsp[-5]));
						                         destroy((yyvsp[-4]));
						                         destroy((yyvsp[-2]));
							                 destroy((yyvsp[-1]));
							                 destroy((yyvsp[0])); }
#line 2468 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 44:
#line 148 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-7])->adopt((yyvsp[-5]));  
	                                                                 (yyval) = (yyvsp[-9])->adopt((yyvsp[-7]),(yyvsp[-1]));
									 destroy((yyvsp[-8]));
									 destroy((yyvsp[-6]));
									 destroy((yyvsp[-4]));
									 destroy((yyvsp[-3]));
									 destroy((yyvsp[-2]));
									 destroy((yyvsp[0])); }
#line 2481 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 45:
#line 157 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); 
                   destroy((yyvsp[0])); }
#line 2488 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 46:
#line 159 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt_sym((yyvsp[-2]),TOK_CALL);
                           destroy((yyvsp[0]));}
#line 2495 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 47:
#line 163 "parser.y" /* yacc.c:1646  */
    { (yyvsp[-1])->adopt_sym((yyvsp[-2]),TOK_CALL); 
                             (yyval) = (yyvsp[-1])->adopt((yyvsp[0])); }
#line 2502 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 48:
#line 165 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2])->adopt((yyvsp[0]));
                             destroy((yyvsp[-1])); }
#line 2509 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 49:
#line 168 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2515 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 50:
#line 169 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-2])->adopt_sym((yyvsp[-3]),TOK_INDEX);
	                              (yyval) = (yyvsp[-2])->adopt((yyvsp[-1]));
	                              destroy((yyvsp[0])); }
#line 2523 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 51:
#line 172 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt((yyvsp[-2]),(yyvsp[0])); }
#line 2529 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 52:
#line 175 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2535 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 53:
#line 176 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2541 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 54:
#line 177 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2547 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 55:
#line 178 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2553 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 56:
#line 182 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])->adopt_sym((yyvsp[0]),TOK_BLOCK);
                     destroy((yyvsp[0])); }
#line 2560 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 57:
#line 184 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1]); 
                     destroy((yyvsp[0]));}
#line 2567 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 58:
#line 186 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[0]); }
#line 2573 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 59:
#line 189 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])-> adopt((yyvsp[0])); }
#line 2579 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 60:
#line 190 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-1])-> adopt((yyvsp[0])); }
#line 2585 "yyparse.cpp" /* yacc.c:1646  */
    break;

  case 61:
#line 193 "parser.y" /* yacc.c:1646  */
    { (yyval) = (yyvsp[-4])->adopt((yyvsp[-2]),(yyvsp[0])); 
                                            destroy((yyvsp[-3]));
					    destroy((yyvsp[-1])); }
#line 2593 "yyparse.cpp" /* yacc.c:1646  */
    break;


#line 2597 "yyparse.cpp" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 199 "parser.y" /* yacc.c:1906  */
 

const char* parser::get_tname (int symbol) {
   return yytname [YYTRANSLATE (symbol)];
}

