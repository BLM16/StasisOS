#pragma once

#include <stdint.h>

#define K_NULL '\x00' // Scan code not present

#define K_ESC  '\x01' // Escape
#define K_BKSP '\x0E' // Backspace
#define K_ENTR '\x1C' // Enter
#define K_LCTL '\x1D' // Left control
#define K_LSFT '\x2A' // Left shift
#define K_RSFT '\x36' // Right shift
#define K_LALT '\x38' // Left alt
#define K_CAPS '\x3A' // CapsLock
#define K_F1   '\x3B' // F1
#define K_F2   '\x3C' // F2
#define K_F3   '\x3D' // F3
#define K_F4   '\x3E' // F4
#define K_F5   '\x3F' // F5
#define K_F6   '\x40' // F6
#define K_F7   '\x41' // F7
#define K_F8   '\x42' // F8
#define K_F9   '\x43' // F9
#define K_F10  '\x44' // F10
#define K_NUML '\x45' // NumberLock
#define K_SCRL '\x46' // ScrollLock
#define K_F11  '\x57' // F11
#define K_F12  '\x58' // F12

namespace drivers::keyboard
{
    extern const char scan_code_set_1[];
}
