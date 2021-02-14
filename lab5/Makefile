CC=gcc
CFLAGS=-std=c18 -pedantic -Wall -Werror

all: main clean

main: main.o io.o list.o list_io.o maybe_int.o
	$(CC) $(CFLAGS) main.o io.o list.o list_io.o maybe_int.o -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

io.o: io.c
	$(CC) $(CFLAGS) -c io.c

list.o: list.c
	$(CC) $(CFLAGS) -c list.c

list_io.o: list_io.c
	$(CC) $(CFLAGS) -c list_io.c

maybe_int.o: maybe_int.c
	$(CC) $(CFLAGS) -c maybe_int.c

clean:
	rm -f *.o 