#include "kernel/util/panic.h"

#include "drivers/video/vga.h"
#include "klib/stdio.h"
#include "util/asm_snippets.h"
#include <stdarg.h>

namespace VGA = drivers::video::VGA;
namespace Color = VGA::Color;

void __noreturn kpanic(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    VGA::set_color(Color::WHITE, Color::RED);
    printf("[PANIC] ");
    vprintf(fmt, args);

    __clear_interrupts();
    __hlt();
    __builtin_unreachable();
}
