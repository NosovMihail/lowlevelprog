section .text

write_to_stdout:
    mov     rax, 1
    mov     rdi, 1
    syscall
    ret

; Принимает код возврата и завершает текущий процесс
exit:
    xor     rax, rax
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
    call    write_to_stdout
    xor     rax, rax
    ret

; Принимает код символа и выводит его в stdout
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
read_word:
    push    r13                        
    push    r14
    xor     r14, r14
    mov     r10, rsi
    mov     r13, rdi
    .init_loop:
        call    read_char                              
        cmp     al, 0x20        
        je      .init_loop                             
        cmp     al, 0x9
        je      .init_loop
        cmp     al, 0xA
        je      .init_loop
        cmp     al, 0x0
        je      .read_end
        jmp     .write_char
    .read_start:
        call    read_char
        cmp     al, 0x0
        je      .read_end
        cmp     al, 0x20
        je      .read_end
        jmp     .write_char
    .write_char:
        mov     byte [r13 + r14], al
        inc     r14
        cmp     r14, r10
        je      .overflow
        jmp     .read_start
    .read_end:
        mov     rax, r13
        mov     byte [r13 + r14], 0
        mov     rdx, r14
        jmp     .return
    .overflow:
        xor     rax, rax
        xor     rdx, rdx
    .return:
        pop     r14
        pop     r13     
        ret

; Принимает указатель на строку, пытается
; прочитать из её начала беззнаковое число.
; Возвращает в rax: число, rdx : его длину в символах
; rdx = 0 если число прочитать не удалось
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