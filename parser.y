%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
void yyerror(const char *s) { fprintf(stderr, "Erro sintático: %s\n", s); }
%}

/* ---- Volta o %union, mas só com int e char* ---- */
%union {
  int   number;
  char* string;
}

/* ---- Declare agora seus tokens com tipo associado ---- */
%token <number> NUMBER
%token <string> IDENTIFIER

/* os demais tokens sem tipo ficam normais */
%token KW_REMEMBER KW_AS KW_FORGET KW_IF KW_ELSE KW_WHILE KW_REPEAT KW_RUN KW_SHOW KW_END
%token OP_EQ OP_NEQ OP_GTE OP_LTE OP_GT OP_LT OP_PLUS OP_MINUS OP_MUL OP_DIV
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON DOLLAR

%%

program:
      statements KW_END SEMICOLON
    {
      printf("Parse concluído com sucesso!\n");
    }
  ;

statements:
      /* vazio */
    | statements statement
  ;

statement:
      KW_REMEMBER IDENTIFIER KW_AS expression SEMICOLON
    | KW_FORGET   IDENTIFIER                 SEMICOLON
    | KW_IF       LPAREN expression RPAREN block
    | KW_IF       LPAREN expression RPAREN block KW_ELSE block
    | KW_WHILE    LPAREN expression RPAREN KW_REPEAT block
    | KW_RUN      LPAREN NUMBER     RPAREN block
    | KW_SHOW     LPAREN expression RPAREN SEMICOLON
    | DOLLAR      block               DOLLAR
  ;

block:
      LBRACE statements RBRACE
  ;

expression:
      term
    | expression OP_PLUS  term
    | expression OP_MINUS term
    | expression OP_MUL   term
    | expression OP_DIV   term
    | expression OP_EQ    term
    | expression OP_NEQ   term
    | expression OP_GT    term
    | expression OP_LT    term
    | expression OP_GTE   term
    | expression OP_LTE   term
  ;

term:
      IDENTIFIER
    | NUMBER
    | LPAREN expression RPAREN
  ;

%%

int main(void) {
    return yyparse();
}
