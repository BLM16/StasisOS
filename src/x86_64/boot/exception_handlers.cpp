#include "isr.h"

namespace VGA = drivers::video::VGA;
namespace Color = VGA::Color;

/// @brief The mnemonics for the different exceptions.
/// These can be found at https://wiki.osdev.org/Exceptions.
const char* exception_names[] = {
    "DE", "DB", "02", "BP",
    "OF", "BR", "UD", "NM",
    "DF", "09", "TS", "NP",
    "SS", "GP", "PF", "15",
    "MF", "AC", "MC", "XF",
    "VE", "CP", "22", "23",
    "24", "25", "26", "27",
    "HV", "VC", "SX", "31",
};

/// @brief Handles all the exceptions for interrupt vectors 0x00-0x1F.
/// @param frame The stack frame for the exception.
void exception_handler(Exception_Stack_Frame frame)
{
    const char* exception_name = exception_names[frame.int_no];

    VGA::set_color(Color::WHITE, Color::RED);
    VGA::print_str("ERR: #");
    VGA::print_str(exception_name);
}
