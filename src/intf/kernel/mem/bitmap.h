#pragma once

#include <stddef.h>
#include <stdint.h>

#define BIT_TO_INDEX(n)  (n / (8 * sizeof(size_t)))
#define BIT_TO_OFFSET(n) (n % (8 * sizeof(size_t)))

typedef struct bitmap {
private:
    size_t length;
    size_t* data;

public:
    bitmap(void* data, size_t length) : length(length), data(reinterpret_cast<size_t*>(data))
    {
        memset(data, 0, DIV_ROUND_UP(length, sizeof(size_t)) * sizeof(size_t));
    }

    inline bool test(size_t bit);
    inline void set(size_t bit);
    inline void clear(size_t bit);
} bitmap;
