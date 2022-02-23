%include "words.inc"
%define start_dict last_add
extern read_word
extern exit
extern print_string
extern find_word
extern print_newline
extern string_length
global _start

section .data
    reading_error_msg: db "Could not read message", 0
	not_found_msg: db "No such key", 0

section .text
_start:
	mov rsi, 255
	sub rsp, 255
	mov rdi, rsp
	call read_word
	test rax,rax
	je .reading_error
	mov rdi,rax
	mov rsi, start_dict
	call find_word
	test rax,rax
	je .not_found
	jmp .found
	.reading_error:
		mov r8,2
		mov rdi,reading_error_msg
		jmp .exit
	.not_found:
		mov r8,2
		mov rdi,not_found_msg
		jmp .exit
	.found:
		add rax, 8
		mov rdi, rax
		mov r9,rax
		call string_length
		add r9, rax
		inc r9
		mov rdi, r9
		mov r8, 1
		jmp .exit
	.exit:
		call print_string
		call print_newline
		call exit
