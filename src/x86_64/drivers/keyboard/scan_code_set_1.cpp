#include "drivers/keyboard/scan_code_set_1.h"

namespace drivers::keyboard
{
    /// @brief The scan code set 1 for PS/2 keyboards.
    /// The scan code list can be found at https://wiki.osdev.org/Keyboard#Scan_Code_Set_1.
    const char scan_code_set_1[] = {
        K_NULL, K_ESC, '1', '2',
        '3', '4', '5', '6',
        '7', '8', '9', '0',
        '-', '=', K_BKSP, '\t',
        'q', 'w', 'e', 'r',
        't', 'y', 'u', 'i',
        'o', 'p', '[', ']',
        K_ENTR, K_LCTL, 'a', 's',
        'd', 'f', 'g', 'h',
        'j', 'k', 'l', ';',
        '\'', '`', K_LSFT, '\\',
        'z', 'x', 'c', 'v',
        'b', 'n', 'm', ',',
        '.', '/', K_RSFT, '*',
        K_LALT, ' ', K_CAPS, K_F1,
        K_F2, K_F3, K_F4, K_F5,
        K_F6, K_F7, K_F8, K_F9,
        K_F10, K_NUML, K_SCRL, '7',
        '8', '9', '-', '4',
        '5', '6', '+', '1',
        '2', '3', '0', '.',
        K_NULL, K_NULL, K_NULL, K_F11,
        K_F12, K_NULL, K_NULL, K_NULL,
    };
}
