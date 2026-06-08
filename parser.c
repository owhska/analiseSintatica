#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"
#include "ts.h"

static char  *src;
static int    pos;
static int    cur_linha;
static int    cur_coluna;
static Token  tokenCorrente;
static FILE  *out;

static void programa();
static void bloco();
static void parteDeclaracoesVariaveis();
static void declaracaoVariaveis();
static void listaIdentificadores();
static void tipo();
static void comandoComposto();
static void comando();
static void atribuicao();
static void comandoCondicional();
static void comandoRepetitivo();
static void expressao();
static void relacao();
static void expressaoSimples();
static void termo();
static void fator();
static void variavel();

static void erro(const char *lex) {
    if (strcmp(lex, "EOF") == 0) {
        fprintf(out,    "%d:fim de arquivo nao esperado.\n", tokenCorrente.linha);
        fprintf(stderr, "%d:fim de arquivo nao esperado.\n", tokenCorrente.linha);
    } else {
        fprintf(out,    "%d:token nao esperado [%s].\n", tokenCorrente.linha, lex);
        fprintf(stderr, "%d:token nao esperado [%s].\n", tokenCorrente.linha, lex);
    }
    fclose(out);
    exit(1);
}

static void casaToken(TokenType esperado) {
    if (tokenCorrente.type == esperado)
        tokenCorrente = getNextToken(src, &pos, &cur_linha, &cur_coluna);
    else
        erro(tokenCorrente.lexema);
}

static void programa() {
    fprintf(out, "<programa> ::= program <identificador> ; <bloco> .\n");
    casaToken(KW_PROGRAM);
    casaToken(ID);
    casaToken(SMB_SEM);
    bloco();
    casaToken(SMB_DOT);
}

static void bloco() {
    fprintf(out, "<bloco> ::= <parte-declaracoes> <comando-composto>\n");
    parteDeclaracoesVariaveis();
    comandoComposto();
}

static void parteDeclaracoesVariaveis() {
    if (tokenCorrente.type != KW_VAR)
        return;
    fprintf(out, "<parte-declaracoes> ::= var <declaracao> { ; <declaracao> } ;\n");
    casaToken(KW_VAR);
    declaracaoVariaveis();
    while (tokenCorrente.type == SMB_SEM) {
        casaToken(SMB_SEM);
        if (tokenCorrente.type == KW_BEGIN || tokenCorrente.type == KW_END
                || tokenCorrente.type == SMB_DOT)
            break;
        declaracaoVariaveis();
    }
}

static void declaracaoVariaveis() {
    fprintf(out, "<declaracao> ::= <lista-identificadores> : <tipo>\n");
    listaIdentificadores();
    casaToken(SMB_COL);
    tipo();
}

static void listaIdentificadores() {
    fprintf(out, "<lista-identificadores> ::= %s", tokenCorrente.lexema);
    casaToken(ID);
    while (tokenCorrente.type == SMB_COM) {
        casaToken(SMB_COM);
        fprintf(out, ", %s", tokenCorrente.lexema);
        casaToken(ID);
    }
    fprintf(out, "\n");
}

static void tipo() {
    if (tokenCorrente.type == KW_INTEGER) {
        fprintf(out, "<tipo> ::= integer\n");
        casaToken(KW_INTEGER);
    } else if (tokenCorrente.type == KW_REAL) {
        fprintf(out, "<tipo> ::= real\n");
        casaToken(KW_REAL);
    } else {
        erro(tokenCorrente.lexema);
    }
}

static void comandoComposto() {
    fprintf(out, "<comando-composto> ::= begin <comando> { ; <comando> } end\n");
    casaToken(KW_BEGIN);
    comando();
    while (tokenCorrente.type == SMB_SEM) {
        casaToken(SMB_SEM);
        if (tokenCorrente.type == KW_END)
            break;
        comando();
    }
    casaToken(KW_END);
}

static void comando() {
    if (tokenCorrente.type == ID)
        atribuicao();
    else if (tokenCorrente.type == KW_BEGIN)
        comandoComposto();
    else if (tokenCorrente.type == KW_IF)
        comandoCondicional();
    else if (tokenCorrente.type == KW_WHILE)
        comandoRepetitivo();
    else
        erro(tokenCorrente.lexema);
}

static void atribuicao() {
    fprintf(out, "<atribuicao> ::= %s := <expressao>\n", tokenCorrente.lexema);
    variavel();
    casaToken(OP_ASS);
    expressao();
}

static void comandoCondicional() {
    fprintf(out, "<comando-condicional> ::= if <expressao> then <comando>\n");
    casaToken(KW_IF);
    expressao();
    casaToken(KW_THEN);
    comando();
    if (tokenCorrente.type == KW_ELSE) {
        fprintf(out, "else <comando>\n");
        casaToken(KW_ELSE);
        comando();
    }
}

static void comandoRepetitivo() {
    fprintf(out, "<comando-repetitivo> ::= while <expressao> do <comando>\n");
    casaToken(KW_WHILE);
    expressao();
    casaToken(KW_DO);
    comando();
}

static void expressao() {
    expressaoSimples();
    if (tokenCorrente.type == OP_EQ || tokenCorrente.type == OP_NE ||
        tokenCorrente.type == OP_LT || tokenCorrente.type == OP_LE ||
        tokenCorrente.type == OP_GT || tokenCorrente.type == OP_GE) {
        relacao();
        expressaoSimples();
    }
}

static void relacao() {
    fprintf(out, "<relacao> ::= %s\n", tokenCorrente.lexema);
    TokenType t = tokenCorrente.type;
    if (t == OP_EQ || t == OP_NE || t == OP_LT ||
        t == OP_LE || t == OP_GT || t == OP_GE)
        casaToken(t);
    else
        erro(tokenCorrente.lexema);
}

static void expressaoSimples() {
    if (tokenCorrente.type == OP_AD)
        casaToken(OP_AD);
    else if (tokenCorrente.type == OP_MIN)
        casaToken(OP_MIN);
    termo();
    while (tokenCorrente.type == OP_AD || tokenCorrente.type == OP_MIN) {
        TokenType t = tokenCorrente.type;
        casaToken(t);
        termo();
    }
}

static void termo() {
    fator();
    while (tokenCorrente.type == OP_MUL || tokenCorrente.type == OP_DIV) {
        TokenType t = tokenCorrente.type;
        casaToken(t);
        fator();
    }
}

static void fator() {
    if (tokenCorrente.type == ID) {
        variavel();
    } else if (tokenCorrente.type == NUM_INT) {
        fprintf(out, "<fator> ::= %s\n", tokenCorrente.lexema);
        casaToken(NUM_INT);
    } else if (tokenCorrente.type == NUM_REAL) {
        fprintf(out, "<fator> ::= %s\n", tokenCorrente.lexema);
        casaToken(NUM_REAL);
    } else if (tokenCorrente.type == SMB_OPA) {
        casaToken(SMB_OPA);
        expressao();
        casaToken(SMB_CPA);
    } else {
        erro(tokenCorrente.lexema);
    }
}

static void variavel() {
    fprintf(out, "<variavel> ::= %s\n", tokenCorrente.lexema);
    casaToken(ID);
}

int parse(char *codigo) {
    src        = codigo;
    pos        = 0;
    cur_linha  = 1;
    cur_coluna = 1;

    out = fopen("saida.sin", "w");
    if (!out) {
        fprintf(stderr, "Erro ao abrir saida.sin\n");
        return 1;
    }

    inicializarTS();
    tokenCorrente = getNextToken(src, &pos, &cur_linha, &cur_coluna);
    programa();

    if (tokenCorrente.type != ERRO || strcmp(tokenCorrente.lexema, "EOF") != 0) {
        fprintf(out,    "%d:token nao esperado [%s].\n", tokenCorrente.linha, tokenCorrente.lexema);
        fprintf(stderr, "%d:token nao esperado [%s].\n", tokenCorrente.linha, tokenCorrente.lexema);
        fclose(out);
        return 1;
    }

    fprintf(out, "ok\n");
    fclose(out);
    return 0;
}
