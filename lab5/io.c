#include <stdio.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdlib.h>

#include "io.h"

#include "maybe_int.h"

struct maybe_int64 read_int64() {
    int64_t b;
    int64_t a=scanf("%" SCNd64,&b);
    if(a==0||a==EOF ) return none_int64;
    else return some_int64(b);
}

size_t read_size() { size_t i; scanf("%zu", &i); return i; }
void print_uint64( uint64_t i ) { printf("%" PRIu64 , i); }
void print_int64( int64_t i ) { printf("%" PRId64 , i); }
void print_newline(void) { printf("\n"); }

void err( const char* msg, ... ) {
  va_list args;
  va_start (args, msg);
  vfprintf(stderr, msg, args);
  va_end (args);
  abort();
}
