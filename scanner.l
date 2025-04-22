%{
#include "parser.tab.h"  
%}

/* definições de padrões */
DIGIT    [0-9]
LETTER   [A-Za-z]
ID       {LETTER}({LETTER}|{DIGIT}|_)*
NUM      {DIGIT}+

%%

/* palavras‑reservadas */
"remember"       return KW_REMEMBER;
"as"             return KW_AS;
"forget"         return KW_FORGET;
"if"             return KW_IF;
"else"           return KW_ELSE;
"while"          return KW_WHILE;
"repeat"         return KW_REPEAT;
"run"            return KW_RUN;
"show"           return KW_SHOW;
"end"            return KW_END;

/* operadores duplos primeiro */
"=="             return OP_EQ;
"!="             return OP_NEQ;
">="             return OP_GTE;
"<="             return OP_LTE;

/* operadores simples */
">"              return OP_GT;
"<"              return OP_LT;
"+"              return OP_PLUS;
"-"              return OP_MINUS;
"*"              return OP_MUL;
"/"              return OP_DIV;

/* pontuação */
"("              return LPAREN;
")"              return RPAREN;
"{"              return LBRACE;
"}"              return RBRACE;
";"              return SEMICOLON;
"$"              return DOLLAR;

/* identificadores e números */
{ID}             { yylval.string = strdup(yytext); return IDENTIFIER; }
{NUM}            { yylval.number = atoi(yytext);    return NUMBER; }

/* ignorar espaços em branco */
[ \t\r\n]+       ;

/* caractere inesperado */
.                { fprintf(stderr, "Caracter inválido: '%s'\n", yytext); }

%%

int yywrap(void) { return 1; }
