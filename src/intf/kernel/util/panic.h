#pragma once

#include "util/attributes.h"

/// @brief Prints a panic message to the screen in white on red.
/// Clears interrupts and hangs the CPU indefinitely.
/// @param fmt The message to print.
void __noreturn kpanic(const char* fmt, ...);
