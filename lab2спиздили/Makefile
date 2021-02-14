AFLAGS=-felf64
ASM=nasm

all: main.asm lib.asm dict.asm
	$(ASM) $(AFLAGS) main.asm  
	$(ASM) $(AFLAGS) lib.asm  
	$(ASM) $(AFLAGS) dict.asm 
	ld -o main main.o dict.o lib.o
clean:
		find . -type f -name '*.o' -delete
		find . -type f -name '*.out' -delete
