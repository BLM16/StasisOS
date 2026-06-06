#include "drivers/video/vga.h"
#include "klib/stdio.h"
#include "pic.h"
#include "idt.h"
#include "util/asm_snippets.h"
#include "multiboot2.h"
#include "kernel/mb2_parser.h"

namespace VGA = drivers::video::VGA;
namespace Color = VGA::Color;

void print_welcome();

/// @brief The entry point into the StasisOS kernel.
extern "C" void kernel_main(const MB2_information_structure* MBI)
{
    // Parse the relevant multiboot information
    parse_multiboot(MBI);

    // Remap the PIC interrupt vectors to 0x20..0x2F
    remap_pic(0x20, 0x28);

    // Set interrupt handlers
    init_idt();
    __enable_interrupts();

    // Print the startup banner
    VGA::clear_screen();
    print_welcome();

    // Create temporary text input prompt
    printf("\n\n> ");

    while (true);
}

/// @brief Prints a startup banner
void print_welcome()
{
    VGA::set_color(Color::GREEN, Color::BLACK);
    printf("Welcome to StasisOS!\n\n");

    VGA::set_color(Color::WHITE, Color::BLACK);
    printf("The OS that is unchanging. The OS that is always in equilibrium.\n\n");

    VGA::set_color(Color::LIGHT_GRAY, Color::BLACK);
    printf("Copyright (c) 2023 Bradley Myers. All rights reserved.");
}
