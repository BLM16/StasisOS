#pragma once

#include <stdarg.h>

#define PRINTF_BUFFER_SIZE (8 * sizeof(int) + 1) // 1 char per byte + null terminator

/// @brief Converts an integer into a string with a radix.
/// @param val The integer to convert.
/// @param buf The string buffer to write to.
/// @param radix The radix of the integer to write.
/// @return A pointer to the written buffer.
char* itoa(int val, char* buf, int radix);

/// @brief Writes the string pointed to by `fmt` to the VGA buffer.
/// When format specifiers are present, they are replaced by the
/// corresponding additional arguments.
/// @param fmt The string with optional format specifiers to print. 
void printf(const char* fmt, ...);

/// @brief Writes the string pointed to by `fmt` to the VGA buffer.
/// When format specefiers are present, they are replaced by the
/// corresponding additional arguments.
/// @param fmt The string with optional format specifiers to print.
/// @param args The argument list.
void vprintf(const char* fmt, va_list args);
