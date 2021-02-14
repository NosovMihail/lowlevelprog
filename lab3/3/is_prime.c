#include <inttypes.h>
#include <stdio.h>
#include <math.h>

void print_string(const char* mess){
    printf("%s \n", (const char *) mess);
}
 uint32_t scan_uint32_t(){
    uint32_t num;
    scanf("%"SCNu32,&num);
    return (const uint32_t) num;
}
 uint32_t is_prime(const uint32_t n){
    uint32_t i;
    if(n<2) {
        return 0;
    }
    if(n % 2 == 0) {
        return 0;
    }
    for(i = 3; i < sqrt(n); i = i + 2) {
        if(n % i == 0) {
            return 0;
        }
    }
    return 1;
}
int main(){
    const uint32_t num=scan_uint32_t();
    if(is_prime(num)==1) print_string("yes");
    else print_string("no");
    return 0;
}