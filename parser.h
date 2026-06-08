#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "lexer.h"

/* Inicializa o parser com o código-fonte e executa a análise sintática.
 * Retorna 0 se o programa for sintaticamente correto, 1 caso contrário. */
int parse(char *codigo);

#endif
