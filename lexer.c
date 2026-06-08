#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "afd_numero.h"
#include "identificador.h"
#include "operadores.h"
#include "ts.h"

Token getNextToken(char *entrada, int *i, int *linha, int *coluna) {

    Token t;
    int j = 0;
    char buffer[100];

    while (isspace(entrada[*i]) || entrada[*i] == '{') {

        if (isspace(entrada[*i])) {
            if (entrada[*i] == '\n') {
                (*linha)++;
                (*coluna) = 1;
            } else {
                (*coluna)++;
            }
            (*i)++;
        }

        else if (entrada[*i] == '{') {
            (*i)++;
            (*coluna)++;

            while (entrada[*i] != '}' && entrada[*i] != '\0') {

                if (entrada[*i] == '\n') {
                    (*linha)++;
                    (*coluna) = 1;
                } else {
                    (*coluna)++;
                }

                (*i)++;
            }

            if (entrada[*i] == '\0') {
                t.linha = *linha;
                t.coluna = *coluna;
                t.type = ERRO;
                strcpy(t.lexema, "comentario nao fechado");
                return t;
            }

            if (entrada[*i] == '}') {
                (*i)++;
                (*coluna)++;
            }
        }
    }

    t.linha = *linha;
    t.coluna = *coluna;

    if (entrada[*i] == '\0') {
        t.type = ERRO;
        strcpy(t.lexema, "EOF");
        return t;
    }

    char c = entrada[*i];


    if (isdigit(c)) {
        while (isdigit(entrada[*i]) || entrada[*i] == '.' || entrada[*i] == 'E'
                || ((entrada[*i] == '+' || entrada[*i] == '-') && j > 0 && buffer[j-1] == 'E')) {
            buffer[j++] = entrada[*i];
            (*i)++;
            (*coluna)++;
        }
        buffer[j] = '\0';

        int result = reconhecerNumeros(buffer);
        if (result == 2)
            t.type = NUM_REAL;
        else if (result == 1)
            t.type = NUM_INT;
        else
            t.type = ERRO;

        strcpy(t.lexema, buffer);
        return t;
    }

    if (isalpha(c)) {
        while (isalnum(entrada[*i])) {
            buffer[j++] = entrada[*i];
            (*i)++;
            (*coluna)++;  // <-- linha adicionada
        }
        buffer[j] = '\0';

        t.type = verificarPalavraReservada(buffer);
        strcpy(t.lexema, buffer);
        adicionarSimbolo(buffer, t.type);
        return t;
    }

    if (c == ':' && entrada[*i + 1] == '=') {
        strcpy(t.lexema, ":=");
        t.type = OP_ASS;
        *i += 2;
        return t;
    }

    if (c == '<' && entrada[*i + 1] == '=') {
        strcpy(t.lexema, "<=");
        t.type = OP_LE;
        *i += 2;
        return t;
    }

    if (c == '>' && entrada[*i + 1] == '=') {
        strcpy(t.lexema, ">=");
        t.type = OP_GE;
        *i += 2;
        return t;
    }

    if (c == '<' && entrada[*i + 1] == '>') {
        strcpy(t.lexema, "<>");
        t.type = OP_NE;
        *i += 2;
        return t;
    }

    buffer[0] = c;
    buffer[1] = '\0';

    t.type = reconhecerOperador(buffer);
    strcpy(t.lexema, buffer);

    (*i)++; 

    return t;
}
