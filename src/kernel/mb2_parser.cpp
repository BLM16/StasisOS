#include "kernel/mb2_parser.h"

#include "drivers/video/vga.h"
#include "klib/stdio.h"

namespace VGA = drivers::video::VGA;
namespace Color = VGA::Color;

void parse_multiboot(const MB2_information_structure* MBI)
{
    const uintptr_t mbi_addr = reinterpret_cast<uintptr_t>(MBI);

    // Ensure the MBI is properly aligned
    if (mbi_addr & 7)
    {
        VGA::set_color(Color::RED, Color::BLACK);
        printf("Err: Unaligned MBI");
        return;
    }

    VGA::clear_screen();
    VGA::set_color(Color::CYAN, Color::BLACK);

    for (MB2_tag* tag = reinterpret_cast<MB2_tag*>(mbi_addr + sizeof(MBI));
         tag->type != MB2_TYPE_END;
         tag = reinterpret_cast<MB2_tag*>(reinterpret_cast<uintptr_t>(tag) + ((tag->size + 7) & ~7)))
    {
        switch (tag->type)
        {
        case MB2_TYPE_CMDLINE:
            printf("Command line found.\n");
            break;

        case MB2_TYPE_BOOTLOADER:
            printf("Boot loader found.\n");
            break;

        case MB2_TYPE_MODULES:
            printf("Module found.\n");
            break;

        case MB2_TYPE_MEMINFO:
            printf("Memory info found.\n");
            printf("\tLower: 0x%x\n", reinterpret_cast<MB2_tag_meminfo*>(tag)->mem_lower);
            printf("\tUpper: 0x%x\n", reinterpret_cast<MB2_tag_meminfo*>(tag)->mem_upper);
            break;

        case MB2_TYPE_BIOSDEV:
            printf("Bios boot device found.\n");
            break;

        case MB2_TYPE_MEMMAP:
            printf("Memory map found.\n");
            break;

        case MB2_TYPE_VBEINFO:
            printf("VBE info found.\n");
            break;

        case MB2_TYPE_FBUFFINFO:
            printf("Frame buffer info found.\n");
            break;

        case MB2_TYPE_ELFSYMBOLS:
            printf("ELF symbols info found.\n");
            break;        

        case MB2_TYPE_APMTABLE:
            printf("APM table info found.\n");
            break;

        case MB2_TYPE_EFISYSTAB32:
            printf("EFI x32 system table info found.\n");
            break;

        case MB2_TYPE_EFISYSTAB64:
            printf("EFI x64 system table info found.\n");
            break;

        case MB2_TYPE_SMBIOSTAB:
            printf("SM BIOS table info found.\n");
            break;

        case MB2_TYPE_ACPIOLD:
            printf("Old ACPI info found.\n");
            break;

        case MB2_TYPE_ACPINEW:
            printf("New ACPI info found.\n");
            break;

        case MB2_TYPE_NETWORK:
            printf("Network info found.\n");
            break;

        case MB2_TYPE_EFIMEMMAP:
            printf("EFI Memory Map found.\n");
            break;

        case MB2_TYPE_EFIBOOTNT:
            printf("EFI boot not terminated.\n");
            break;

        case MB2_TYPE_EFIIMGHND32:
            printf("EFI x32 image handle found.\n");
            break;

        case MB2_TYPE_EFIIMGHND64:
            printf("EFI x64 image handle found.\n");
            break;

        case MB2_TYPE_IMGLDBPA:
            printf("Image base address found.\n");
            printf("\t0x%x\n", reinterpret_cast<MB2_tag_imgldbpa*>(tag)->load_base_addr);
            break;

        default:
            printf("Unrecognized tag found.\n");
            break;
        }
    }
}