section .multiboot
header_start:
    dd 0xE85250D6                                                   ; multiboot 2 magic number
    dd 0                                                            ; architecture: protected mode i386
    dd header_end - header_start                                    ; header length
    dd 0x100000000 - (0xE85250D6 + 0 + (header_end - header_start)) ; checksum

    dw 0
    dw 0
    dd 8
header_end:
