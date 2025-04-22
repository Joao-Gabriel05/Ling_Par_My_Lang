%{
#include <stdio.h>
#include <stdlib.h>
%}

/* união de valores semânticos */
%union {
  int    number;
  char*  string;
}

%token KW_REMEMBER KW_AS KW_FORGET KW_IF KW_ELSE KW_WHILE KW_REPEAT KW_RUN KW_SHOW KW_END
%token OP_EQ OP_NEQ OP_GTE OP_LTE OP_GT OP_LT OP_PLUS OP_MINUS OP_MUL OP_DIV
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON DOLLAR
%token <string> IDENTIFIER
%token <number> NUMBER

%type <number> expression term

%left OP_EQ OP_NEQ OP_GT OP_LT OP_GTE OP_LTE
%left OP_PLUS OP_MINUS
%left OP_MUL OP_DIV

%%

programa:
    statements KW_END SEMICOLON
  ;

statements:
  | statements statement
  ;

statement:
    create_variable
  | delete_variable
  | conditional
  | loop
  | repeat_n_times
  | print
  | debug_block
  | SEMICOLON          
  ;

create_variable:
    KW_REMEMBER IDENTIFIER KW_AS expression SEMICOLON
  ;

delete_variable:
    KW_FORGET IDENTIFIER SEMICOLON
  ;

conditional:
    KW_IF LPAREN expression RPAREN block
  | KW_IF LPAREN expression RPAREN block KW_ELSE LPAREN expression RPAREN block
  ;

loop:
    KW_WHILE LPAREN expression RPAREN KW_REPEAT block
  ;

repeat_n_times:
    KW_RUN LPAREN NUMBER RPAREN block
  ;

print:
    KW_SHOW LPAREN expression RPAREN SEMICOLON
  ;

debug_block:
    DOLLAR statements DOLLAR
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

void yyerror(const char *s) {
    fprintf(stderr, "Erro de sintaxe: %s\n", s);
}
