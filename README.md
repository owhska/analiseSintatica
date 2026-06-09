# Analisador Sintático — MicroPascal

Trabalho prático da disciplina de Linguagens Formais, Autômatos e Compiladores — UCB, 1° semestre de 2026.

Implementa um analisador sintático para a linguagem **MicroPascal (µ-Pascal)** em C, pelo método de **análise descendente recursiva**. Cada símbolo não-terminal da gramática BNF corresponde a uma função em C.

> O código do analisador léxico desenvolvido anteriormente ([owhska/analiseLexica](https://github.com/owhska/analiseLexica)) foi usado como base. Os módulos `lexer`, `token`, `afd_numero`, `identificador`, `operadores` e `ts` foram reaproveitados integralmente.

## Arquivos

| Arquivo             | Descrição                                                        |
| ------------------- | ---------------------------------------------------------------- |
| `main.c`            | Ponto de entrada, lê o arquivo fonte e chama `parse()`           |
| `parser.c/h`        | Analisador sintático — `casaToken()` e todos os não-terminais    |
| `lexer.c/h`         | Função `getNextToken()` — fornece tokens ao parser               |
| `afd_numero.c/h`    | AFD para reconhecimento de inteiros, reais e notação científica  |
| `identificador.c/h` | Reconhecimento de identificadores e palavras reservadas          |
| `operadores.c/h`    | Reconhecimento de operadores e símbolos                          |
| `token.c/h`         | Struct `Token` e enum `TokenType`                                |
| `ts.c/h`            | Tabela de Símbolos                                               |

## Compilar e executar

```
gcc main.c afd_numero.c identificador.c operadores.c lexer.c token.c ts.c parser.c -o parser

./parser <arquivo.pac>
```

Ou com o Makefile:

```
make
./parser <arquivo.pac>
```

## Saída gerada

- `saida.sin` — sequência de regras de produção utilizadas na análise, ou mensagem de erro

## Formato das mensagens de erro

```
nn:token nao esperado [lex].
nn:fim de arquivo nao esperado.
```

onde `nn` é o número da linha e `lex` é o lexema encontrado. A mensagem é impressa em `saida.sin` e em `stderr`.

## Exemplo de saída (programa correto)

```
<programa> ::= program <identificador> ; <bloco> .
<bloco> ::= <parte-declaracoes> <comando-composto>
<parte-declaracoes> ::= var <declaracao> { ; <declaracao> } ;
<declaracao> ::= <lista-identificadores> : <tipo>
<lista-identificadores> ::= x, y
<tipo> ::= integer
<comando-composto> ::= begin <comando> { ; <comando> } end
<atribuicao> ::= x := <expressao>
<variavel> ::= x
<expressao> ::= <expressao-simples> [ <relacao> <expressao-simples> ]
<expressao-simples> ::= [ +|- ] <termo> { (+|-) <termo> }
<termo> ::= <fator> { (*|/) <fator> }
<fator> ::= 10
...
ok
```

## Gramática (MicroPascal)

```
<programa>     ::= program <identificador> ; <bloco> .
<bloco>        ::= <parte-declaracoes> <comando-composto>
<parte-declaracoes> ::= { var <declaracao> { ; <declaracao> } ; }
<declaracao>   ::= <lista-identificadores> : <tipo>
<lista-identificadores> ::= <identificador> { , <identificador> }
<tipo>         ::= integer | real
<comando-composto> ::= begin <comando> { ; <comando> } end
<comando>      ::= <atribuicao> | <comando-composto> | <comando-condicional> | <comando-repetitivo>
<atribuicao>   ::= <variavel> := <expressao>
<comando-condicional> ::= if <expressao> then <comando> [ else <comando> ]
<comando-repetitivo>  ::= while <expressao> do <comando>
<expressao>    ::= <expressao-simples> [ <relacao> <expressao-simples> ]
<relacao>      ::= = | <> | < | <= | >= | >
<expressao-simples> ::= [ + | - ] <termo> { ( + | - ) <termo> }
<termo>        ::= <fator> { ( * | / ) <fator> }
<fator>        ::= <variavel> | <numero> | ( <expressao> )
<variavel>     ::= <identificador>
```
