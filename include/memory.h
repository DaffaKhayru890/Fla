#ifndef FLA_MEMORY_H
#define FLA_MEMORY_H

#include <stdlib.h>
#include <stddef.h>

#define ALLOCATE(type, count) \
    ((type*)allocate(NULL, sizeof(type) * (count)))

#define FREE(pointer) \
    (freeMemory(pointer))

#define GROW(type, pointer, newCount) \
    ((type*)reallocate((pointer), sizeof(type) * (newCount)))

#define GROW_CAPACITY(capacity) \
    (((capacity) < 8) ? 8 : ((capacity) * 2))

#define GROW_ARRAY(type, pointer, oldCapacity, newCapacity) \
    ((type*)reallocate((pointer), sizeof(type) * (newCapacity)))

void* allocate(void* pointer, size_t size);
void* reallocate(void* pointer, size_t new_size);
void freeMemory(void* pointer);

#endif