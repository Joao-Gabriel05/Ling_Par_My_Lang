#include "ast.h"

static int indent = 0;
static void emit_indent() {
    for(int i=0;i<indent;i++) putchar(' ');
}

void codegen(Node *n) {
    if (!n) return;
    switch(n->kind) {
    case NODE_VAR_DECL:
        emit_indent();
        printf("int %s = ", n->children[0]->lexeme);
        codegen(n->children[1]);
        printf(";\n");
        break;
    case NODE_VAR_DEL:
        emit_indent();
        printf("/* forget %s */\n", n->children[0]->lexeme);
        break;
    case NODE_PRINT:
        emit_indent();
        printf("printf(\"%%d\\n\", ");
        codegen(n->children[0]);
        printf(");\n");
        break;
    case NODE_IF:
        emit_indent();
        printf("if (");
        codegen(n->children[0]);
        printf(") {\n");
        indent += 2;
        codegen(n->children[1]);
        indent -= 2;
        if (n->child_count == 3) {
            emit_indent(); printf("} else {\n");
            indent += 2;
            codegen(n->children[2]);
            indent -= 2;
        }
        emit_indent(); printf("}\n");
        break;
    case NODE_WHILE:
        emit_indent();
        printf("while (");
        codegen(n->children[0]);
        printf(") {\n");
        indent+=2;
        codegen(n->children[1]);
        indent-=2;
        emit_indent(); printf("}\n");
        break;
    case NODE_REPEAT:
        emit_indent();
        printf("for(int i=0; i<");
        codegen(n->children[0]);
        printf("; i++) {\n");
        indent+=2;
        codegen(n->children[1]);
        indent-=2;
        emit_indent(); printf("}\n");
        break;

    case NODE_DEBUG: {
        emit_indent();
        printf("printf(\"[DEBUG] Entering debug block\\n\");\n");
        Node *block = n->children[0];
        for (int i = 0; i < block->child_count; i++) {
            Node *stmt = block->children[i];
            switch (stmt->kind) {
                case NODE_VAR_DECL: {
                    char *name = stmt->children[0]->lexeme;
                    Node *expr = stmt->children[1];
                    emit_indent();
                    printf("int %s = ", name);
                    codegen(expr);
                    printf(";\n");
                    emit_indent();
                    printf("printf(\"Line %d: remember %s as %%d\\n\", %s);\n", i+1, name, name);
                    break;
                }
                case NODE_ASSIGN: {
                    char *name = stmt->children[0]->lexeme;
                    Node *expr = stmt->children[1];
                    emit_indent();
                    printf("%s = ", name);
                    codegen(expr);
                    printf(";\n");
                    emit_indent();
                    printf("printf(\"Line %d: %s = %%d\\n\", %s);\n", i+1, name, name);
                    break;
                }
                case NODE_PRINT: {
                    emit_indent();
                    printf("printf(\"Line %d: show = %%d\\n\", ", i+1);
                    codegen(stmt->children[0]);
                    printf(");\n");
                    break;
                }
                case NODE_IF: {
                    Node *cond = stmt->children[0];
                    emit_indent();
                    printf("printf(\"Line %d: condition result = %%d\\n\", (", i+1);
                    codegen(cond);
                    printf("));\n");
                    codegen(stmt);
                    break;
                }
                case NODE_WHILE: {
                    Node *cond = stmt->children[0];
                    // print current variable and result of condition
                    emit_indent();
                    printf("printf(\"Line %d: ", i+1);
                    // left side of condition
                    codegen(cond->children[0]);
                    printf(" = %%d, ");
                    // full condition
                    codegen(cond);
                    printf(" = %%d\\n\", ");
                    // arguments: var value, condition result
                    codegen(cond->children[0]); printf(", "); codegen(cond);
                    printf(");\n");
                    // now actually generate the while
                    codegen(stmt);
                    break;
                }
                default: {
                    codegen(stmt);
                    break;
                }
            }
        }
        emit_indent();
        printf("printf(\"[DEBUG] Exiting debug block\\n\");\n");
        break;
    }
    case NODE_BLOCK:
        for(int i=0;i<n->child_count;i++)
            codegen(n->children[i]);
        break;
    case NODE_BINOP:
        codegen(n->children[0]);
        printf(" %s ", n->lexeme);
        codegen(n->children[1]);
        break;
    case NODE_UNOP: {
            // unário: imprime algo como "(-expr)" ou "(+expr)"
            emit_indent();
            printf("(");
            printf("%s", n->lexeme);
            codegen(n->children[0]);
            printf(")");
            break;
        }
    case NODE_NUMBER:
        printf("%d", n->number);
        break;
    case NODE_IDENT:
        printf("%s", n->lexeme);
        break;
    case NODE_ASSIGN: {
            Node *id = n->children[0];
            Node *expr = n->children[1];
            printf("    %s = ", id->lexeme);
            codegen(expr);
            printf(";\n");
            break;
        }
    }
}
