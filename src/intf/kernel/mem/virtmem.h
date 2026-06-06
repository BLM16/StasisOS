#pragma once

#include <stdint.h>
#include <stddef.h>

#include "multiboot2.h"
#include "kernel/mem/bitmap.h"

#define PAGE_SIZE 4096

extern "C" uint64_t PML4[];
extern "C" uint64_t PDPT[];
extern "C" uint64_t PDPT_HH[];
extern "C" uint64_t PD_KERN[];

void init_virtmem(MB2_tag_memmap* memmap);
void* virtmem_alloc(size_t pages);
int virtmem_free(void* ptr, size_t pages);
