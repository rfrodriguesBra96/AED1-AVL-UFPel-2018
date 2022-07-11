CC=gcc

CFLAGS=-Wall -Wextra -Werror -O0 -g -std=c11 -I.. 
LDLIBS=-lm

all: test
	./test


fila.o: fila.c
extra.o: extra.c
# coloque outras dependencias aqui


test: fila.o extra.o arvore.o test.c




clean:
	rm -f *.o test

