#pragma once

#define __clear_interrupts() asm volatile("cli")
#define __enable_interrupts() asm volatile("sti")

#define __hlt() asm volatile("hlt")
