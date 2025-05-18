#include <stdio.h>
#include <stdlib.h>
#include "ast.h"

/* Declarações do Bison e Flex */
extern int yyparse();
extern FILE* yyin;
extern Node* root;

/* Geração de código */
extern void codegen(Node* n);

int main(int argc, char** argv) {
    FILE* input_file;
    
    /* Verifica argumentos */
    if (argc != 2) {
        fprintf(stderr, "Uso: %s arquivo.easylang\n", argv[0]);
        return 1;
    }
    
    /* Abre o arquivo de entrada */
    input_file = fopen(argv[1], "r");
    if (!input_file) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", argv[1]);
        return 1;
    }
    
    fprintf(stderr, "DEBUG: Arquivo aberto com sucesso\n");
    
    /* Define o arquivo como entrada para o Flex */
    yyin = input_file;
    
    /* Executa o parser */
    fprintf(stderr, "DEBUG: Iniciando análise sintática...\n");
    int result = yyparse();
    if (result != 0) {
        fprintf(stderr, "Erro na análise sintática\n");
        fclose(input_file);
        return 1;
    }
    
    fprintf(stderr, "DEBUG: Análise sintática concluída com sucesso\n");
    
    /* Verifica se temos uma AST válida */
    if (root == NULL) {
        fprintf(stderr, "AST nula após análise sintática\n");
        fclose(input_file);
        return 1;
    }
    
    fprintf(stderr, "DEBUG: AST construída com sucesso\n");
    
    /* Cria o arquivo de saída */
    FILE* out = fopen("out.c", "w");
    if (!out) {
        fprintf(stderr, "Erro ao criar arquivo de saída\n");
        fclose(input_file);
        return 1;
    }
    
    fprintf(stderr, "DEBUG: Arquivo de saída criado\n");
    
    /* Redireciona stdout para o arquivo */
    FILE* old_stdout = stdout;
    stdout = out;
    
    /* Gera o código */
    fprintf(stderr, "DEBUG: Iniciando geração de código...\n");
    
    printf("/* Código gerado pelo compilador EasyLang */\n");
    printf("#include <stdio.h>\n\n");
    printf("int main() {\n");
    
    /* Chama o gerador de código */
    if (root) {
        fprintf(stderr, "DEBUG: Chamando codegen para nó raiz tipo %d com %d filhos\n", 
                root->kind, root->child_count);
        codegen(root);
    }
    
    printf("    return 0;\n");
    printf("}\n");
    
    /* Restaura stdout e fecha o arquivo */
    fclose(out);
    stdout = old_stdout;
    
    fprintf(stderr, "DEBUG: Geração de código concluída\n");
    
    /* Fecha o arquivo de entrada */
    fclose(input_file);
    
    fprintf(stderr, "DEBUG: Compilando o código gerado...\n");
    system("gcc -o programa out.c");
    fprintf(stderr, "DEBUG: Executando o programa gerado...\n");
    system("./programa");
    
    return 0;
}