bits 32

global test_multiboot
global test_cpuid
global test_long_mode

%define KERNEL_VMA 0xFFFFFFFF80000000

section .boot.text

; tests for multiboot capability
test_multiboot:
    cmp eax, 0x36D76289
    jne .no_multiboot
    ret

    .no_multiboot:
        mov eax, MSG_NO_MULTIBOOT - KERNEL_VMA
        jmp error

; tests for cpuid support
test_cpuid:
    pushfd
    pop eax
    mov ecx, eax
    xor eax, 1 << 21
    push eax
    popfd
    pushfd
    pop eax
    push ecx
    popfd
    cmp eax, ecx
    je .no_cpuid
    ret

    .no_cpuid:
        mov eax, MSG_NO_CPUID - KERNEL_VMA
        jmp error

; tests for long mode capability
test_long_mode:
    mov eax, 0x80000000
    cpuid
    cmp eax, 0x80000001
    jb .no_long_mode

    mov eax, 0x80000001
    cpuid
    test edx, 1 << 29
    jz .no_long_mode
    ret
    
    .no_long_mode:
        mov eax, MSG_NO_LONG_MODE - KERNEL_VMA
        jmp error

; print the error message from eax to the VGA buffer then hlt
error:
    mov esi, eax        ; string source from error msg
    mov edi, 0xB8000    ; string destination to VGA buffer
    mov ah, 0x4F        ; color descriptor (white on red)

    .print_loop:
        lodsb           ; next byte from string -> al
        or al, al       ; check null terminator (end of string)
        jz .print_end

        mov [edi], ax   ; write color and char to VGA buffer
        add edi, 2      ; increment VGA buffer offset

        jmp .print_loop
    .print_end:
        
    hlt

section .rodata
MSG_NO_MULTIBOOT db "ERR: MULTIBOOT NOT SUPPORTED", 0x0
MSG_NO_CPUID     db "ERR: CPUID NOT PRESENT", 0x0
MSG_NO_LONG_MODE db "ERR: LONG MODE NOT SUPPORTED", 0x0
