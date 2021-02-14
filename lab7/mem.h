

#ifndef LAB7_MEM_H
#define LAB7_MEM_H

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>

#define MEMORY_CHUNK 4 * 1024 * 1024 // 4Kb
#define HEAP_START ((void*)0x04040000)
struct mem;

struct mem {
    struct mem* next;
    size_t capacity;
    char is_free;
};


void* mem_malloc(size_t query);
void  mem_free(void* mem);
void* heap_init(size_t initial_size);

#endif //LAB7_MEM_H
