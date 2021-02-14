CC=gcc
CFLAGS=-std=c18 -pedantic -Wall -Werror

all: run

run: main
	./main

main: main.c subsidiary_funk.h list_funk.h clean
	$(CC) $(CFLAGS) -o main main.c subsidiary_funk.h list_funk.h

clean:
	rm -f *.o 