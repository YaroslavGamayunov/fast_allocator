//
// Created by Ярослав Гамаюнов on 2020-03-13.
//

#ifndef FAST_ALLOCATOR_FIXED_ALLOCATOR_H
#define FAST_ALLOCATOR_FIXED_ALLOCATOR_H

#include <cstdio>
#include <cstdlib>
#include "memory_constants.h"

template<size_t chunkSize>
class FixedAllocator {
public:
    FixedAllocator(size_t initSize = 1 * MIB) {
        memoryBegin = (char *) malloc(initSize);
        allocPointer = (char *) memoryBegin;
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

    void freeMemory() {
        free(memoryBegin);
    }

//    ~FixedAllocator() {
//        std::cout << "(destructor)memory begin at " << (void *) memoryBegin << " id=" << id << "\n";
//        free(memoryBegin);
//        memoryBegin = 0;
//    }

private:
    char *memoryBegin;
    char *allocPointer = nullptr;
    size_t freeMemorySize;
};

//template<size_t chunkSize>
//void *FixedAllocator<chunkSize>::allocateBlock(size_t n, size_t initiallyAllocatedSize) {
//    char *allocatedMemoryBegin = (char *) malloc(n);
//    allocPointer = allocatedMemoryBegin + initiallyAllocatedSize;
//
//    freeMemorySize = n - initiallyAllocatedSize;
//    poolMemorySize = n;
//
//    return allocatedMemoryBegin;
//

#endif //FAST_ALLOCATOR_FIXED_ALLOCATOR_H
