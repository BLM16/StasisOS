bits 64

global long_mode_start

section .boot.text

; trampolines to the kernel_start wrapper in the higher-half
long_mode_start:
    ; null all data segment registers
    xor eax, eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    jmp kernel_start

section .text
bits 64

extern kernel_main
extern stack_top

kernel_start:
    ; reload the stack with the virtual memory address
    lea rbp, [stack_top]
    mov rsp, rbp

    call kernel_main ; jump into kernel code

    ; hang the CPU if the kernel falls through
    cli
    hlt
