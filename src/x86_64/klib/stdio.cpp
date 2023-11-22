#include "klib/stdio.h"
#include "drivers/video/vga.h"

namespace VGA = drivers::video::VGA;
namespace Color = VGA::Color;

static inline void swap(char& a, char& b)
{
    char temp = a;
    a = b;
    b = temp;
}

static void reverse(char* str, int length)
{
    int start = 0;
    int end = length - 1;
    while (start < end)
    {
        swap(str[start], str[end]);
        start++;
        end--;
    }
}

char* itoa(int val, char* buf, int radix)
{
    // Handle 0 explicitly, otherwise empty string is printed
    if (val == 0)
    {
        buf[0] = '0';
        buf[1] = '\0';
        return buf;
    }

    // Process individual digits
    int i = 0;
    bool isNegative = false;

    if (val < 0 && radix == 10)
    {
        isNegative = true;
        val = -val;
    }

    if (radix == 16)
    {
        while (val != 0)
        {
            int rem = val % radix;
            buf[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
            val = val / radix;
        }
    }
    else
    {
        while (val != 0)
        {
            int rem = val % radix;
            buf[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
            val = val / radix;
        }
    }

    // Append negative sign for base 10
    if (isNegative && radix == 10)
    {
        buf[i++] = '-';
    }

    buf[i] = '\0';

    reverse(buf, i);
    return buf;
}

void printf(const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    vprintf(fmt, args);

    va_end(args);
}

void vprintf(const char* fmt, va_list args)
{
    char buf[PRINTF_BUFFER_SIZE];

    va_list vargs;
    va_copy(vargs, args);

    while (*fmt != '\0')
    {
        if (*fmt != '%')
        {
            VGA::print_chr(*fmt);
        }
        else
        {
            fmt++;
            switch (*fmt)
            {
                case '%':
                {
                    // Escaped % character
                    VGA::print_chr('%');
                    break;
                }
                case 'd':
                {
                    int value = va_arg(vargs, int);
                    itoa(value, buf, 10);
                    VGA::print_str(buf);
                    break;
                }
                case 's':
                {
                    const char* str = va_arg(vargs, const char*);
                    VGA::print_str(str);
                    break;
                }
                case 'x':
                {
                    int value = va_arg(vargs, int);
                    itoa(value, buf, 16);
                    VGA::print_str(buf);
                    break;
                }
                case 'c':
                {
                    char c = va_arg(vargs, int);
                    VGA::print_chr(c);
                    break;
                }

                default:
                    printf("Err: unsupported format %%%c", *fmt);
                    break;
            }
        }

        fmt++;
    }

    va_end(vargs);
}
