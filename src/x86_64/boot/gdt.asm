bits 64

global gdt_descriptor
global SEG_KERNEL_CODE, SEG_KERNEL_DATA

%define KERNEL_VMA 0xFFFFFFFF80000000

section .rodata

; The layout of the segment descriptors can be found at:
; https://wiki.osdev.org/Global_Descriptor_Table#Segment_Descriptor
gdt:
    dq 0x0              ; null descriptor

    .seg_kernel_code:
        dw 0xFFFF       ; limit low
        dw 0x0          ; base low
        db 0x0          ; base mid
        db 10011010b    ; access (present, ring 0 [2 bits], code/data segment, code segment, non-conforming, readable, not-accessed)
        db 10101111b    ; flags [4 bits] (4 KiB, _, long-mode, _) << 4 | limit high
        db 0x0          ; base high

    .seg_kernel_data:
        dw 0xFFFF       ; limit low
        dw 0x0          ; base low
        db 0x0          ; base mid
        db 10010000b    ; access (present, ring 0 [2 bits], code/data segment, data segment, non-conforming, non-writable, not-accessed)
        db 10101111b    ; flags [4 bits] (4 KiB, _, long-mode, _) << 4 | limit high
        db 0x0          ; base high

gdt_end:

gdt_descriptor:
    dw gdt_end - gdt - 1        ; limit
    dd gdt - KERNEL_VMA         ; address

; global segment accessors
SEG_KERNEL_CODE equ gdt.seg_kernel_code - gdt
SEG_KERNEL_DATA equ gdt.seg_kernel_data - gdt
