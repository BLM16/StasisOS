bits 64

global long_mode_start

extern remap_pic
extern init_idt
extern kernel_main

section .text
long_mode_start:
    ; null all data segment registers
    xor eax, eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax

    ; remap the PIC interrupt vectors to 0x20..0x2F
    mov esi, 0x28 ; slave_offset (0x28..0x2F)
    mov edi, 0x20 ; master_offset (0x20..0x27)
    call remap_pic
    
    ; Enable interrupts
    call init_idt
    sti

    ; start the kernel
    call kernel_main

    ; hang the CPU if the kernel falls through
    .hang:
        hlt
        jmp .hang
