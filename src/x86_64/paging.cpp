#include "paging.h"

/// @brief Gets a physical address from its corresponding virtual address.
/// @param virtual_address The virtual memory address.
/// @param pml4_base The address of the PML4 table.
/// @param flags The expected flags for the address.
/// @return The physical address on success, PhysicalAddress {0, 0} on failure.
PhysicalAddress get_physical_addr_from(uintptr_t virtual_address, uintptr_t pml4_base, uint16_t flags) {
    // Extract the four level indices from the virtual address
    uint64_t pml4_index = (virtual_address >> 39) & 0x1FF; // Bits 39-47
    uint64_t pdp_index = (virtual_address >> 30) & 0x1FF; // Bits 30-38
    uint64_t pd_index = (virtual_address >> 21) & 0x1FF; // Bits 21-29
    uint64_t pt_index = (virtual_address >> 12) & 0x1FF; // Bits 12-20

    // Get the page table entry from the PML4 table
    uint64_t pml4_entry = get_pte(pml4_base, pml4_index);

    // Ensure the PML4 entry is present and has the required flags
    if ((pml4_entry & ENTRY_PRESENT) == 0 || (pml4_entry & flags) != flags) {
        return {0, 0};
    }

    // Get the page table base address from the PML4 entry
    uintptr_t pdp_base = pml4_entry & 0xFFFFFFFFF000; // Bits 12-51

    // Get the page table entry from the PDP table
    uint64_t pdp_entry = get_pte(pdp_base, pdp_index);

    // Ensure the PDP entry is present and has the required flags
    if ((pdp_entry & ENTRY_PRESENT) == 0 || (pdp_entry & flags) != flags) {
        return {0, 0};
    }

    // Check if the PDP entry is a large page (1 GB)
    if ((pdp_entry & ENTRY_PS) != 0) {
        // The PDP entry is a large page, extract the physical address and the flags from it
        uint64_t physical_address = pdp_entry & 0xFFFFFC0000000; // Bits 30-51
        uint16_t physical_flags = pdp_entry & 0xFFF; // Bits 0-11

        // Add the offset from the virtual address to the physical address
        physical_address += virtual_address & 0x3FFFFFFF; // Bits 0-29

        // Return the physical address and the flags
        return {physical_address, physical_flags};
    }

    // Get the page table base address from the PDP entry
    uintptr_t pd_base = pdp_entry & 0xFFFFFFFFF000; // Bits 12-51

    // Get the page table entry from the PD table
    uint64_t pd_entry = get_pte(pd_base, pd_index);

    // Ensure the PD entry is present and has the required flags
    if ((pd_entry & ENTRY_PRESENT) == 0 || (pd_entry & flags) != flags) {
        return {0, 0};
    }

    // Check if the PD entry is a large page (2 MB)
    if ((pd_entry & ENTRY_PS) != 0) {
        // The PD entry is a large page, extract the physical address and the flags from it
        uint64_t physical_address = pd_entry & 0xFFFFFFE00000; // Bits 21-51
        uint16_t physical_flags = pd_entry & 0xFFF; // Bits 0-11

        // Add the offset from the virtual address to the physical address
        physical_address += virtual_address & 0x1FFFFF; // Bits 0-20

        // Return the physical address and the flags
        return {physical_address, physical_flags};
    }

    // Get the page table base address from the PD entry
    uintptr_t pt_base = pd_entry & 0xFFFFFFFFF000; // Bits 12-51

    // Get the page table entry from the PT table
    uint64_t pt_entry = get_pte(pt_base, pt_index);

    // Ensure the PT entry is present and has the required flags
    if ((pt_entry & ENTRY_PRESENT) == 0 || (pt_entry & flags) != flags) {
        return {0, 0};
    }

    // The PT entry is a normal page (4 KB), extract the physical address and the flags from it
    uint64_t physical_address = pt_entry & 0xFFFFFFFFF000; // Bits 12-51
    uint16_t physical_flags = pt_entry & 0xFFF; // Bits 0-11

    // Add the offset from the virtual address to the physical address
    physical_address += virtual_address & 0xFFF; // Bits 0-11

    // Return the physical address and the flags
    return {physical_address, physical_flags};
}

/// @brief Insert an entry into the appropriate page table to map a virtual address to a physical one
/// @param virtual_address The virtual address to map.
/// @param physical_address The physical address the virual one should map to.
/// @param pml4_base The address of the PML4 table.
void insert_mapping(uintptr_t virtual_address, PhysicalAddress physical_address, uintptr_t pml4_base) {
    // Extract the four level indices from the virtual address
    uint64_t pml4_index = (virtual_address >> 39) & 0x1FF; // Bits 39-47
    uint64_t pdp_index = (virtual_address >> 30) & 0x1FF; // Bits 30-38
    uint64_t pd_index = (virtual_address >> 21) & 0x1FF; // Bits 21-29
    uint64_t pt_index = (virtual_address >> 12) & 0x1FF; // Bits 12-20

    // Get the page table entry from the PML4 table
    uint64_t pml4_entry = get_pte(pml4_base, pml4_index);

    // Ensure the PML4 entry is present or allocate a new PDP table and save it to PML4
    if ((pml4_entry & ENTRY_PRESENT) == 0) {
        uintptr_t pdp_base = alloc_pt();
        pml4_entry = pdp_base | ENTRY_PRESENT;
        set_pte(pml4_base, pml4_index, pml4_entry);
    }

    // Get the page table base address from the PML4 entry
    uintptr_t pdp_base = pml4_entry & 0xFFFFFFFFF000; // Bits 12-51

    // Get the page table entry from the PDP table
    uint64_t pdp_entry = get_pte(pdp_base, pdp_index);

    // Ensure the PDP entry is present or allocate a new PD table and save it to PDP
    if ((pdp_entry & ENTRY_PRESENT) == 0) {
        uintptr_t pd_base = alloc_pt();
        pdp_entry = pd_base | ENTRY_PRESENT;
        set_pte(pdp_base, pdp_index, pdp_entry);
    }

    // Get the page table base address from the PDP entry
    uintptr_t pd_base = pdp_entry & 0xFFFFFFFFF000; // Bits 12-51

    // Get the page table entry from the PD table
    uint64_t pd_entry = get_pte(pd_base, pd_index);

    // Ensure the PD entry is present or allocate a new PT table and save it to PD
    if ((pd_entry & ENTRY_PRESENT) == 0) {
        uintptr_t pt_base = alloc_pt();
        pd_entry = pt_base | ENTRY_PRESENT;
        set_pte(pd_base, pd_index, pd_entry);
    }

    // Get the page table base address from the PD entry
    uintptr_t pt_base = pd_entry & 0xFFFFFFFFF000; // Bits 12-51

    // Set the page table entry in the PT table with the physical address and the flags
    uint64_t pt_entry = (physical_address.address & 0xFFFFFFFFF000) | (physical_address.flags & 0xFFF);
    set_pte(pt_base, pt_index, pt_entry);
}
