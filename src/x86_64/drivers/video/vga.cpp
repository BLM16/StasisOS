#include "drivers/video/vga.h"

namespace drivers::video::VGA
{
    const static size_t NUM_COLS = 80; // The number of columns in the VGA
    const static size_t NUM_ROWS = 25; // The number of rows in the VGA

    /// @brief The currently active brush/color for printing to the VGA.
    uint8_t current_color = Color::from(Color::WHITE, Color::BLACK);

    /// @brief The current location of the cursor on the VGA.
    static Cursor cursor = {
        .row = 0,
        .col = 0,
    };

    /// @brief Clears the specified row of the VGA.
    /// @param row The row index to clear.
    static void clear_row(size_t row)
    {
        const VGA_Cell empty = {
            .character = ' ',
            .color = Color::from(Color::WHITE, Color::BLACK),
        };

        for (size_t col = 0; col < NUM_COLS; col++)
        {
            VGA_BUFFER[col + NUM_COLS * row] = empty;
        }
    }

    /// @brief Clears the entire VGA.
    void clear_screen()
    {
        cursor.row = 0;
        cursor.col = 0;

        for (size_t i = 0; i < NUM_ROWS; i++)
        {
            clear_row(i);
        }
    }

    /// @brief Prints a new line to the VGA by updating the cursor's location.
    /// Handles shifting all the lines up when the entire array is filled.
    static void print_newline()
    {
        cursor.col = 0;

        // Screen still has rows beneath
        if (cursor.row < NUM_ROWS - 1)
        {
            cursor.row++;
            return;
        }

        // Shift all rows up 1
        for (size_t row = 1; row < NUM_ROWS; row++)
        {
            for (size_t col = 0; col < NUM_COLS; col++)
            {
                VGA_BUFFER[col + NUM_COLS * (row - 1)] = VGA_BUFFER[col + NUM_COLS * row];
            }
        }

        // Clear the last row
        clear_row(NUM_ROWS - 1);
    }

    /// @brief Prints a tab to the VGA by updating the cursor's location.
    static void print_tab()
    {
        cursor.col += TAB_SIZE;
    }
    
    /// @brief Prints a single character to the VGA at the current cursor location.
    /// @param character The character to print.
    void print_chr(uint8_t character)
    {
        if (character == '\n')
        {
            print_newline();
            return;
        }

        if (character == '\t')
        {
            print_tab();
            return;
        }

        if (cursor.col >= NUM_COLS)
        {
            print_newline();
        }

        VGA_BUFFER[cursor.col + NUM_COLS * cursor.row] = (VGA_Cell) {
            .character = character,
            .color = current_color,
        };

        cursor.col++;
    }

    /// @brief Prints a null-terminated string to the VGA starting at the current cursor location.
    /// Keeps printing the given string until a null byte is encountered.
    /// @param str The string to print. Must be null-terminated.
    void print_str(const char* str)
    {
        for (size_t i = 0; true; i++)
        {
            uint8_t character = str[i];

            if (character == '\0')
            {
                return;
            }
            
            print_chr(character);
        }
    }

    /// @brief Sets the active brush (foreground and background colors) to be used while printing to the VGA.
    /// @param color The byte representing the color to set as active.
    void set_color(uint8_t color)
    {
        current_color = color;
    }
}
