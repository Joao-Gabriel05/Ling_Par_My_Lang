#include "ast.h"
#include <stdarg.h>

Node *new_node(NodeKind kind, int child_count, ...) {
    Node *n = malloc(sizeof(Node));
    n->kind = kind;
    n->child_count = child_count;
    n->children = child_count
        ? malloc(sizeof(Node*) * child_count)
        : NULL;
    n->lexeme = NULL;
    n->number = 0;
    va_list ap; va_start(ap, child_count);
    for(int i=0;i<child_count;i++){
        n->children[i] = va_arg(ap, Node*);
    }
    va_end(ap);
    return n;
}

void free_node(Node *n) {
    if (!n) return;
    for(int i=0;i<n->child_count;i++)
        free_node(n->children[i]);
    free(n->children);
    if (n->lexeme) free(n->lexeme);
    free(n);
}
