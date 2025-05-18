#ifndef AST_H
#define AST_H

#include <stdlib.h>
#include <stdio.h>

typedef enum {
    NODE_VAR_DECL, NODE_VAR_DEL,
    NODE_IF, NODE_WHILE, NODE_REPEAT,
    NODE_PRINT, NODE_DEBUG,
    NODE_ASSIGN,
    NODE_BLOCK, NODE_BINOP, NODE_UNOP, NODE_NUMBER, NODE_IDENT
} NodeKind;

typedef struct Node {
    NodeKind kind;
    struct Node **children;   // vetor de ponteiros para filhos
    int child_count;
    char *lexeme;             // para IDENT
    int number;               // para NUMBER
} Node;

// Helpers para criar nós
Node *new_node(NodeKind kind, int child_count, ...);
void free_node(Node *n);

#endif // AST_H
