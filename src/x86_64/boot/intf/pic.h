#pragma once

#include "port.h"

#define PIC1_CMD    0x20 // Master PIC command
#define PIC1_DATA   0x21 // Master PIC data
#define PIC2_CMD    0xA0 // Slave PIC command
#define PIC2_DATA   0xA1 // Slave PIC data

#define PIC_EOI     0x20 // End of interrupt

extern "C" void remap_pic(uint32_t master_offset, uint32_t slave_offset);
extern "C" void mask_irq(uint8_t irq);
extern "C" void unmask_irq(uint8_t irq);

/// @brief Sends the "End of Interrupt" signal to the PIC's specified IRQ line.
/// This acknowledges the interrupt and will either indicate the IRQ is handled
/// or request the next byte to be sent.
/// @param irq The IRQ line to send the EOI to.
static inline void sendEOI(uint8_t irq)
{
    // If slave PIC set IRQ we acknowledge it
    if (irq >= 8)
    {
        outb(PIC2_CMD, PIC_EOI);
    }

    // Master PIC must always be acknowledged
    outb(PIC1_CMD, PIC_EOI);
}
