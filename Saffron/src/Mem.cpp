#include "Core.h"

//#define DEBUG_MEM


#ifdef DEBUG_MEM

static size_t g_totalMemory = 0;

void* operator new(std::size_t size) {
    void* ptr = std::malloc(size);
    if (!ptr) throw std::bad_alloc();

    g_totalMemory += size;
    SF_CORE_WARN_("Allocated " << size 
              << " bytes, total = " << g_totalMemory, "(--DEBUG_MEM--)");

    return ptr;
}

void operator delete(void* ptr) noexcept {
    if (!ptr) return;
    // We don’t know the size here unless we track it separately.
    // For simplicity, just log the free.
    SF_CORE_WARN_("Freed memory @ " << ptr 
              << " (total still = " << g_totalMemory << ")", "(--DEBUG_MEM--)");
    std::free(ptr);
}

void* operator new[](std::size_t size) {
    return ::operator new(size);
}

void operator delete[](void* ptr) noexcept {
    ::operator delete(ptr);
}

#endif // DEBUG_MEM