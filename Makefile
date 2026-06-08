CC = gcc
CFLAGS = -Wall -g
SRCS = afd_numero.c identificador.c operadores.c token.c ts.c lexer.c parser.c main.c
OBJ = parser

all: $(OBJ)

$(OBJ): $(SRCS)
	$(CC) $(CFLAGS) -o $(OBJ) $(SRCS)

clean:
	rm -f $(OBJ) saida.sin
