/* A Bison parser, made by GNU Bison 2.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C

   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006
   Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street, Fifth Floor,
   Boston, MA 02110-1301, USA.  */

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

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     OP_NEQ = 258,
     OP_EQ = 259,
     OP_LTE = 260,
     OP_GTE = 261,
     OP_LT = 262,
     OP_GT = 263,
     OP_MINUS = 264,
     OP_PLUS = 265,
     OP_DIV = 266,
     OP_MUL = 267,
     UPLUS = 268,
     UMINUS = 269,
     NUMBER = 270,
     IDENTIFIER = 271,
     KW_REMEMBER = 272,
     KW_AS = 273,
     KW_FORGET = 274,
     KW_IF = 275,
     KW_ELSE = 276,
     KW_WHILE = 277,
     KW_REPEAT = 278,
     KW_RUN = 279,
     KW_SHOW = 280,
     KW_END = 281,
     DOLLAR = 282,
     LPAREN = 283,
     RPAREN = 284,
     LBRACE = 285,
     RBRACE = 286,
     SEMICOLON = 287
   };
#endif
/* Tokens.  */
#define OP_NEQ 258
#define OP_EQ 259
#define OP_LTE 260
#define OP_GTE 261
#define OP_LT 262
#define OP_GT 263
#define OP_MINUS 264
#define OP_PLUS 265
#define OP_DIV 266
#define OP_MUL 267
#define UPLUS 268
#define UMINUS 269
#define NUMBER 270
#define IDENTIFIER 271
#define KW_REMEMBER 272
#define KW_AS 273
#define KW_FORGET 274
#define KW_IF 275
#define KW_ELSE 276
#define KW_WHILE 277
#define KW_REPEAT 278
#define KW_RUN 279
#define KW_SHOW 280
#define KW_END 281
#define DOLLAR 282
#define LPAREN 283
#define RPAREN 284
#define LBRACE 285
#define RBRACE 286
#define SEMICOLON 287




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 39 "src/parser.y"
{
    int      number;
    char    *string;
    struct Node    *node;
}
/* Line 1529 of yacc.c.  */
#line 119 "parser.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

