#include <stdio.h>
#include <string.h>
#include "ts.h"

#define MAX_TS 100

Simbolo tabela[MAX_TS];
int tamanhoTS = 0;

int existe(char *lexema) {
    for (int i = 0; i < tamanhoTS; i++) {
        if (strcmp(tabela[i].lexema, lexema) == 0)
            return 1;
    }
    return 0;
}

void adicionarSimbolo(char *lexema, TokenType tipo) {
    if (!existe(lexema)) {
        strcpy(tabela[tamanhoTS].lexema, lexema);
        tabela[tamanhoTS].tipo = tipo;
        tamanhoTS++;
    }
}

void salvarTS() {
    FILE *f = fopen("saida.ts", "w");
    fprintf(f, "%-20s %s\n", "Lexema", "Tipo");
    fprintf(f, "%-20s %s\n", "--------------------", "--------------------");
    for (int i = 0; i < tamanhoTS; i++) {
        const char *tipo = (tabela[i].tipo == ID) ? "identificador" : "palavra-reservada";
        fprintf(f, "%-20s %s\n", tabela[i].lexema, tipo);
    }
    fclose(f);
}

void inicializarTS() {
    adicionarSimbolo("program", KW_PROGRAM);
    adicionarSimbolo("var",     KW_VAR);
    adicionarSimbolo("integer", KW_INTEGER);
    adicionarSimbolo("real",    KW_REAL);
    adicionarSimbolo("begin",   KW_BEGIN);
    adicionarSimbolo("end",     KW_END);
    adicionarSimbolo("if",      KW_IF);
    adicionarSimbolo("then",    KW_THEN);
    adicionarSimbolo("else",    KW_ELSE);
    adicionarSimbolo("while",   KW_WHILE);
    adicionarSimbolo("do",      KW_DO);
}
