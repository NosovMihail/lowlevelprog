global find_word
extern string_equals
section .text
find_word:
	mov r8, rdi
	.loop:
		mov r9, rsi
		test rsi, rsi
		je .exit_not_found
		add rsi, 8
        	mov rdi, r8
		call string_equals
		mov rsi, r9
		test rax, rax
		jnz .exit_found
		mov rsi, [rsi]
		jmp .loop
	.exit_found:
		mov rax, rsi
		ret
	.exit_not_found:
		mov rax, 0
		ret
