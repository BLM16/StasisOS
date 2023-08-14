#pragma once

#include "keyboard.h"

namespace drivers::keyboard
{
    /// @brief Required by __attribute__((interrupt))
    struct interrupt_frame;

    __attribute__((interrupt))
    void irq_handler(interrupt_frame *frame);
}
