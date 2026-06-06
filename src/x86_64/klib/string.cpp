#include "klib/string.h"

void* memset(void* dest, int ch, size_t count)
{
    uint8_t* destination = (uint8_t*)dest;
    for (size_t i = 0; i < count; i++)
    {
        destination[i] = ch;
    }
    return dest;
}

void* memcpy(void* dest, const void* src, size_t count)
{
    const uint8_t* source = (uint8_t*)src;
    uint8_t* destination  = (uint8_t*)dest;

    for (size_t i = 0; i < count; i++)
    {
        destination[i] = source[i];
    }

    return dest;
}

size_t strlen(const char* str)
{
    const char* end = str;
    while (*end != '\0')
        ++end;
    return end - str;
}
