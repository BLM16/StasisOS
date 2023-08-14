bits 32

global start

extern test_multiboot, test_cpuid, test_long_mode
extern setup_page_tables, enable_paging
extern gdt_descriptor, SEG_KERNEL_CODE
extern long_mode_start

section .text
start:  
    cli ; clear interrupts

    ; setup the stack
    mov ebp, stack_top
    mov esp, ebp

    ; test requirements for long mode support (error and hlt if fail)
    call test_multiboot
    call test_cpuid
    call test_long_mode

    ; setup paging and enable long mode
    call setup_page_tables
    call enable_paging

    ; load GDT
    lgdt [gdt_descriptor]

    ; start long mode
    jmp SEG_KERNEL_CODE:long_mode_start

section .bss
align 4096
stack_bottom:
    resb 4096 * 4
stack_top:
