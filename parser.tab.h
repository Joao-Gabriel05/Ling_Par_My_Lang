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
     NUMBER = 258,
     IDENTIFIER = 259,
     KW_REMEMBER = 260,
     KW_AS = 261,
     KW_FORGET = 262,
     KW_IF = 263,
     KW_ELSE = 264,
     KW_WHILE = 265,
     KW_REPEAT = 266,
     KW_RUN = 267,
     KW_SHOW = 268,
     KW_END = 269,
     OP_EQ = 270,
     OP_NEQ = 271,
     OP_GTE = 272,
     OP_LTE = 273,
     OP_GT = 274,
     OP_LT = 275,
     OP_PLUS = 276,
     OP_MINUS = 277,
     OP_MUL = 278,
     OP_DIV = 279,
     LPAREN = 280,
     RPAREN = 281,
     LBRACE = 282,
     RBRACE = 283,
     SEMICOLON = 284,
     DOLLAR = 285
   };
#endif
/* Tokens.  */
#define NUMBER 258
#define IDENTIFIER 259
#define KW_REMEMBER 260
#define KW_AS 261
#define KW_FORGET 262
#define KW_IF 263
#define KW_ELSE 264
#define KW_WHILE 265
#define KW_REPEAT 266
#define KW_RUN 267
#define KW_SHOW 268
#define KW_END 269
#define OP_EQ 270
#define OP_NEQ 271
#define OP_GTE 272
#define OP_LTE 273
#define OP_GT 274
#define OP_LT 275
#define OP_PLUS 276
#define OP_MINUS 277
#define OP_MUL 278
#define OP_DIV 279
#define LPAREN 280
#define RPAREN 281
#define LBRACE 282
#define RBRACE 283
#define SEMICOLON 284
#define DOLLAR 285




#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE
#line 9 "parser.y"
{
  int   number;
  char* string;
}
/* Line 1529 of yacc.c.  */
#line 114 "parser.tab.h"
	YYSTYPE;
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE yylval;

