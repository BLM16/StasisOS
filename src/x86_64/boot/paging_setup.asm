bits 32

global setup_page_tables
global enable_paging

%define KERNEL_VMA 0xFFFFFFFF80000000

section .boot.text

; initializes the kernel page table mappings
setup_page_tables:
    ; identity map kernel
    mov eax, PDPT - KERNEL_VMA
    or eax, 11b ; writable, present
    mov dword [PML4 - KERNEL_VMA], eax
    
    ; higher half kernel mapping
    mov eax, PDPT_HH - KERNEL_VMA
    or eax, 11b ; writable, present
    mov dword [(PML4 - KERNEL_VMA) + 511 * 8], eax

    ; map PML4 into itself
    mov eax, PML4 - KERNEL_VMA
    or eax, 11b ; writable, present
    mov dword [(PML4 - KERNEL_VMA) + 510 * 8], eax

    ; map kernel page directory to identity mapping
    mov eax, PD_KERN - KERNEL_VMA
    or eax, 11b ; writable, present
    mov dword [PDPT - KERNEL_VMA], eax

    ; map kernel page directory to higher half mapping
    mov eax, PD_KERN - KERNEL_VMA
    or eax, 11b ; writable, present
    mov dword [(PDPT_HH - KERNEL_VMA) + 510 * 8], eax

    ; map all the entries in the page directory
    mov ecx, 0
    .map_page_directory:
        mov eax, 0x200000 ; 2 MiB pages
        mul ecx           ; * page number
        or eax, 10000011b ; huge page, writable, present

        ; Move computed value into page directory entry ecx * 8
        mov [(PD_KERN - KERNEL_VMA) + ecx * 8], eax

        inc ecx
        cmp ecx, 512
        jne .map_page_directory

    ret

; enables paging, PAE, and long mode
enable_paging:
    ; pass page table location to cpu
    mov eax, PML4 - KERNEL_VMA
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
    or eax, 1 << 31 ; Enable paging
    or eax, 1 << 16 ; Disable ring 0 from writing to readonly pages
    mov cr0, eax

    ret

section .bss
align 4096
PML4:    resb 4096
PDPT:    resb 4096  ; Kernel identity mapping
PDPT_HH: resb 4096  ; Virtual higher half mapping
PD_KERN: resb 4096  ; Directory to map the kernel
