#ifndef TS_H
#define TS_H

#include "token.h"

typedef struct{
    char lexema[100];
    TokenType tipo;
} Simbolo;

void adicionarSimbolo(char *lexema, TokenType tipo);
void salvarTS();
void inicializarTS();

#endif

