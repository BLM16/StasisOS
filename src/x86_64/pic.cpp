#include "pic.h"

/// @brief Remaps the master and slave PIC interrupt vectors given specific offsets.
/// @param master_offset Master PIC interrupt vectors become master_offset..(master_offset + 7).
/// @param slave_offset Slave PIC interrupt vectors become slave_offset..(slave_offset + 7).
void remap_pic(uint32_t master_offset, uint32_t slave_offset)
{
    // Save masks
    uint8_t a1 = inb(PIC1_DATA), a2 = inb(PIC2_DATA);

    // Initialize PIC for remap
    outb(PIC1_CMD, 0x11);
        io_wait();
    outb(PIC2_CMD, 0x11);
        io_wait();

    // Set PIC interrupt vectors
    outb(PIC1_DATA, master_offset);
        io_wait();
    outb(PIC2_DATA, slave_offset);
        io_wait();

    // Map master & slave PICs
    outb(PIC1_DATA, 0x04);
        io_wait();
    outb(PIC2_DATA, 0x02);
        io_wait();

    // Set PICs to 8086 mode
    outb(PIC1_DATA, 0x01);
        io_wait();
    outb(PIC2_DATA, 0x01);
        io_wait();

    // Restore saved masks
    outb(PIC1_DATA, a1);
        io_wait();
    outb(PIC2_DATA, a2);
        io_wait();
}

/// @brief Masks/disables the PIC interrupts for the given IRQ.
/// Masking 0x2 masks all slave PIC interrupts.
/// @param irq The IRQ to mask (0-15).
void mask_irq(uint8_t irq)
{
    uint16_t port;
    uint8_t value;

    if (irq < 8)
    {
        port = PIC1_DATA;
    }
    else
    {
        port = PIC2_DATA;
        irq -= 8; // Slave PIC line 0 -> IRQ8
    }

    value = inb(port) | (1 << irq);
    outb(port, value);
}

/// @brief Unmasks/enables the PIC interrupts for the given IRQ.
/// Unmasking 0x2 enables all the slave PIC interrupts that aren't individually masked.
/// @param irq The IRQ to unmask (0-15).
void unmask_irq(uint8_t irq)
{
    uint16_t port;
    uint8_t value;

    if (irq < 8)
    {
        port = PIC1_DATA;
    }
    else
    {
        port = PIC2_DATA;
        irq -= 8; // Slave PIC line 0 -> IRQ8
    }

    value = inb(port) & ~(1 << irq);
    outb(port, value);
}
