#pragma once

#include <stddef.h>
#include <stdint.h>
#include "util/attributes.h"

#define VGA_BUFFER ((VGA_Cell*) 0xB8000)

#define TAB_SIZE 4 // Size of a tab in spaces

namespace drivers::video::VGA
{
    namespace Color
    {
        typedef enum Color : uint8_t {
            BLACK,
            BLUE,
            GREEN,
            CYAN,
            RED,
            MAGENTA,
            BROWN,
            LIGHT_GRAY,
            DARK_GRAY,
            LIGHT_BLUE,
            LIGHT_GREEN,
            LIGHT_CYAN,
            LIGHT_RED,
            PINK,
            YELLOW,
            WHITE,
        } Color;

        /// @brief Converts a foreground and background color into their byte representation.
        /// @param foreground The foreground color.
        /// @param background The background color.
        /// @return The byte representation of the color.
        inline uint8_t from(Color foreground, Color background)
        {
            return background << 4 | foreground;
        }
    }

    /// @brief Represents a location in the VGA where there is a cursor.
    typedef struct Cursor {
        size_t row;
        size_t col;
    } Cursor;

    /// @brief Represents a single cell in the VGA tracking both the character and the brush for that character.
    typedef struct __packed VGA_Cell {
        uint8_t character;
        uint8_t color;
    } VGA_Cell;

    void clear_screen();

    void print_chr(uint8_t character);
    void print_str(const char* string);

    void set_color(uint8_t color);

    /// @brief Sets the active brush (foreground and background colors) to be used while printing to the VGA.
    /// @param foreground The foreground color to set as active.
    /// @param background The background color to set as active.
    inline void set_color(Color::Color foreground, Color::Color background)
    {
        set_color(Color::from(foreground, background));
    }
}
