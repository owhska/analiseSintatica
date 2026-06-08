#include <string.h>
#include "operadores.h"

TokenType reconhecerOperador(char *str){
    
    // ops de 2 caracteres
    if (strcmp(str, ":=") == 0) return OP_ASS;
    if (strcmp(str, "<=") == 0) return OP_LE;
    if (strcmp(str, ">=") == 0) return OP_GE;
    if (strcmp(str, "<>") == 0) return OP_NE;

    // ops de 1 caractere
    if (strcmp(str, "=") == 0) return OP_EQ;
    if (strcmp(str, "<") == 0) return OP_LT;
    if (strcmp(str, ">") == 0) return OP_GT;
    if (strcmp(str, "+") == 0) return OP_AD;
    if (strcmp(str, "-") == 0) return OP_MIN;
    if (strcmp(str, "*") == 0) return OP_MUL;
    if (strcmp(str, "/") == 0) return OP_DIV;

    // simbolos
    if (strcmp(str, ";") == 0) return SMB_SEM;
    if (strcmp(str, ",") == 0) return SMB_COM;
    if (strcmp(str, "(") == 0) return SMB_OPA;
    if (strcmp(str, ")") == 0) return SMB_CPA;
    if (strcmp(str, ":") == 0) return SMB_COL;
    if (strcmp(str, ".") == 0) return SMB_DOT;
    if (strcmp(str, "{") == 0) return SMB_OBC;
    if (strcmp(str, "}") == 0) return SMB_CBC;

    return ERRO;

}
