#pragma once

#include "keyboard.h"
#include "util/attributes.h"

namespace drivers::keyboard
{
    /// @brief Required by __interrupt
    struct interrupt_frame;

    void __interrupt irq_handler(interrupt_frame *frame);
}
