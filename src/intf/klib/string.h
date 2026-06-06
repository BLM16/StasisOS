#pragma once

#include <stddef.h>
#include <stdint.h>

void* memset(void* dest, int ch, size_t count);
void* memcpy(void* dest, const void* src, size_t count);

size_t strlen(const char* str);
