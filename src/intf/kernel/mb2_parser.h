#pragma once

#include "multiboot2.h"

extern "C" uintptr_t KERNEL_VMA;

/// @brief Parses the multiboot2 information structure for relevant
/// information to the kernel and updates data with the parsed values.
/// @param MBI A pointer to the multiboot2 information structure.
void parse_multiboot(const MB2_information_structure* MBI);
