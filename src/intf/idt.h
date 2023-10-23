#pragma once

#include <stdint.h>
#include "isr.h"
#include "gdt.h"
#include "pic.h"

#define IDT_ENTRIES 256

#define ENTRY_PRES(x) ((x & 0x1) << 0x7)
#define ENTRY_RING(x) ((x & 0x3) << 0x5)
#define ENTRY_GATE_INTERRUPT 0xE
#define ENTRY_GATE_TRAP 0xF

/// @brief Represents an IDT entry in the appropriate memory layout.
typedef struct __attribute__((packed)) IDT_Entry {
    uint16_t offset_low;
    uint16_t segment;       // GDT segment on which to run the ISR
    uint8_t  ist;           // 3 bit offset into the IST (ignored if 0)
    uint8_t  flags;         // Present, ring, gate type
    uint16_t offset_mid;
    uint32_t offset_high;
    uint32_t zero;          // Reserved field should always be 0
} IDT_Entry;

/// @brief Represents the IDT pointer to be loaded into the idtr register.
typedef struct __attribute__((packed)) IDT_Ptr {
    uint16_t limit;
    uint64_t base;
} IDT_Ptr;

extern "C" void init_idt();

/// @brief `cli`
inline void __clear_interrupts() { asm volatile("cli"); }
/// @brief `sti`
inline void __enable_interrupts() { asm volatile("sti"); }
