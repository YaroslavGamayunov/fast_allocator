//
// Created by Ярослав Гамаюнов on 2020-03-13.
//

#ifndef FAST_ALLOCATOR_FIXED_ALLOCATOR_H
#define FAST_ALLOCATOR_FIXED_ALLOCATOR_H

#include <cstdio>
#include <cstdlib>
#include "memory_constants.h"

struct MemoryDeleter {
    template<typename T>
    void operator()(T *pointer) {
        free(pointer);
    }
};

template<size_t chunkSize>
class FixedAllocator {
public:
    FixedAllocator(size_t initSize = 1 * MIB) {
        memoryBegin = std::shared_ptr<char>((char *) malloc(initSize), MemoryDeleter());
        allocPointer = memoryBegin.get();
        freeMemorySize = initSize;
    }

    void *allocate(size_t n) {
        size_t allocationMemorySize = n * chunkSize;
        if (allocationMemorySize > freeMemorySize) {
            return nullptr;
        }
        void *allocatedMemoryBegin = allocPointer;
        allocPointer += allocationMemorySize;
        freeMemorySize -= allocationMemorySize;
        return allocatedMemoryBegin;
    }

    void deallocate(void *ptr, size_t n) {

    }

private:
    std::shared_ptr<char> memoryBegin;
    char *allocPointer = nullptr;
    size_t freeMemorySize;
};

#endif //FAST_ALLOCATOR_FIXED_ALLOCATOR_H
