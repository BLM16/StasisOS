#include "idt.h"
#include "drivers/keyboard/irq_handler.h"

/// @brief The IDT to hold the ISR definitions.
static IDT_Entry idt[IDT_ENTRIES];

/// @brief Creates an IDT entry for the given vector.
/// @param vector The interrupt vector to set.
/// @param handler The handler for the interrupt vector.
/// @param flags The interrupt flags (present, ring, interrupt/trap)
static void set_isr(uint8_t vector, uintptr_t handler, uint8_t flags)
{
    IDT_Entry* entry = &idt[vector];
    
    entry->offset_low = (uintptr_t)handler & 0xFFFF;
    entry->segment = SEG_KERNEL_CODE;
    entry->ist = 0;
    entry->flags = flags;
    entry->offset_mid = ((uintptr_t)handler >> 16) & 0xFFFF;
    entry->offset_high = ((uintptr_t)handler >> 32) & 0xFFFFFFFF;
    entry->zero = 0;
}

/// @brief Initializes all the IDT entries for the exceptions and IRQs.
void init_idt()
{
    IDT_Ptr idt_pointer = {
        .limit = IDT_ENTRIES * sizeof(IDT_Entry) - 1,
        .base = (uintptr_t)&idt[0],
    };
    
    // Exceptions
    set_isr(0x00, (uintptr_t)isr0,  ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x01, (uintptr_t)isr1,  ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x02, (uintptr_t)isr2,  ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x03, (uintptr_t)isr3,  ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x04, (uintptr_t)isr4,  ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x05, (uintptr_t)isr5,  ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x06, (uintptr_t)isr6,  ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x07, (uintptr_t)isr7,  ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x08, (uintptr_t)isr8,  ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x09, (uintptr_t)isr9,  ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x0A, (uintptr_t)isr10, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x0B, (uintptr_t)isr11, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x0C, (uintptr_t)isr12, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x0D, (uintptr_t)isr13, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x0E, (uintptr_t)isr14, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x0F, (uintptr_t)isr15, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x10, (uintptr_t)isr16, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x11, (uintptr_t)isr17, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x12, (uintptr_t)isr18, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x13, (uintptr_t)isr19, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x14, (uintptr_t)isr20, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x15, (uintptr_t)isr21, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x16, (uintptr_t)isr22, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x17, (uintptr_t)isr23, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x18, (uintptr_t)isr24, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x19, (uintptr_t)isr25, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x1A, (uintptr_t)isr26, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x1B, (uintptr_t)isr27, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x1C, (uintptr_t)isr28, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x1D, (uintptr_t)isr29, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x1E, (uintptr_t)isr30, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);
    set_isr(0x1F, (uintptr_t)isr31, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT);

    // Mask/disable all the unused IRQs
    // IRQ1 = keyboard (used)
    // IRQ2 = slave PIC (slave PIC interrupts 8-15 masked separately)
    mask_irq(0);
    mask_irq(3);
    mask_irq(4);
    mask_irq(5);
    mask_irq(6);
    mask_irq(7);
    mask_irq(8);
    mask_irq(9);
    mask_irq(10);
    mask_irq(11);
    mask_irq(12);
    mask_irq(13);
    mask_irq(14);
    mask_irq(15);

    // IRQs
    // set_isr(0x20, (uintptr_t)tmp_irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // PIT
    set_isr(0x21, (uintptr_t)drivers::keyboard::irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // Keyboard IRQ
    // Slave PIC mapped to IRQ2 (vector 0x22); IRQ2 is never raised and should not have a registered ISR
    // set_isr(0x23, (uintptr_t)tmp_irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // COM2
    // set_isr(0x24, (uintptr_t)tmp_irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // COM1
    // set_isr(0x25, (uintptr_t)tmp_irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // LPT2
    // set_isr(0x26, (uintptr_t)tmp_irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // Floppy disk
    // set_isr(0x27, (uintptr_t)tmp_irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // LPT1 (spurious)
    // set_isr(0x28, (uintptr_t)tmp_irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // CMOS
    // set_isr(0x29, (uintptr_t)tmp_irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // Peripherals
    // set_isr(0x2A, (uintptr_t)tmp_irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // Peripherals
    // set_isr(0x2B, (uintptr_t)tmp_irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // Peripherals
    // set_isr(0x2C, (uintptr_t)tmp_irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // Mouse
    // set_isr(0x2D, (uintptr_t)tmp_irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // FPU
    // set_isr(0x2E, (uintptr_t)tmp_irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // Primary ATA hard disk
    // set_isr(0x2F, (uintptr_t)tmp_irq_handler, ENTRY_PRES(1) | ENTRY_RING(0) | ENTRY_GATE_INTERRUPT); // Secondary ATA hard disk
    
    asm volatile("lidt %0" : : "m" (idt_pointer));
}
