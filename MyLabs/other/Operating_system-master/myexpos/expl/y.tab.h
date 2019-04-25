/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    NUM = 258,
    ID = 259,
    PLUS = 260,
    MUL = 261,
    DIV = 262,
    MOD = 263,
    ASGN = 264,
    READ = 265,
    WRITE = 266,
    MINUS = 267,
    NEWLINE = 268,
    LT = 269,
    GT = 270,
    DEQ = 271,
    NEQ = 272,
    ELSE = 273,
    IF = 274,
    THEN = 275,
    ENDIF = 276,
    ENDWHILE = 277,
    WHILE = 278,
    DO = 279,
    START = 280,
    END = 281,
    DECL = 282,
    ENDDECL = 283,
    INT = 284,
    STR = 285,
    LE = 286,
    GE = 287,
    NOT = 288,
    AND = 289,
    OR = 290,
    MAIN = 291,
    RETURN = 292,
    ALLOC = 293,
    FREE = 294,
    INIT = 295,
    BRK = 296,
    CONTINUE = 297,
    BRKP = 298,
    TYPE = 299,
    ENDTYPE = 300,
    NILL = 301,
    DEQNILL = 302,
    NEQNILL = 303,
    STRVAL = 304,
    EXPOSCALL = 305
  };
#endif
/* Tokens.  */
#define NUM 258
#define ID 259
#define PLUS 260
#define MUL 261
#define DIV 262
#define MOD 263
#define ASGN 264
#define READ 265
#define WRITE 266
#define MINUS 267
#define NEWLINE 268
#define LT 269
#define GT 270
#define DEQ 271
#define NEQ 272
#define ELSE 273
#define IF 274
#define THEN 275
#define ENDIF 276
#define ENDWHILE 277
#define WHILE 278
#define DO 279
#define START 280
#define END 281
#define DECL 282
#define ENDDECL 283
#define INT 284
#define STR 285
#define LE 286
#define GE 287
#define NOT 288
#define AND 289
#define OR 290
#define MAIN 291
#define RETURN 292
#define ALLOC 293
#define FREE 294
#define INIT 295
#define BRK 296
#define CONTINUE 297
#define BRKP 298
#define TYPE 299
#define ENDTYPE 300
#define NILL 301
#define DEQNILL 302
#define NEQNILL 303
#define STRVAL 304
#define EXPOSCALL 305

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 33 "abstree.y" /* yacc.c:1909  */

    struct ASTNode *nptr;

#line 158 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
