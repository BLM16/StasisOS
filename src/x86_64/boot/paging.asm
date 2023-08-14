bits 32

global setup_page_tables
global enable_paging

section .text

; Initializes the page tables for memory management
setup_page_tables:
    mov eax, page_table_l3
    or eax, 11b ; present, writable
    mov [page_table_l4], eax
    
    mov eax, page_table_l2
    or eax, 11b ; present, writable
    mov [page_table_l3], eax

    mov ecx, 0
    .loop:
        mov eax, 0x200000   ; 2 MiB
        mul ecx
        or eax, 10000011b   ; present, writable, huge page
        mov [page_table_l2 + ecx * 8], eax

        inc ecx
        cmp ecx, 512
        jne .loop
    ret

; Enables paging with the flat memory model
; Also enables PAE and long mode
enable_paging:
    ; pass page table location to cpu
    mov eax, page_table_l4
    mov cr3, eax

    ; enable PAE
    mov eax, cr4
    or eax, 1 << 5
    mov cr4, eax

    ; enable long mode
    mov ecx, 0xC0000080
    rdmsr
    or eax, 1 << 8
    wrmsr

    ; enable paging
    mov eax, cr0
    or eax, 1 << 31
    mov cr0, eax

    ret

section .bss
align 4096
page_table_l4: resb 4096
page_table_l3: resb 4096
page_table_l2: resb 4096
