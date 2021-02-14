CC=gcc
CFLAGS=-std=c18 -pedantic -Wall -Werror

all: main clean

main: main.o bmp.o image.o util.o 
	$(CC) $(CFLAGS) main.o bmp.o image.o util.o  -o main

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

bmp.o: bmp.c
	$(CC) $(CFLAGS) -c bmp.c

image.o: image.c
	$(CC) $(CFLAGS) -c image.c

util.o: util.c
	$(CC) $(CFLAGS) -c util.c

clean:
	rm -f *.o 