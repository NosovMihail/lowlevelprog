#include <stdio.h>
#include "subsidiary_funk.h"
#include "list_funk.h"
int main() {
    struct list *lst=list_read();

    printf("List elements: ");
    list_print(lst);
    printf("\n");
    printf("List size: ");
    print_int64(list_length(lst));

    printf("\n");
    printf("15 element: ");
    maybe_int64_print(list_at(lst,15));

    printf("\n");
    printf("List sum: ");
    maybe_int64_print(list_sum(lst));

    printf("\n");
    printf("Reverse list: ");
    list_print(list_reverse(lst));
    printf("\n");

    return 0;
}
