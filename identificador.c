#include <ctype.h>
#include <string.h>
#include "token.h"
#include "identificador.h"

int reconhecerIdentificador(char *str){
    
    if (!isalpha(str[0]))
        return 0;

    for (int i = 0; str[i] != '\0'; i++){
        if (!isalnum(str[i]))
            return 0;
    }

    return 1;

}

void toLowerCase(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

TokenType verificarPalavraReservada(char *str) {

    toLowerCase(str);

    if (strcmp(str, "program") == 0) return KW_PROGRAM;
    if (strcmp(str, "var") == 0) return KW_VAR;
    if (strcmp(str, "integer") == 0) return KW_INTEGER;
    if (strcmp(str, "real") == 0) return KW_REAL;
    if (strcmp(str, "begin") == 0) return KW_BEGIN;
    if (strcmp(str, "end") == 0) return KW_END;
    if (strcmp(str, "if") == 0) return KW_IF;
    if (strcmp(str, "then") == 0) return KW_THEN;
    if (strcmp(str, "else") == 0) return KW_ELSE;
    if (strcmp(str, "while") == 0) return KW_WHILE;
    if (strcmp(str, "do") == 0) return KW_DO;

    return ID;
}
