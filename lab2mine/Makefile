all: lib.asm dict.asm main.asm
	nasm -felf64  lib.asm
	nasm -felf64 dict.asm
	nasm -felf64 main.asm
	ld -o main dict.o lib.o  main.o
clean:
	find . -type f -name '*.o' -delete