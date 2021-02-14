#include <inttypes.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

void print_int64(int64_t i) { printf("%"PRId64, i); }
void print_size(size_t i) { printf("%zu", i); }

struct maybe_int64 {int64_t value; bool valid;};
struct maybe_int64 some_int64(int64_t i) {return (struct maybe_int64) { i, true };}
const struct maybe_int64 none_int64 = { 0 };

void maybe_int64_print( struct maybe_int64 i ) {
    if (i.valid) printf("Some %" PRId64, i.value );
    else printf("None");
}

// Считать число с входа
// Если scanf возвращает константу EOF, то больше на входе ничего нет

struct maybe_int64 read_int64() {
    int64_t b;
    int64_t a=scanf("%" SCNd64,&b);
    if(a==0||a==EOF ) return none_int64;
    else return some_int64(b);
}