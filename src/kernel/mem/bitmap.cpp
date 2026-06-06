#include "kernel/mem/bitmap.h"

bool bitmap::test(size_t bit) {
    return (data[BIT_TO_INDEX(bit)] >> (BIT_TO_OFFSET(bit))) & 1;
}

void bitmap::set(size_t bit) {
    data[BIT_TO_INDEX(bit)] |= 1 << (BIT_TO_OFFSET(bit));
}

void bitmap::clear(size_t bit) {
    data[BIT_TO_INDEX(bit)] &= ~(1 << (BIT_TO_OFFSET(bit)));
}
