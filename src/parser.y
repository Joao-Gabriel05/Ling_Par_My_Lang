%{
#include "ast.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* AST raiz definida em parser.c */
Node *root;

/* Flex/Bison */
extern int yylex(void);
extern int yydebug;
void yyerror(const char *s) {
    fprintf(stderr, "Erro sintático: %s\n", s);
}

/* Gerador de código */
extern void codegen(Node *n);
%}

/* Ativa debug e mensagens detalhadas de erro */
%debug
%error-verbose
%start program

/* Precedência para expressões */
/* comparações (mais baixas) */
%left OP_EQ OP_NEQ
%left OP_GT OP_LT OP_GTE OP_LTE
/* soma/subtração binária */
%left OP_PLUS OP_MINUS
/* multiplicação/divisão */
%left OP_MUL  OP_DIV
/* unários (maior precedência que tudo acima) */
%right UMINUS UPLUS


/* Tipos semânticos */
%union {
    int      number;
    char    *string;
    struct Node    *node;
}

/* Tokens com valor */
%token <number> NUMBER
%token <string> IDENTIFIER

/* Demais tokens */
%token KW_REMEMBER KW_AS KW_FORGET
%token KW_IF KW_ELSE
%token KW_WHILE KW_REPEAT KW_RUN
%token KW_SHOW KW_END DOLLAR
%token OP_EQ OP_NEQ OP_GTE OP_LTE OP_GT OP_LT
%token OP_PLUS OP_MINUS OP_MUL OP_DIV
%token LPAREN RPAREN LBRACE RBRACE SEMICOLON

/* Non-terminals que retornam Node* */
%type <node> program stmt_list block_stmts statement block expression term

%%

program
  : stmt_list KW_END SEMICOLON
    { root = $1; }
  ;

/* Lista de statements no nível do programa (pelo menos 1) */
stmt_list
  : statement
    { $$ = new_node(NODE_BLOCK, 1, $1); }
  | stmt_list statement
    {
      int n = $1->child_count;
      $1->children = realloc($1->children, sizeof(struct Node*)*(n+1));
      $1->children[n] = $2;
      $1->child_count = n+1;
      $$ = $1;
    }
  ;

/* Statements dentro de um bloco (zero ou mais) */
block_stmts
  : /* vazio */
    { $$ = new_node(NODE_BLOCK, 0); }
  | block_stmts statement
    {
      int n = $1->child_count;
      $1->children = realloc($1->children, sizeof(struct Node*)*(n+1));
      $1->children[n] = $2;
      $1->child_count = n+1;
      $$ = $1;
    }
  ;

statement
  : KW_REMEMBER IDENTIFIER KW_AS expression SEMICOLON
  {
      /*  Cria um nó IDENT separado, e aloca o lexeme corretamente */
      Node *idNode = new_node(NODE_IDENT, 0);
      idNode->lexeme = strdup($2);

     /* Agora crie o VAR_DECL com o child[0] sendo esse idNode */
      $$ = new_node(NODE_VAR_DECL, 2,
                    idNode,
                    $4);
    }
  | KW_FORGET IDENTIFIER SEMICOLON
    {
      Node *idNode = new_node(NODE_IDENT, 0);
      idNode->lexeme = strdup($2);

      $$ = new_node(NODE_VAR_DEL, 1, idNode);
    }
 | IDENTIFIER KW_AS expression SEMICOLON
   {
     /* redefinição: monta um nó de atribuição */
     Node *idNode = new_node(NODE_IDENT, 0);
     idNode->lexeme = strdup($1);

     /* filho 0 = identificador, filho 1 = expressão */
    $$ = new_node(NODE_ASSIGN, 2, idNode, $3);
   }
  | KW_IF LPAREN expression RPAREN block KW_ELSE block
    { $$ = new_node(NODE_IF, 3, $3, $5, $7); }
  | KW_IF LPAREN expression RPAREN block
    { $$ = new_node(NODE_IF, 2, $3, $5); }
  | KW_WHILE LPAREN expression RPAREN KW_REPEAT block
    { $$ = new_node(NODE_WHILE, 2, $3, $6); }
  | KW_RUN LPAREN expression RPAREN block
    { $$ = new_node(NODE_REPEAT, 2, $3, $5); }
  | KW_SHOW LPAREN expression RPAREN SEMICOLON
    { $$ = new_node(NODE_PRINT, 1, $3); }
  | DOLLAR block DOLLAR
    { $$ = new_node(NODE_DEBUG, 1, $2); }
  ;

block
  : LBRACE block_stmts RBRACE
    { $$ = $2; }
  ;


expression
  /* 1) Caso base */
  : term
    { $$ = $1; }
  /* 2) Unários, com %prec para UMINUS/UPLUS */
  | OP_MINUS expression  %prec UMINUS
    {
      Node *un = new_node(NODE_UNOP, 1, $2);
      un->lexeme = strdup("-");
      $$ = un;
    }
  | OP_PLUS expression   %prec UPLUS
    {
      Node *un = new_node(NODE_UNOP, 1, $2);
      un->lexeme = strdup("+");
      $$ = un;
    }
  /* 3) Binários multiplicativos */
  | expression OP_MUL   expression
    { $$ = new_node(NODE_BINOP, 2, $1, $3); $$->lexeme = "*"; }
  | expression OP_DIV   expression
    { $$ = new_node(NODE_BINOP, 2, $1, $3); $$->lexeme = "/"; }
  /* 4) Binários aditivos */
  | expression OP_PLUS  expression
    { $$ = new_node(NODE_BINOP, 2, $1, $3); $$->lexeme = "+"; }
  | expression OP_MINUS expression
    { $$ = new_node(NODE_BINOP, 2, $1, $3); $$->lexeme = "-"; }
  /* 5) Comparações */
  | expression OP_EQ    expression
    { $$ = new_node(NODE_BINOP, 2, $1, $3); $$->lexeme = "=="; }
  | expression OP_NEQ   expression
    { $$ = new_node(NODE_BINOP, 2, $1, $3); $$->lexeme = "!="; }
  | expression OP_GT    expression
    { $$ = new_node(NODE_BINOP, 2, $1, $3); $$->lexeme = ">";  }
  | expression OP_LT    expression
    { $$ = new_node(NODE_BINOP, 2, $1, $3); $$->lexeme = "<";  }
  | expression OP_GTE   expression
    { $$ = new_node(NODE_BINOP, 2, $1, $3); $$->lexeme = ">="; }
  | expression OP_LTE   expression
    { $$ = new_node(NODE_BINOP, 2, $1, $3); $$->lexeme = "<="; }
  ;

term
  : IDENTIFIER
    { $$ = new_node(NODE_IDENT, 0); $$->lexeme = $1; }
  | NUMBER
    { $$ = new_node(NODE_NUMBER, 0); $$->number = $1; }
  | LPAREN expression RPAREN
    { $$ = $2; }
  ;
%%