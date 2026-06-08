#ifndef LEXER_H
#define LEXER_H

#include "token.h"

Token getNextToken(char *entrada, int *i, int *linha, int *coluna);

#endif
