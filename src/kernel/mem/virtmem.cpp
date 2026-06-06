#include "kernel/mem/virtmem.h"

void init_virtmem(MB2_tag_memmap* memmap)
{
    size_t memmap_entries = (memmap->size - sizeof(MB2_tag_memmap)) / memmap->entry_size;
    for (size_t i = 0; i < memmap_entries; i++)
    {
        MB2_memmap_entry* entry = &memmap->entries[i];
        if (entry->type != MB2_MEM_AVAILABLE) continue;
        
        
    }
}

void* virtmem_alloc(size_t pages)
{
    
}

int virtmem_free(void* ptr, size_t pages)
{

}
