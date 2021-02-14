global write_to_stdout
global exit
global string_length
global print_string
global print_char
global print_newline
global print_uint
global print_int
global string_equals
global read_char
global read_word
global parse_uint
global parse_int
global string_copy
global write_to_stderr
section .text

%define tab       9 ; 0x9
%define CR       13 ; 0xD
%define new_line 10 ; 0xA
%define space    32 ; 0x20
%define minus    45 ; 0x2D

; args:rsi-const char *buf, rdx-size_t count
write_to_stdout:
    mov     rax, 1
    mov     rdi, 1
    syscall
    ret

write_to_stderr:
    mov     rax, 1
    mov     rdi, 2
    syscall
    ret
; Принимает код возврата и завершает текущий процесс
exit:
    xor     rax, rax
    mov     rax, 60
    syscall

; Принимает указатель на нуль-терминированную строку, возвращает её длину
; args: rdi - pointer to the start of the string -> returns: rax - string's length
string_length:
	xor     rax, rax
	.loop:
		cmp     byte[rdi + rax], 0
		je      .end
		inc     rax
		jmp     .loop
	.end:
		ret

; Принимает указатель на нуль-терминированную строку, выводит её в stdout
;args: rdi - pointer to the start of the string, r8 - stream
print_string:
    xor     rax, rax
    mov     rsi, rdi
    call    string_length
    mov     rdx, rax

    mov     rax, 1
    mov     rdi, r8
    syscall

    xor     rax, rax
    ret

; Принимает код символа и выводит его в stdout
; args: rdi - char itself -> Side effect
print_char:
    xor     rax, rax
    push    rdi
    mov     rsi, rsp
    mov     rdx, 1
    call    write_to_stdout
    add     rsp, 8
    ret

; Переводит строку (выводит символ с кодом 0xA)
print_newline:
    mov     rdi, 10 ; код новой строки
	call    print_char
    ret

; Выводит беззнаковое 8-байтовое число в десятичном формате 
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
; args: rdi - unsigned integer itself -> Side effect
print_uint:
    push    r12
    mov     r12, rsp                                    
    mov     rax, rdi                                    
    dec     rsp
    mov     byte[rsp], 0                                
    .loop:
        xor     rdx, rdx
        dec     rsp
        push    r13
        mov     r13, 10
        div     r13
        pop     r13
        add     rdx, 0x30
        mov     byte[rsp], dl
        test    rax, rax
        jz      .print                 
        jmp     .loop
    .print:
        mov     rdi, rsp           
        call    print_string       
        mov     rsp, r12           
    pop     r12
    ret

; Выводит знаковое 8-байтовое число в десятичном формате
; args: rdi - signed integer itself ->  Side effect
print_int:
    xor     rax, rax
    mov     rax, rdi                                    
    test    rax, rax
    jns     .positive
    push    rax                        
    mov     rdi, '-'
    call    print_char     
    pop     rax
    neg     rax
    mov     rdi, rax
    .positive:
        call    print_uint
        ret

; Принимает два указателя на нуль-терминированные строки, возвращает 1 если они равны, 0 иначе
; args: rdi = string1 address, rsi = string2 address -> returns: rax = 1 (true) or rax = 0 (false)
string_equals:
        xor     rax, rax
        push    r10
        push    r13
        .loop:
            mov     r10b, byte[rsi]
            mov     r13b, byte[rdi]
            inc     rsi
            inc     rdi
            cmp     r10b, r13b
            jne     .ret_zero
            cmp     r13b, 0
            jne     .loop
            inc     rax
       .ret_zero:
            pop     r13
            pop     r10
            ret
            
; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
; EMPTY args ->  returns: rax - new char
read_char:
    push    rdi
    push    rdx
    dec     rsp
    mov     rax, 0
    mov     rdi, 0
    mov     rdx, 1          
    mov     rsi, rsp
    syscall
    test    rax, rax
    je      .return
    xor     rax, rax
    mov     al, [rsp]
    .return:
        inc     rsp
        pop     rdx
        pop     rdi
        ret


; Принимает: адрес начала буфера, размер буфера
; Читает в буфер слово из stdin, пропуская пробельные символы в начале, .
; Пробельные символы это пробел 0x20, табуляция 0x9 и перевод строки 0xA.
; Останавливается и возвращает 0 если слово слишком большое для буфера
; При успехе возвращает адрес буфера в rax, длину слова в rdx.
; При неудаче возвращает 0 в rax
; Эта функция должна дописывать к слову нуль-терминатор
; args: rdi - buffer address, rsi - buffer size -> returns: Right(rax - buffer address, rdx - word length) or Left(rax = 0)
read_word:
	push r14
	push r15

	xor r14, r14
	mov r15, rsi

	dec r15

	.space_init_loop:
		push rdi
		call read_char		; Read new char (preserving rdi)
		pop rdi

		cmp al, space		; Compare with space
		je .space_init_loop
		cmp al, new_line	; Compare with new_line
		je .space_init_loop
		cmp al, tab		; Compare with tab
		je .space_init_loop
		cmp al, CR		; Compare with "Carruage Return"
		je .space_init_loop

		test al, al
		jz .correct_ending

	.read_word_loop:
		mov byte[rdi + r14], al
		inc r14

		push rdi
		call read_char		; Read new char (preserving rdi)
		pop rdi

		cmp al, space		; Compare with space
		je .correct_ending
		cmp al, new_line	; Compare with new_line
		je .correct_ending
		cmp al, tab		; Compare with tab
		je .correct_ending
		cmp al, CR		; Compare with "Carruage Return"
		je .correct_ending
		test al, al		; Compare with null
		jz .correct_ending

		cmp r14, r15		; Check if not overflown
		je .incorrect_ending

		jmp .read_word_loop

	.correct_ending:
		mov byte[rdi + r14], 0	; Append null symbol

		mov rax, rdi			; Insert results
		mov rdx, r14

		jmp .ending

	.incorrect_ending:
		xor rax, rax			; Set result to 0

		jmp .ending

	.ending:
		pop r15		; Restoring r14-r15
		pop r14

		ret

; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
; args: rdi = integer string repr address -> returns: rax - number, rdx - count of characters
parse_uint:
    xor     rax, rax
    push    r13
    mov     r13, 10
    xor     rax, rax
    xor     rcx, rcx
    xor     rdx, rdx
    xor     rsi, rsi
    .parse_char:
        mov     sil, [rdi + rcx]
        cmp     sil, '0'
        jl      .return
        cmp     sil, '9'
        jg      .return
        inc     rcx
        sub     sil, '0'
        mul     r13
        add     rax, rsi
        jmp     .parse_char
    .return:
        mov     rdx, rcx
        pop     r13
        ret

; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был) 
; rdx = 0 если число прочитать не удалось
; args: rdi = integer string repr address -> returns: rax - number, rdx - count of characters
parse_int:
    xor     rax, rax
    cmp     byte [rdi], 0x2d
    je      .parse_ng
    call    parse_uint
    ret
    .parse_ng:
        inc     rdi
        call    parse_uint
        cmp     rdx, 0
        je      .return
        neg     rax
        inc     rdx
    .return:
        ret

; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
; args: rdi = source address, rsi = destinastion address, rdx = destination size -> returns: Right(rax = destination address) or Left(rax = 0)
string_copy:
    push    r12
    xor     rcx, rcx
    .main_loop:
        cmp     rcx, rdx
        je      .overflow
        mov     r12, [rdi + rcx]
        mov     [rsi, rcx], r12
        cmp     r12, 0
        je      .exit
        inc     rcx
        jmp     .main_loop
    .overflow:
        mov     rax, 0
        jmp     .exit
    .exit:
        pop     r12
        ret