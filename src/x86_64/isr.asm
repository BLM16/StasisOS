bits 64

extern exception_handler

%macro pushaq 0
    push rax
    push rbx
    push rcx
    push rdx
    push rbp
    push rsi
    push rdi
%endmacro

%macro popaq 0
    pop rdi
    pop rsi
    pop rbp
    pop rdx
    pop rcx
    pop rbx
    pop rax
%endmacro

%macro define_isr 1
    global isr%+%1
    
    isr%+%1:
        ; push dummy err_code if the interrupt doesn't have one
        %ifndef has_error_code
            push 0
        %endif

        push %1         ; int_no
        pushaq
        
        cld
        call exception_handler

        popaq
        add esp, 8      ; clean err_code and int_no 
        iretq
%endmacro

; create isr0-isr31
%assign i 0
%rep    32
    ; these interrupts already have error codes that are automatically pushed
    %if i == 8 || i == 10 || i == 11 || i == 12 || i == 13 || i == 14 || i == 17 || i == 21 || i == 29 || i == 30
        %define has_error_code
    %endif

    ; define the ISR label
    define_isr i

    %undef has_error_code
    %assign i i+1
%endrep
