#include "drivers/video/vga.h"
#include "pic.h"
#include "idt.h"

namespace VGA = drivers::video::VGA;
namespace Color = VGA::Color;

void print_welcome();

/// @brief The entry point into the StasisOS kernel.
extern "C" void kernel_main()
{
    // Remap the PIC interrupt vectors to 0x20..0x2F
    remap_pic(0x20, 0x28);

    // Set interrupt handlers
    init_idt();
    __enable_interrupts();

    // Print the startup banner
    VGA::clear_screen();
    print_welcome();

    // Create temporary text input prompt
    VGA::print_str("\n\n");
    VGA::print_str("> ");

    while (true);
}

/// @brief Prints a startup banner
void print_welcome()
{
    VGA::set_color(Color::GREEN, Color::BLACK);
    VGA::print_str("Welcome to StasisOS!\n");
    VGA::print_chr('\n');

    VGA::set_color(Color::WHITE, Color::BLACK);
    VGA::print_str("The OS that is unchanging. The OS that is always in equilibrium.\n\n");

    VGA::set_color(Color::LIGHT_GRAY, Color::BLACK);
    VGA::print_str("Copyright (c) 2023 Bradley Myers. All rights reserved.");
}
