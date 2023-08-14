#pragma once

#include <stdint.h>

/// @brief Write a byte out to a given port.
/// @param port The port to write to.
/// @param val The byte to write to the port.
static inline void outb(uint16_t port, uint8_t val)
{
    asm volatile("outb %0, %1" : : "a"(val), "Nd"(port) : "memory");
}

/// @brief Read a byte in from a given port.
/// @param port The port to read the byte from.
/// @return The byte read from the port.
static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm volatile("inb %1, %0" : "=a"(ret) : "Nd"(port) : "memory");
    return ret;
}

/// @brief Wait for port I/O operations on ports by writing to an unused port
/// which helps ensure that the previous port operation has completed.
static inline void io_wait()
{
    outb(0x80, 0);
}
