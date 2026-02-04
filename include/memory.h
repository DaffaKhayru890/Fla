#ifndef FLA_MEMORY_H
#define FLA_MEMORY_H

#include <stdlib.h>
#include <stddef.h>

#define ALLOCATE(type, count) \
    ((type*)allocate(NULL, sizeof(type) * (count)))

#define FREE(pointer) \
    (freeMemory(pointer))

#define GROW(type, pointer, newCapacity) \
    ((type*)reallocate((pointer), (sizeof(type) * (newCapacity))))

void *allocate(void *pointer, size_t size);
void *reallocate(void *pointer, size_t new_size);
void freeMemory(void *pointer);

#endif