//
// Created by kurt on 05.01.2021.
//
#include <inttypes.h>
#include <stdio.h>
#include <malloc.h>

void array_int_fill( int64_t* array, size_t size ) {
    for(size_t i=0;i<size;i++){
        scanf( "%" SCNd64, &array[i] );
    }

}
int64_t* array_int_read( size_t* size ) {
    scanf( "%zu", size );
    int64_t* point= malloc(sizeof(int64_t)*(*size));
    array_int_fill(point,*size);
    return point;
}
void array_int64_t_print(int64_t const* array, size_t size) {
    for( size_t i = 0; i < size; i = i + 1) {
        printf( "%" PRId64 " ", array[i] );
    }
    printf("\n");
}