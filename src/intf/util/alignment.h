#pragma once

#define ALIGN_ADJUSTMENT(addr, align) (align - (addr & (align - 1)))
#define ALIGN(addr, align) (addr + ALIGN_ADJUSTMENT(addr, align))
