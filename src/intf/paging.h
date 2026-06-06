#pragma once

#include <stdint.h>
#include "klib/memory.h"

#define ENTRY_PRESENT   1 << 0  // Present
#define ENTRY_WRITEABLE 1 << 1  // Writable when set, else readonly
#define ENTRY_USER      1 << 2  // Ring 3 accessible when set, else ring 0 only
#define ENTRY_PWT       1 << 3  // Write-through caching enabled when set
#define ENTRY_PCD       1 << 4  // Page caching in TLD disabled when set
#define ENTRY_PS        1 << 7  // Page size is large page when set
#define ENTRY_GLOBAL    1 << 8  // Global page not invalidated in TLB upon a MOV to CR3 when set
#define ENTRY_NOEXEC    1 << 63 // Execute disabled for memory when set

extern "C" uintptr_t BOOT_LMA;
extern "C" uintptr_t KERNEL_LMA;
extern "C" uintptr_t KERNEL_VMA;

extern "C" uint64_t PML4[512];

/// @brief Represents a physical address and its corresponding flags.
struct PhysicalAddress {
    uintptr_t address; // The 52-bit physical address
    uint16_t flags;    // The 12-bit flags
};

/// @brief Gets a page table entry from a page table at a specified index.
/// @param pt_base The base page table address.
/// @param index The index of the page table entry.
/// @return The page table entry at the specified index.
inline uint64_t get_pte(uintptr_t pt_base, uint64_t index) {
    return *((uintptr_t*)(pt_base + index * 8));
}

/// @brief Creates a page table entry in a page table at a specified index.
/// @param pt_base The base page table address.
/// @param index The target index of the page table entry.
/// @param pte The page table entry to insert.
inline void set_pte(uintptr_t pt_base, uint64_t index, uint64_t pte) {
    *((uintptr_t*)(pt_base + index * 8)) = pte;
}

/// @brief Allocates memory for a new page table.
/// @return The address of the new page table.
inline uintptr_t alloc_pt() {
    return (uintptr_t)kmalloc(4096);
}

PhysicalAddress get_physical_addr_from(uintptr_t virtual_address, uintptr_t pml4_base, uint16_t flags);
void insert_mapping(uintptr_t virtual_address, PhysicalAddress physical_address, uintptr_t pml4_base);

/// @brief Maps a virtual address to the same physical address.
/// @param addr The address to identity map.
/// @param flags The flags to set for the entry.
/// @param pml4_base The address of the PML4 table.
inline void identity_map(uintptr_t addr, uint16_t flags, uintptr_t pml4_base) 
{
    insert_mapping(addr, PhysicalAddress { addr, flags }, pml4_base);
}
