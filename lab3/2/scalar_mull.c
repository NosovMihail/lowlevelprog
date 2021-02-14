#include <inttypes.h>
#include <stdio.h>
#include "arr_lib.h"
#include <malloc.h>

void print_err(const char* mess){
    fprintf(stderr,"%s \n", (const char*) mess);
}
const int64_t* scalar_mull(const int64_t* arr1,const int64_t* arr2,const size_t size){
    int64_t* scalar_arr=malloc(sizeof(int64_t)*(size));
    for(size_t i=0;i<size;i++){
        scalar_arr[i]=arr1[i]*arr2[i];
    }
    return scalar_arr;
}
int main(){
    size_t size1=0;
    size_t size2=0;
    char mess[]="Sizes of arrays are different";
    const int64_t *arr_1= (const int64_t*) array_int_read(&size1);
    const int64_t *arr_2= (const int64_t*) array_int_read(&size2);
    if (size1!=size2) {
        print_err((const char *) &mess);
        return 0;
    }
    const int64_t* scalar_arr=scalar_mull(arr_1,arr_2,size1);
    array_int64_t_print(scalar_arr,size1);

    return 0;
}