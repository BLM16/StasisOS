bits 32

global start
global stack_top

extern test_multiboot, test_cpuid, test_long_mode
extern setup_page_tables, enable_paging
extern gdt_descriptor, SEG_KERNEL_CODE
extern long_mode_start

%define KERNEL_VMA 0xFFFFFFFF80000000

section .boot.text progbits alloc exec nowrite align=16
start:  
    cli ; clear interrupts

    mov esi, eax ; save MB2 magic
    mov edi, ebx ; save MBI pointer

    ; setup the stack
    mov ebp, stack_top - KERNEL_VMA
    mov esp, ebp

    ; test requirements for long mode support (error and hlt if fail)
    call test_multiboot
    call test_cpuid
    call test_long_mode

    ; setup paging and enable long mode
    call setup_page_tables
    call enable_paging

    ; load GDT
    mov eax, gdt_descriptor - KERNEL_VMA
    lgdt [eax]

    ; start long mode
    jmp SEG_KERNEL_CODE:long_mode_start

section .bss
align 4096
stack_bottom:
    resb 4096 * 4 ; 16 KiB 
stack_top:
