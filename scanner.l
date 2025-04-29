%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.tab.h"    /* Tokens gerados pelo Bison */

int line_num = 1;       /* Contador de linhas para erros */

/* strdup para sistemas que não têm */
#if !defined(__APPLE__)
char* strdup(const char* s) {
    char* p = malloc(strlen(s) + 1);
    if (p) strcpy(p, s);
    return p;
}
#endif
%}

%option noyywrap

%%


[ \t]+                ;


\n                    { line_num++; }


\/\/.*                ;


"remember"            { return KW_REMEMBER; }
"as"                  { return KW_AS; }
"forget"              { return KW_FORGET; }
"if"                  { return KW_IF; }
"else"                { return KW_ELSE; }
"while"               { return KW_WHILE; }
"repeat"              { return KW_REPEAT; }
"run"                 { return KW_RUN; }
"show"                { return KW_SHOW; }
"end"                 { return KW_END; }


"=="                  { return OP_EQ; }
"!="                  { return OP_NEQ; }
">="                  { return OP_GTE; }
"<="                  { return OP_LTE; }


">"                   { return OP_GT; }
"<"                   { return OP_LT; }
"+"                   { return OP_PLUS; }
"-"                   { return OP_MINUS; }
"*"                   { return OP_MUL; }
"/"                   { return OP_DIV; }


"("                   { return LPAREN; }
")"                   { return RPAREN; }
"{"                   { return LBRACE; }
"}"                   { return RBRACE; }
";"                   { return SEMICOLON; }
"$"                   { return DOLLAR; }


[0-9]+                 { yylval.number = atoi(yytext); return NUMBER; }
[A-Za-z][A-Za-z0-9_]*  { yylval.string = strdup(yytext); return IDENTIFIER; }


.                      { fprintf(stderr, "Linha %d: caractere inválido '%s'\n", line_num, yytext); }

%%

