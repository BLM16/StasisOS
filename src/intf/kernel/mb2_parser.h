#pragma once

#include "multiboot2.h"

extern "C" uintptr_t KERNEL_VMA;

/// @brief Parses the multiboot2 information structure for relevant
/// information to the kernel and updates data with the parsed values.
/// @param MBI A pointer to the multiboot2 information structure.
void parse_multiboot(const MB2_information_structure* MBI);

/// @brief Parses the multiboot2 memory map tag and entries to
/// collect information about the available memory regions.
/// @param memmap_tag The memory map tag to parse.
void parse_memmap(MB2_tag_memmap* memmap_tag);
