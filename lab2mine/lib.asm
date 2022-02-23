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

section .text
 
 
; Принимает код возврата и завершает текущий процесс
exit: 
    mov     rax, 60
    syscall

; Принимает указатель на нуль-терминированную строку, возвращает её длину
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
print_string:
    xor     rax, rax
    mov     rsi, rdi
    call    string_length
    mov     rdx, rax
    mov     rax, 1
    mov     rdi, 1
    syscall
    ret

; Принимает код символа и выводит его в stdout
print_char:
    xor     rax, rax
    push    rdi
    mov     rsi, rsp
    mov     rdx, 1
    mov     rax, 1
    mov     rdi, 1
    syscall
    add     rsp, 8
    ret

; Переводит строку (выводит символ с кодом 0xA)
print_newline:
    mov     rdi, 10
	call    print_char
    ret

; Выводит беззнаковое 8-байтовое число в десятичном формате 
; Совет: выделите место в стеке и храните там результаты деления
; Не забудьте перевести цифры в их ASCII коды.
print_uint:
    push    r12
    mov     r12, rsp                                                                        
    dec     rsp
    mov     byte[rsp], 0
    mov     rax, rdi                                
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
string_equals:
    xor     rax, rax
        push    r10
        push    r13
        .loop:
            mov     r10b, byte[rdi]
            mov     r13b, byte[rsi]
            inc     rsi
            inc     rdi
            cmp     r10b, r13b
            jne     .ret_zero
            cmp     r10b, 0
            jne     .loop
            inc     rax
       .ret_zero:
            pop     r13
            pop     r10
            ret

; Читает один символ из stdin и возвращает его. Возвращает 0 если достигнут конец потока
read_char:
    xor rax, rax
    push    rdi
    push    rdx
    dec     rsp
    xor     rdi, rdi
    mov     rdx, 1          
    mov     rsi, rsp
    syscall
    test    rax, rax
    je      .rtrn
    mov     al, [rsp]
    .rtrn:
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

read_word:
    push    r14                        
    push    r13
    xor     r14, r14
    mov     r10, rsi
    mov     r13, rdi
    .start:
        call    read_char    
        cmp     al, 0x0
        je      .end                          
        cmp     al, 0x20        
        je      .start                             
        cmp     al, 0x9
        je      .start
        cmp     al, 0xA
        je      .start
        jmp     .write_char
    .loop:
        call    read_char
        cmp     al, 0x0
        je      .end
        cmp     al, 0x20
        je      .end
        jmp     .write_char
    .write_char:
        mov     byte [r13 + r14], al
        inc     r14
        cmp     r14, r10
        je      .overflow
        jmp     .loop
    .end:
        mov     byte [r13 + r14], 0
        mov     rax, r13
        mov     rdx, r14
        jmp     .return
    .overflow:
        xor     rax, rax
        xor     rdx, rdx
    .return:
        pop     r13
        pop     r14     
        ret
 

; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
parse_uint:
    parse_uint:
    push    r13
    mov     r13, 10
    xor     rax, rax
    xor     rcx, rcx
    xor     rdx, rdx
    xor     rsi, rsi
    .next_dig:
        mov     sil, [rdi + rcx]
        cmp     sil, '9'
        jg      .return
        cmp     sil, '0'
        jl      .return
        sub     sil, '0'
        mul     r13
        add     rax, rsi
        inc     rcx
        jmp     .next_dig
    .return:
        mov     rdx, rcx
        pop     r13
        ret




; Принимает указатель на строку, пытается
; прочитать из её начала знаковое число.
; Если есть знак, пробелы между ним и числом не разрешены.
; Возвращает в rax: число, rdx : его длину в символах (включая знак, если он был) 
; rdx = 0 если число прочитать не удалось
parse_int:
    xor     rax, rax
    cmp     byte [rdi], '-'
    je      .negat
    call    parse_uint
    ret
    .negat:
        inc     rdi
        call    parse_uint
        neg     rax
        cmp     rdx, 0
        je      .return
        inc     rdx
    .return:
        ret 

; Принимает указатель на строку, указатель на буфер и длину буфера
; Копирует строку в буфер
; Возвращает длину строки если она умещается в буфер, иначе 0
string_copy:
    string_copy:
    push    r10
    xor     rcx, rcx
    .loop:
        cmp     rcx, rdx
        je      .overflow
        mov     r10, [rdi + rcx]
        mov     [rsi, rcx], r10
        cmp     r10, 0
        je      .return
        inc     rcx
        jmp     .loop
    .overflow:
        xor     rax, rax
        jmp     .return
    .return:
        pop     r10
        ret
