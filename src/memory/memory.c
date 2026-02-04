#include "../../include/memory.h"
#include <stdio.h>
#include <string.h>

void *allocate(void *pointer, size_t size) {
    if (size == 0) {
        fprintf(stderr, "Error: Cannot allocate 0 bytes\n");
        return NULL;
    }
    
    void *result = malloc(size);
    
    if (result == NULL) {
        fprintf(stderr, "Error: Failed to allocate %zu bytes\n", size);
        exit(EXIT_FAILURE);
    }
    
    memset(result, 0, size);
    
    return result;
}

void *reallocate(void *pointer, size_t new_size) {
    if (new_size == 0) {
        if (pointer != NULL) {
            free(pointer);
        }
        return NULL;
    }
    
    void *result = realloc(pointer, new_size);
    
    if (result == NULL) {
        fprintf(stderr, "Error: Failed to reallocate to %zu bytes\n", new_size);
        exit(EXIT_FAILURE);
    }
    
    return result;
}

void freeMemory(void* pointer) {
    if (pointer != NULL) {
        free(pointer);
    }
}