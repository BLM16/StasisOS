/*
 * This memory manager "liballoc" is taken from https://github.com/blanham/liballoc.
 * It is licensed in the public domain.
 */

#pragma once

#include <stddef.h>
#include <stdint.h>

/// @brief This function is supposed to lock the memory data structures.
/// It could be as simple as disabling interrupts or acquiring a spinlock.
/// @return 0 if the lock was acquired successfully. Anything else is failure.
extern "C" int liballoc_lock();

/// @brief This function unlocks what was previously locked by the liballoc_lock
/// function. If it disabled interrupts, it enables interrupts. If it
/// had acquiried a spinlock, it releases the spinlock. etc.
/// @return 0 if the lock was successfully released.
extern "C" int liballoc_unlock();

/// @brief This is the hook into the local system which allocates pages.
/// The page size was set up in the liballoc_init function.
/// @param pages The number of pages required.
/// @return A pointer to the allocated memory or NULL if the pages were not allocated.
extern "C" void* liballoc_alloc(size_t pages);

/// @brief This frees previously allocated memory.
/// @param ptr The same value returned from a previous liballoc_alloc call.
/// @param pages The number of pages to free.
/// @return 0 if the memory was successfully freed.
extern "C" int liballoc_free(void* ptr, size_t pages);

extern void *kmalloc(size_t);
extern void *krealloc(void *, size_t);
extern void *kcalloc(size_t, size_t);
extern void  kfree(void *);
