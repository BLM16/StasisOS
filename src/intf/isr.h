#pragma once

#include <stdint.h>
#include "util/attributes.h"

/// @brief Represents the stack frame for an exception including
/// the interrupt number, the error code, and registers for debugging.
typedef struct __packed Exception_Stack_Frame {
    uint64_t rdi, rsi, rbp, rdx, rcx, rbx, rax;
    uint64_t int_no, err_code;
    uint64_t rip, cs, rflags, rsp, ss;
} Exception_Stack_Frame;

extern "C" void exception_handler(Exception_Stack_Frame frame);

extern "C" {
    void isr0();
    void isr1();
    void isr2();
    void isr3();
    void isr4();
    void isr5();
    void isr6();
    void isr7();
    void isr8();
    void isr9();
    void isr10();
    void isr11();
    void isr12();
    void isr13();
    void isr14();
    void isr15();
    void isr16();
    void isr17();
    void isr18();
    void isr19();
    void isr20();
    void isr21();
    void isr22();
    void isr23();
    void isr24();
    void isr25();
    void isr26();
    void isr27();
    void isr28();
    void isr29();
    void isr30();
    void isr31();
}
