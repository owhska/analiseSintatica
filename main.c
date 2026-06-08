#include <stdio.h>
#include <string.h>
#include "token.h"
#include "ts.h"
#include "parser.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <arquivo.pac>\n", argv[0]);
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (!f) {
        printf("Erro ao abrir arquivo: %s\n", argv[1]);
        return 1;
    }

    char codigo[20000];
    int tamanho = fread(codigo, 1, sizeof(codigo) - 1, f);
    codigo[tamanho] = '\0';
    fclose(f);

    printf("| analise: %s |\n", argv[1]);
    int resultado = parse(codigo);

    if (resultado == 0)
        printf("Programa aceito. Regras salvas em saida.sin\n");
    else
        printf("Programa rejeitado.\n");

    return resultado;
}
