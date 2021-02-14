#include <inttypes.h>
#include <stdio.h>
#include <malloc.h>
#include "arr_lib.h"


int64_t array_sum(const int64_t* arr,const size_t size ){
    int64_t sum=0;
    for(size_t i=0;i<size;i++){
        sum+=arr[i];
    }
    return sum;
}
void print_int64_t(const int64_t num){
    printf("%" PRId64, num);
    printf("\n");
}


int main(){
    size_t size=0;
    const int64_t arr= (const int64_t) array_int_read(&size);
    const int64_t sum= array_sum((const int64_t *) arr, size);
    print_int64_t(sum);
    return 0;
}