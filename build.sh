#!/usr/bin/env bash
set -e

# 1) Bison primeiro: atualiza parser.c e parser.tab.h
bison -d -v -o parser.c src/parser.y


# 2) Agora sim o scanner: inclui o parser.tab.h fresquinho
flex -o scanner.c src/scanner.l

# 3) Compila tudo junto
gcc -I src -o easylang \
    parser.c scanner.c \
    src/ast.c src/codegen.c \
    src/main.c

echo "✔️ Build concluído: ./easylang"
