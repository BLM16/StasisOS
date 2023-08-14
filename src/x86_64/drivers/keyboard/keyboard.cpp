#include "drivers/keyboard/keyboard.h"

namespace drivers::keyboard
{    
    /// @brief The states of the keyboard modifier keys.
    Key_State key_state = {
        .alt = false,
        .caps = false,
        .ctrl = false,
        .shift = false,
    };

    /// @brief Gets the character for a given key when shift is pressed.
    /// This will capitalize letters and return symbols as appropriate.
    /// If there is no shifted key variant for the given key, the given key returned.
    /// @param key The key to get the shifted variant of.
    /// @return The shifted variant of the key.
    uint8_t get_shifted_variant(uint8_t key)
    {
        if (key >= 'a' && key <= 'z')
        {
            return toupper(key); // Capitalize letters
        }
        
        switch (key)
        {
            case '1': return '!';
            case '2': return '@';
            case '3': return '#';
            case '4': return '$';
            case '5': return '%';
            case '6': return '^';
            case '7': return '&';
            case '8': return '*';
            case '9': return '(';
            case '0': return ')';
            case '-': return '_';
            case '=': return '+';
            case '[': return '{';
            case ']': return '}';
            case ';': return ':';
            case '\'': return '"';
            case '`': return '~';
            case '\\': return '|';
            case ',': return '<';
            case '.': return '>';
            case '/': return '?';

            default: return key;
        }
    }
}
