

#include "mem.h"
#include "mem_debug.h"

#include <stdio.h>

struct game{
    int id;
    double rating;
    char* name;
};

int main() {

    void* heap_start = NULL;
    void* big_mem_test = mem_malloc(MEMORY_CHUNK * 3);

    heap_start = (char*) big_mem_test - sizeof(struct mem);
    memalloc_debug_heap(stdout, heap_start);

    

    struct game * fallout = mem_malloc(sizeof(struct game));
    fallout->id = 112830;
    fallout->rating = 0.86;
    fallout->name = "Fallout 2";

    memalloc_debug_heap(stdout, heap_start);


    struct game * divinity = mem_malloc(sizeof(struct game));
    divinity->id = 312367;
    divinity->rating = 0.87;
    divinity->name = "Divinity: Original Sin";

    memalloc_debug_heap(stdout, heap_start);

    

    struct game * cpunk = mem_malloc(sizeof(struct game));
    cpunk->id = 1714915;
    cpunk->rating = 0.56;
    cpunk->name = "Cyberpunk 2077";

    memalloc_debug_heap(stdout, heap_start);


    mem_free(cpunk);
    mem_free(divinity);
    mem_free(fallout);

    memalloc_debug_heap(stdout, heap_start);
}
