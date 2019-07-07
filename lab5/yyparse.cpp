/* A Bison parser, made by GNU Bison 3.3.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2019 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.3.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "parser.y" /* yacc.c:337  */


#include <assert.h>
#include <stdlib.h>
#include <string.h>

#include "astree.h"
#include "lyutils.h"


#line 81 "yyparse.cpp" /* yacc.c:337  */
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
    TOK_INDEX = 287,
    TOK_FUNCTION = 288,
    TOK_PARAM = 289,
    U_PLUS = 290,
    U_MINUS = 291
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
typedef unsigned short yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short yytype_int16;
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
#  define YYSIZE_T unsigned
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

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
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
#define YYLAST   544

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  53
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  23
/* YYNRULES -- Number of rules.  */
#define YYNRULES  76
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  162

#define YYUNDEFTOK  2
#define YYMAXUTOK   291

/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  ((unsigned) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,    42,     2,     2,
      46,    50,    40,    38,    51,    39,     2,    41,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    48,
      36,    35,    37,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    45,     2,    52,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    49,     2,    47,     2,     2,     2,     2,
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
      43,    44
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,    50,    50,    53,    54,    55,    56,    57,    58,    61,
      65,    72,    77,    85,    86,    87,    88,    89,    90,    91,
      95,   101,   107,   108,   113,   114,   115,   116,   123,   124,
     125,   126,   127,   128,   129,   130,   131,   132,   133,   135,
     137,   138,   139,   140,   141,   144,   145,   146,   149,   155,
     162,   173,   176,   181,   184,   189,   190,   194,   197,   198,
     199,   200,   204,   207,   212,   213,   216,   222,   228,   234,
     237,   243,   250,   260,   264,   271,   274
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
  "TOK_BLOCK", "TOK_CALL", "TOK_INITDECL", "TOK_TYPE_ID", "TOK_INDEX",
  "TOK_FUNCTION", "TOK_PARAM", "'='", "'<'", "'>'", "'+'", "'-'", "'*'",
  "'/'", "'%'", "U_PLUS", "U_MINUS", "'['", "'('", "'}'", "';'", "'{'",
  "')'", "','", "']'", "$accept", "start", "program", "structdef", "sargs",
  "statement", "vardecl", "type", "plaintype", "expr", "allocator", "call",
  "cargs", "variable", "constant", "block", "bargs", "while", "ifelse",
  "return", "function", "fargs2", "fend", YY_NULLPTR
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
     285,   286,   287,   288,   289,    61,    60,    62,    43,    45,
      42,    47,    37,   290,   291,    91,    40,   125,    59,   123,
      41,    44,    93
};
# endif

#define YYPACT_NINF -87

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-87)))

#define YYTABLE_NINF -3

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -87,     6,   147,   -87,   -33,   -87,   -87,   -87,   -15,   -12,
      -7,   -87,    65,   -87,   -13,   -87,   -87,   -87,   -87,   -22,
      52,    23,   -10,    35,   -23,    86,    34,    60,   -87,    38,
     485,    16,   -87,     2,    40,    74,   -87,    62,   -87,   -87,
      64,   485,    56,   -87,   -87,   -87,   485,   485,   485,   393,
     -87,   -87,    10,   -87,   -87,    14,    80,    14,   276,   -87,
      59,   -87,    25,    -9,   211,    -9,    -9,   227,    81,   485,
     485,   485,   485,   485,   485,   485,   485,   485,   485,   485,
     485,   485,   -87,   -87,   485,   -87,    70,   -87,   117,   -87,
     -87,   -87,    87,   -87,    76,    92,    88,   -87,   499,   -87,
     -87,   213,   213,   213,   213,   499,   213,   213,   140,   140,
      -9,    -9,    -9,   179,   499,    84,    89,   379,   -87,   -87,
     -87,   -87,   111,   423,   -87,   -87,   -87,   -87,   -87,   -87,
     -87,    90,   100,    52,   -87,   485,   485,   -87,   453,   -26,
     -87,   485,    98,   101,   257,   287,   -87,   317,    95,   109,
     164,   164,   -87,   -87,   103,   151,   -87,   485,   164,   347,
     -87,   -87
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       8,     0,     0,     1,     0,    25,    24,    26,     0,     0,
       0,     3,     0,     5,     0,    22,     4,     6,     7,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     9,     0,
       0,     0,    21,     0,     0,     0,    23,     0,    11,    61,
       0,     0,    55,    58,    59,    60,     0,     0,     0,     0,
      43,    45,     0,    46,    47,     0,     0,     0,     0,    10,
       0,    27,     0,    42,     0,    41,    40,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    20,    51,     0,    75,     0,    76,     0,    72,
      73,    71,     0,    12,     0,     0,     0,    52,    53,    44,
      57,    34,    35,    36,    37,    28,    38,    39,    29,    30,
      31,    32,    33,     0,    54,     0,     0,     0,    63,    18,
      64,    13,     0,     0,    14,    15,    16,    17,    62,    65,
      74,     0,     0,     0,    56,     0,     0,    70,     0,     0,
      19,     0,     0,     0,     0,     0,    69,     0,     0,     0,
       0,     0,    48,    49,     0,    68,    66,     0,     0,     0,
      67,    50
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -87,   -87,   -87,   -87,   -87,   -86,   152,     1,   -19,   -30,
     -87,   -87,   -87,   -87,   -87,   -50,   -87,   -87,   -87,   -87,
     -87,   -87,   104
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     1,     2,    11,    12,   120,   121,   122,    15,   123,
      50,    51,    52,    53,    54,   124,    88,   125,   126,   127,
      16,    33,    89
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    26,   129,    14,    68,    87,     3,    87,    19,    30,
      24,    63,    30,    23,    17,    18,    65,    66,    67,     5,
       6,     7,    32,    31,    20,    32,    35,    25,     9,    21,
      94,    10,    56,    27,    98,    95,    81,    96,    28,   101,
     102,   103,   104,   105,   106,   107,   108,   109,   110,   111,
     112,   113,    57,    58,   114,     5,     6,     7,    29,    92,
      83,    84,    85,    86,   155,   156,    55,    10,     5,     6,
       7,    36,   160,     5,     6,     7,   115,     9,   116,   117,
      10,    39,     9,    37,    40,    10,    38,   138,    59,     5,
       6,     7,    41,    42,    43,    44,    45,    60,     9,    61,
      62,    10,    64,    90,   100,   144,   145,    93,    46,    47,
     130,   147,    22,   131,   143,   132,    48,   118,   119,    86,
       5,     6,     7,   115,   133,   116,   117,   159,    39,     9,
     135,    40,    10,    34,   139,   136,   141,   142,   149,    41,
      42,    43,    44,    45,   148,   153,   154,    -2,     4,   157,
       5,     6,     7,    68,    13,    46,    47,     8,   158,     9,
       0,    91,    10,    48,   128,   119,    86,     5,     6,     7,
     115,     0,   116,   117,     0,    39,     9,     0,    40,    10,
      78,    79,    80,     0,     0,    81,    41,    42,    43,    44,
      45,     0,    68,     0,     0,    69,    70,     0,    71,     0,
      72,     0,    46,    47,     0,     0,     0,     0,     0,     0,
      48,     0,   119,    86,    73,    74,    75,    76,    77,    78,
      79,    80,    39,     0,    81,    40,    68,     0,     0,     0,
       0,   134,     0,    41,    42,    43,    44,    45,     0,     0,
      68,     0,     0,    69,    70,     0,    71,     0,    72,    46,
      47,    76,    77,    78,    79,    80,     0,    48,    81,     0,
       0,    97,    73,    74,    75,    76,    77,    78,    79,    80,
      68,     0,    81,    69,    70,     0,    71,    99,    72,     5,
       6,     7,     0,     0,     0,     0,     0,     0,     9,     0,
       0,    10,    73,    74,    75,    76,    77,    78,    79,    80,
      68,     0,    81,    69,    70,     0,    71,   150,    72,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    73,    74,    75,    76,    77,    78,    79,    80,
      68,     0,    81,    69,    70,     0,    71,   151,    72,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    73,    74,    75,    76,    77,    78,    79,    80,
      68,     0,    81,    69,    70,     0,    71,   152,    72,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    73,    74,    75,    76,    77,    78,    79,    80,
      39,     0,    81,    40,     0,     0,     0,   161,     0,     0,
       0,    41,    42,    43,    44,    45,    68,     0,     0,    69,
      70,     0,    71,     0,    72,     0,     0,    46,    47,     0,
       0,     0,     0,     0,     0,    48,     0,   137,    73,    74,
      75,    76,    77,    78,    79,    80,    68,     0,    81,    69,
      70,    82,    71,     0,    72,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    73,    74,
      75,    76,    77,    78,    79,    80,    68,     0,    81,    69,
      70,   140,    71,     0,    72,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,    73,    74,
      75,    76,    77,    78,    79,    80,    39,     0,    81,    40,
       0,   146,     0,     0,     0,     0,     0,    41,    42,    43,
      44,    45,    68,     0,     0,    69,    70,     0,    71,     0,
      72,     0,     0,    46,    47,     0,     0,     0,     0,     0,
       0,    48,     0,     0,    73,    74,    75,    76,    77,    78,
      79,    80,     0,     0,    81
};

static const yytype_int16 yycheck[] =
{
      30,    20,    88,     2,    13,    55,     0,    57,    23,    35,
      23,    41,    35,    12,    47,    48,    46,    47,    48,     3,
       4,     5,    48,    46,    36,    48,    25,    49,    12,    36,
       5,    15,    31,    10,    64,    10,    45,    12,    48,    69,
      70,    71,    72,    73,    74,    75,    76,    77,    78,    79,
      80,    81,    50,    51,    84,     3,     4,     5,    23,    58,
      50,    51,    48,    49,   150,   151,    50,    15,     3,     4,
       5,    37,   158,     3,     4,     5,     6,    12,     8,     9,
      15,    11,    12,    23,    14,    15,    48,   117,    48,     3,
       4,     5,    22,    23,    24,    25,    26,    23,    12,    37,
      36,    15,    46,    23,    23,   135,   136,    48,    38,    39,
      23,   141,    47,    37,   133,    23,    46,    47,    48,    49,
       3,     4,     5,     6,    36,     8,     9,   157,    11,    12,
      46,    14,    15,    47,    23,    46,    46,    37,    37,    22,
      23,    24,    25,    26,    46,    50,    37,     0,     1,    46,
       3,     4,     5,    13,     2,    38,    39,    10,     7,    12,
      -1,    57,    15,    46,    47,    48,    49,     3,     4,     5,
       6,    -1,     8,     9,    -1,    11,    12,    -1,    14,    15,
      40,    41,    42,    -1,    -1,    45,    22,    23,    24,    25,
      26,    -1,    13,    -1,    -1,    16,    17,    -1,    19,    -1,
      21,    -1,    38,    39,    -1,    -1,    -1,    -1,    -1,    -1,
      46,    -1,    48,    49,    35,    36,    37,    38,    39,    40,
      41,    42,    11,    -1,    45,    14,    13,    -1,    -1,    -1,
      -1,    52,    -1,    22,    23,    24,    25,    26,    -1,    -1,
      13,    -1,    -1,    16,    17,    -1,    19,    -1,    21,    38,
      39,    38,    39,    40,    41,    42,    -1,    46,    45,    -1,
      -1,    50,    35,    36,    37,    38,    39,    40,    41,    42,
      13,    -1,    45,    16,    17,    -1,    19,    50,    21,     3,
       4,     5,    -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      -1,    15,    35,    36,    37,    38,    39,    40,    41,    42,
      13,    -1,    45,    16,    17,    -1,    19,    50,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      13,    -1,    45,    16,    17,    -1,    19,    50,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      13,    -1,    45,    16,    17,    -1,    19,    50,    21,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    35,    36,    37,    38,    39,    40,    41,    42,
      11,    -1,    45,    14,    -1,    -1,    -1,    50,    -1,    -1,
      -1,    22,    23,    24,    25,    26,    13,    -1,    -1,    16,
      17,    -1,    19,    -1,    21,    -1,    -1,    38,    39,    -1,
      -1,    -1,    -1,    -1,    -1,    46,    -1,    48,    35,    36,
      37,    38,    39,    40,    41,    42,    13,    -1,    45,    16,
      17,    48,    19,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    13,    -1,    45,    16,
      17,    48,    19,    -1,    21,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    35,    36,
      37,    38,    39,    40,    41,    42,    11,    -1,    45,    14,
      -1,    48,    -1,    -1,    -1,    -1,    -1,    22,    23,    24,
      25,    26,    13,    -1,    -1,    16,    17,    -1,    19,    -1,
      21,    -1,    -1,    38,    39,    -1,    -1,    -1,    -1,    -1,
      -1,    46,    -1,    -1,    35,    36,    37,    38,    39,    40,
      41,    42,    -1,    -1,    45
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    54,    55,     0,     1,     3,     4,     5,    10,    12,
      15,    56,    57,    59,    60,    61,    73,    47,    48,    23,
      36,    36,    47,    60,    23,    49,    61,    10,    48,    23,
      35,    46,    48,    74,    47,    60,    37,    23,    48,    11,
      14,    22,    23,    24,    25,    26,    38,    39,    46,    62,
      63,    64,    65,    66,    67,    50,    60,    50,    51,    48,
      23,    37,    36,    62,    46,    62,    62,    62,    13,    16,
      17,    19,    21,    35,    36,    37,    38,    39,    40,    41,
      42,    45,    48,    50,    51,    48,    49,    68,    69,    75,
      23,    75,    60,    48,     5,    10,    12,    50,    62,    50,
      23,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,     6,     8,     9,    47,    48,
      58,    59,    60,    62,    68,    70,    71,    72,    47,    58,
      23,    37,    23,    36,    52,    46,    46,    48,    62,    23,
      48,    46,    37,    61,    62,    62,    48,    62,    46,    37,
      50,    50,    50,    50,    37,    58,    58,    46,     7,    62,
      58,    50
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    53,    54,    55,    55,    55,    55,    55,    55,    56,
      56,    57,    57,    58,    58,    58,    58,    58,    58,    58,
      59,    59,    60,    60,    61,    61,    61,    61,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    62,    63,    63,
      63,    64,    64,    65,    65,    66,    66,    66,    67,    67,
      67,    67,    68,    68,    69,    69,    70,    71,    71,    72,
      72,    73,    73,    74,    74,    75,    75
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     2,     2,     3,     3,     0,     3,
       5,     4,     6,     1,     1,     1,     1,     1,     1,     2,
       5,     3,     1,     4,     1,     1,     1,     5,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       2,     2,     2,     1,     3,     1,     1,     1,     7,     7,
      10,     2,     3,     3,     3,     1,     4,     3,     1,     1,
       1,     1,     2,     2,     2,     2,     5,     7,     5,     3,
       2,     5,     5,     3,     4,     1,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  switch (yytype)
    {
    case 3: /* TOK_VOID  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 838 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 4: /* TOK_INT  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 844 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 5: /* TOK_STRING  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 850 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 6: /* TOK_IF  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 856 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 7: /* TOK_ELSE  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 862 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 8: /* TOK_WHILE  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 868 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 9: /* TOK_RETURN  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 874 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 10: /* TOK_STRUCT  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 880 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 11: /* TOK_NULLPTR  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 886 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 12: /* TOK_ARRAY  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 892 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 13: /* TOK_ARROW  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 898 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 14: /* TOK_ALLOC  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 904 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 15: /* TOK_PTR  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 910 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 16: /* TOK_EQ  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 916 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 17: /* TOK_NE  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 922 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 18: /* TOK_LT  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 928 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 19: /* TOK_LE  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 934 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 20: /* TOK_GT  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 940 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 21: /* TOK_GE  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 946 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 22: /* TOK_NOT  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 952 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 23: /* TOK_IDENT  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 958 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 24: /* TOK_INTCON  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 964 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 25: /* TOK_CHARCON  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 970 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 26: /* TOK_STRINGCON  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 976 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 27: /* TOK_ROOT  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 982 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 28: /* TOK_BLOCK  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 988 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 29: /* TOK_CALL  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 994 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 30: /* TOK_INITDECL  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1000 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 31: /* TOK_TYPE_ID  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1006 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 32: /* TOK_INDEX  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1012 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 33: /* TOK_FUNCTION  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1018 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 34: /* TOK_PARAM  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1024 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 35: /* '='  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1030 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 36: /* '<'  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1036 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 37: /* '>'  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1042 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 38: /* '+'  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1048 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 39: /* '-'  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1054 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 40: /* '*'  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1060 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 41: /* '/'  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1066 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 42: /* '%'  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1072 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 43: /* U_PLUS  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1078 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 44: /* U_MINUS  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1084 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 45: /* '['  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1090 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 46: /* '('  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1096 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 47: /* '}'  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1102 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 48: /* ';'  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1108 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 49: /* '{'  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1114 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 50: /* ')'  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1120 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 51: /* ','  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1126 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 52: /* ']'  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1132 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 54: /* start  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1138 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 55: /* program  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1144 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 56: /* structdef  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1150 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 57: /* sargs  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1156 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 58: /* statement  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1162 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 59: /* vardecl  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1168 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 60: /* type  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1174 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 61: /* plaintype  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1180 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 62: /* expr  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1186 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 63: /* allocator  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1192 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 64: /* call  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1198 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 65: /* cargs  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1204 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 66: /* variable  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1210 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 67: /* constant  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1216 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 68: /* block  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1222 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 69: /* bargs  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1228 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 70: /* while  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1234 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 71: /* ifelse  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1240 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 72: /* return  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1246 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 73: /* function  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1252 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 74: /* fargs2  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1258 "yyparse.cpp" /* yacc.c:680  */
        break;

    case 75: /* fend  */
#line 26 "parser.y" /* yacc.c:680  */
      { astree::dump (yyoutput, (*yyvaluep)); }
#line 1264 "yyparse.cpp" /* yacc.c:680  */
        break;

      default:
        break;
    }
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyo, yytype, yyvaluep);
  YYFPRINTF (yyo, ")");
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
  unsigned long yylno = yyrline[yyrule];
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
                       &yyvsp[(yyi + 1) - (yynrhs)]
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
            else
              goto append;

          append:
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

  return (YYSIZE_T) (yystpcpy (yyres, yystr) - yyres);
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
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
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
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
      { destroy ((*yyvaluep)); }
#line 1614 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 4: /* TOK_INT  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1620 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 5: /* TOK_STRING  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1626 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 6: /* TOK_IF  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1632 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 7: /* TOK_ELSE  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1638 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 8: /* TOK_WHILE  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1644 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 9: /* TOK_RETURN  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1650 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 10: /* TOK_STRUCT  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1656 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 11: /* TOK_NULLPTR  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1662 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 12: /* TOK_ARRAY  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1668 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 13: /* TOK_ARROW  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1674 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 14: /* TOK_ALLOC  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1680 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 15: /* TOK_PTR  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1686 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 16: /* TOK_EQ  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1692 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 17: /* TOK_NE  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1698 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 18: /* TOK_LT  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1704 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 19: /* TOK_LE  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1710 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 20: /* TOK_GT  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1716 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 21: /* TOK_GE  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1722 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 22: /* TOK_NOT  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1728 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 23: /* TOK_IDENT  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1734 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 24: /* TOK_INTCON  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1740 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 25: /* TOK_CHARCON  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1746 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 26: /* TOK_STRINGCON  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1752 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 27: /* TOK_ROOT  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1758 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 28: /* TOK_BLOCK  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1764 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 29: /* TOK_CALL  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1770 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 30: /* TOK_INITDECL  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1776 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 31: /* TOK_TYPE_ID  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1782 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 32: /* TOK_INDEX  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1788 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 33: /* TOK_FUNCTION  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1794 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 34: /* TOK_PARAM  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1800 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 35: /* '='  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1806 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 36: /* '<'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1812 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 37: /* '>'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1818 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 38: /* '+'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1824 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 39: /* '-'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1830 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 40: /* '*'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1836 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 41: /* '/'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1842 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 42: /* '%'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1848 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 43: /* U_PLUS  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1854 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 44: /* U_MINUS  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1860 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 45: /* '['  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1866 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 46: /* '('  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1872 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 47: /* '}'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1878 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 48: /* ';'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1884 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 49: /* '{'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1890 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 50: /* ')'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1896 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 51: /* ','  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1902 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 52: /* ']'  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1908 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 54: /* start  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1914 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 55: /* program  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1920 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 56: /* structdef  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1926 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 57: /* sargs  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1932 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 58: /* statement  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1938 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 59: /* vardecl  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1944 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 60: /* type  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1950 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 61: /* plaintype  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1956 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 62: /* expr  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1962 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 63: /* allocator  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1968 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 64: /* call  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1974 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 65: /* cargs  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1980 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 66: /* variable  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1986 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 67: /* constant  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1992 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 68: /* block  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 1998 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 69: /* bargs  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 2004 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 70: /* while  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 2010 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 71: /* ifelse  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 2016 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 72: /* return  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 2022 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 73: /* function  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 2028 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 74: /* fargs2  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 2034 "yyparse.cpp" /* yacc.c:1257  */
        break;

    case 75: /* fend  */
#line 25 "parser.y" /* yacc.c:1257  */
      { destroy ((*yyvaluep)); }
#line 2040 "yyparse.cpp" /* yacc.c:1257  */
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
#line 20 "parser.y" /* yacc.c:1431  */
{
  location lloc  = {0, 0, 0 };
  parser::root = new astree (TOK_ROOT, lloc, "<<ROOT>>");
}

#line 2130 "yyparse.cpp" /* yacc.c:1431  */
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yynewstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  *yyssp = (yytype_int16) yystate;

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = (YYSIZE_T) (yyssp - yyss + 1);

# if defined yyoverflow
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
# else /* defined YYSTACK_RELOCATE */
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
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */

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
        case 2:
#line 50 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0] = nullptr; }
#line 2316 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 3:
#line 53 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[0]); }
#line 2322 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 4:
#line 54 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[0]); }
#line 2328 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 5:
#line 55 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[0]); }
#line 2334 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 6:
#line 56 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-2]; destroy(yyvsp[0]); }
#line 2340 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 7:
#line 57 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-2]; destroy(yyvsp[0]); }
#line 2346 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 8:
#line 58 "parser.y" /* yacc.c:1652  */
    { yyval = parser::root; }
#line 2352 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 9:
#line 61 "parser.y" /* yacc.c:1652  */
    { 
             yyval = yyvsp[-2];
             destroy(yyvsp[-1]);
             destroy(yyvsp[0]); }
#line 2361 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 10:
#line 65 "parser.y" /* yacc.c:1652  */
    { 
              yyval = yyvsp[-4]->adopt(yyvsp[-3]);    
              destroy(yyvsp[-2]);      
              destroy(yyvsp[-1]);
              destroy(yyvsp[0]); }
#line 2371 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 11:
#line 72 "parser.y" /* yacc.c:1652  */
    { 
              astree* tid = new astree(TOK_TYPE_ID, yyvsp[-2]->lloc,"");
              tid->adopt(yyvsp[-2],yyvsp[-1]);    
              yyval = yyvsp[-3]->adopt(tid);
              destroy(yyvsp[0]); }
#line 2381 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 12:
#line 77 "parser.y" /* yacc.c:1652  */
    {
              astree* tid = new astree(TOK_TYPE_ID, yyvsp[-2]->lloc,"");
              tid->adopt(yyvsp[-2],yyvsp[-1]);
              yyval = yyvsp[-5]->adopt(yyvsp[-4],tid);
              destroy(yyvsp[-3]);
              destroy(yyvsp[0]); }
#line 2392 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 13:
#line 85 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2398 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 14:
#line 86 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2404 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 15:
#line 87 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2410 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 16:
#line 88 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2416 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 17:
#line 89 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2422 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 18:
#line 90 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2428 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 19:
#line 91 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]; 
                       destroy (yyvsp[0]); }
#line 2435 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 20:
#line 95 "parser.y" /* yacc.c:1652  */
    { 
            astree* tid = new astree(TOK_TYPE_ID, yyvsp[-4]->lloc,"");
            tid->adopt(yyvsp[-4],yyvsp[-3]);
            yyval = tid->adopt(yyvsp[-1]);
            destroy(yyvsp[-2]); 
            destroy(yyvsp[0]); }
#line 2446 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 21:
#line 101 "parser.y" /* yacc.c:1652  */
    { 
            astree* tid = new astree(TOK_TYPE_ID, yyvsp[-2]->lloc,"");
            yyval = tid->adopt(yyvsp[-2],yyvsp[-1]);
            destroy(yyvsp[0]); }
#line 2455 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 22:
#line 107 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2461 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 23:
#line 108 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-3]->adopt(yyvsp[-1]); 
                                     destroy(yyvsp[-2]);
                                     destroy(yyvsp[0]); }
#line 2469 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 24:
#line 113 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2475 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 25:
#line 114 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2481 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 26:
#line 115 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2487 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 27:
#line 116 "parser.y" /* yacc.c:1652  */
    { 
              yyval = yyvsp[-4]->adopt(yyvsp[-1]); 
              destroy(yyvsp[-2]);
              destroy(yyvsp[-3]); 
              destroy(yyvsp[0]); }
#line 2497 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 28:
#line 123 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[-2], yyvsp[0]); }
#line 2503 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 29:
#line 124 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[-2], yyvsp[0]); }
#line 2509 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 30:
#line 125 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[-2], yyvsp[0]); }
#line 2515 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 31:
#line 126 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[-2], yyvsp[0]); }
#line 2521 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 32:
#line 127 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[-2], yyvsp[0]); }
#line 2527 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 33:
#line 128 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[-2], yyvsp[0]); }
#line 2533 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 34:
#line 129 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[-2], yyvsp[0]); }
#line 2539 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 35:
#line 130 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[-2], yyvsp[0]); }
#line 2545 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 36:
#line 131 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[-2], yyvsp[0]); }
#line 2551 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 37:
#line 132 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[-2], yyvsp[0]); }
#line 2557 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 38:
#line 133 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt_sym(yyvsp[-2],TOK_LT); 
                                   yyvsp[-1]->adopt(yyvsp[0]); }
#line 2564 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 39:
#line 135 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt_sym(yyvsp[-2],TOK_GT); 
                                   yyvsp[-1]->adopt(yyvsp[0]); }
#line 2571 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 40:
#line 137 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[0]); }
#line 2577 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 41:
#line 138 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[0]); }
#line 2583 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 42:
#line 139 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[0]); }
#line 2589 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 43:
#line 140 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2595 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 44:
#line 141 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]; 
                                   destroy (yyvsp[-2]);
                                   destroy (yyvsp[0]);}
#line 2603 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 45:
#line 144 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2609 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 46:
#line 145 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2615 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 47:
#line 146 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2621 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 48:
#line 149 "parser.y" /* yacc.c:1652  */
    { 
              yyval = yyvsp[-6]->adopt(yyvsp[-4],yyvsp[-1]);
              destroy(yyvsp[-5]);
              destroy(yyvsp[-3]); 
              destroy(yyvsp[-2]);
              destroy(yyvsp[0]); }
#line 2632 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 49:
#line 155 "parser.y" /* yacc.c:1652  */
    { 
              yyval = yyvsp[-6]->adopt(yyvsp[-3]);
              destroy(yyvsp[-5]);
              destroy(yyvsp[-4]);
              destroy(yyvsp[-2]);
              destroy(yyvsp[-1]);
              destroy(yyvsp[0]); }
#line 2644 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 50:
#line 162 "parser.y" /* yacc.c:1652  */
    {
              yyvsp[-7]->adopt(yyvsp[-5]);  
              yyval = yyvsp[-9]->adopt(yyvsp[-7],yyvsp[-1]);
              destroy(yyvsp[-8]);
              destroy(yyvsp[-6]);
              destroy(yyvsp[-4]);
              destroy(yyvsp[-3]);
              destroy(yyvsp[-2]);
              destroy(yyvsp[0]); }
#line 2658 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 51:
#line 173 "parser.y" /* yacc.c:1652  */
    { 
         yyval = yyvsp[-1]; 
         destroy(yyvsp[0]); }
#line 2666 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 52:
#line 176 "parser.y" /* yacc.c:1652  */
    { 
         yyval = yyvsp[-1]->adopt_sym(yyvsp[-2],TOK_CALL);
         destroy(yyvsp[0]); }
#line 2674 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 53:
#line 181 "parser.y" /* yacc.c:1652  */
    { 
          yyvsp[-1]->adopt_sym(yyvsp[-2],TOK_CALL); 
          yyval = yyvsp[-1]->adopt(yyvsp[0]); }
#line 2682 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 54:
#line 184 "parser.y" /* yacc.c:1652  */
    { 
          yyval = yyvsp[-2]->adopt(yyvsp[0]);
          destroy(yyvsp[-1]); }
#line 2690 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 55:
#line 189 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2696 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 56:
#line 190 "parser.y" /* yacc.c:1652  */
    { 
             yyvsp[-2]->adopt_sym(yyvsp[-3],TOK_INDEX);
             yyval = yyvsp[-2]->adopt(yyvsp[-1]);
             destroy(yyvsp[0]); }
#line 2705 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 57:
#line 194 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]->adopt(yyvsp[-2],yyvsp[0]); }
#line 2711 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 58:
#line 197 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2717 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 59:
#line 198 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2723 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 60:
#line 199 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2729 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 61:
#line 200 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2735 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 62:
#line 204 "parser.y" /* yacc.c:1652  */
    { 
          yyval = yyvsp[-1];
          destroy(yyvsp[0]); }
#line 2743 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 63:
#line 207 "parser.y" /* yacc.c:1652  */
    { 
          yyval = yyvsp[-1]->adopt_sym(nullptr,TOK_BLOCK);
          destroy(yyvsp[0]); }
#line 2751 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 64:
#line 212 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]-> adopt_sym(yyvsp[0],TOK_BLOCK); }
#line 2757 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 65:
#line 213 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[-1]-> adopt(yyvsp[0]); }
#line 2763 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 66:
#line 216 "parser.y" /* yacc.c:1652  */
    { 
           yyval = yyvsp[-4]->adopt(yyvsp[-2],yyvsp[0]); 
           destroy(yyvsp[-3]);
           destroy(yyvsp[-1]); }
#line 2772 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 67:
#line 222 "parser.y" /* yacc.c:1652  */
    { 
           yyvsp[-6]->adopt(yyvsp[-4],yyvsp[-2]); 
           yyval = yyvsp[-6]->adopt(yyvsp[0]);
           destroy(yyvsp[-5]);
           destroy(yyvsp[-3]);
           destroy(yyvsp[-1]); }
#line 2783 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 68:
#line 228 "parser.y" /* yacc.c:1652  */
    { 
           yyval = yyvsp[-4]->adopt(yyvsp[-2],yyvsp[0]);
           destroy(yyvsp[-3]);
           destroy(yyvsp[-1]); }
#line 2792 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 69:
#line 234 "parser.y" /* yacc.c:1652  */
    { 
           yyval= yyvsp[-2]->adopt(yyvsp[-1]);
           destroy(yyvsp[0]); }
#line 2800 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 70:
#line 237 "parser.y" /* yacc.c:1652  */
    { 
           yyval = yyvsp[-1]; 
           destroy(yyvsp[0]); }
#line 2808 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 71:
#line 243 "parser.y" /* yacc.c:1652  */
    { 
             astree* func = new astree(TOK_FUNCTION, yyvsp[-4]->lloc,"");
             astree* tid = new astree(TOK_TYPE_ID, yyvsp[-4]->lloc,"");
             tid->adopt(yyvsp[-4],yyvsp[-3]);
             func->adopt(tid);
             yyval = func->adopt(yyvsp[-2],yyvsp[0]);
             destroy(yyvsp[-1]); }
#line 2820 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 72:
#line 250 "parser.y" /* yacc.c:1652  */
    { 
             astree* func = new astree(TOK_FUNCTION, yyvsp[-4]->lloc,"");
             astree* tid = new astree(TOK_TYPE_ID, yyvsp[-4]->lloc,"");
             tid->adopt(yyvsp[-4],yyvsp[-3]);
             func->adopt(tid);
             yyvsp[-2]->adopt_sym(nullptr,TOK_PARAM);
             yyval = func->adopt (yyvsp[-2],yyvsp[0]);
             destroy(yyvsp[-1]);}
#line 2833 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 73:
#line 260 "parser.y" /* yacc.c:1652  */
    {
           astree* tid = new astree(TOK_TYPE_ID, yyvsp[-1]->lloc,"");
           tid->adopt(yyvsp[-1],yyvsp[0]);
           yyval = yyvsp[-2]->adopt_sym(tid,TOK_PARAM); }
#line 2842 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 74:
#line 264 "parser.y" /* yacc.c:1652  */
    {
           astree* tid = new astree(TOK_TYPE_ID, yyvsp[-1]->lloc,"");
           tid->adopt(yyvsp[-1],yyvsp[0]);
           yyval = yyvsp[-3]->adopt(tid); 
           destroy(yyvsp[-2]); }
#line 2852 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 75:
#line 271 "parser.y" /* yacc.c:1652  */
    { 
         yyval = nullptr; 
         destroy (yyvsp[0]); }
#line 2860 "yyparse.cpp" /* yacc.c:1652  */
    break;

  case 76:
#line 274 "parser.y" /* yacc.c:1652  */
    { yyval = yyvsp[0]; }
#line 2866 "yyparse.cpp" /* yacc.c:1652  */
    break;


#line 2870 "yyparse.cpp" /* yacc.c:1652  */
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
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
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
#line 277 "parser.y" /* yacc.c:1918  */
 

const char* parser::get_tname (int symbol) {
   return yytname [YYTRANSLATE (symbol)];
}

