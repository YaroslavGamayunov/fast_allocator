//
// Created by Ярослав Гамаюнов on 2020-03-14.
//

#ifndef FAST_ALLOCATOR_FAST_ALLOCATOR_H
#define FAST_ALLOCATOR_FAST_ALLOCATOR_H

#include "../src/FixedAllocator.h"
#include "../src/memory_constants.h"

template<class T>
class FastAllocator {
public:
    typedef T value_type;
    template<class U>
    struct rebind {
        typedef FastAllocator<U> other;
    };

    T *allocate(size_t n) {
        void *ptr = nullptr;

        if (sizeof(T) == 4) {
            ptr = fixedAllocator4B.allocate(n);
        }
        if (sizeof(T) == 8) {
            ptr = fixedAllocator8B.allocate(n);
        }
        if (ptr == nullptr) {
            ptr = new T[n];
        }
        return (T *) ptr;
    }

    void deallocate(void *ptr, size_t n) {
        if (sizeof(T) != 4 && sizeof(T) != 8) {
            delete[] (T *) ptr;
        }
    }

    FastAllocator() {
        fixedAllocator4B = FixedAllocator<4>(500 * MIB);
        fixedAllocator8B = FixedAllocator<8>(500 * MIB);
    }

    FastAllocator(const FastAllocator<value_type> &other) = default;

    ~FastAllocator() {
        fixedAllocator8B.freeMemory();
        fixedAllocator4B.freeMemory();
    }

private:
    FixedAllocator<4> fixedAllocator4B;

    FixedAllocator<8> fixedAllocator8B;
};

#endif //FAST_ALLOCATOR_FAST_ALLOCATOR_H
