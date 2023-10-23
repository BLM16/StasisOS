ENTRY(start)

BOOT_LMA = 0x100000;
KERNEL_VMA = 0xFFFFFFFF80000000;

SECTIONS
{
    . = BOOT_LMA;

    .multiboot :
    {
        KEEP(*(.multiboot))
    }

    .boot.text :
    {
        *(.boot.text)
    }

    KERNEL_LMA = .;
    . += KERNEL_VMA;

    .text ALIGN(4096) : AT(ADDR(.text) - KERNEL_VMA)
    {
        *(.text)
    }

    .rodata ALIGN(4096) : AT(ADDR(.rodata) - KERNEL_VMA)
    {
        *(.rodata*)
    }

    .data ALIGN(4096) : AT(ADDR(.data) - KERNEL_VMA)
    {
        *(.data)
    }

    .bss ALIGN(4096) : AT(ADDR(.bss) - KERNEL_VMA)
    {
        *(COMMON)
        *(.bss)
    }

    KERNEL_END_VMA = .;
}
