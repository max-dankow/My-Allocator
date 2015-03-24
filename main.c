#include <stdio.h>
#include "my-allocator.h"

int main()
{
    //
    char* a2 = my_malloc(30);
    int* a1 = my_malloc(10);
    void* a3 = my_malloc(1);

    void* a4 = my_malloc(11);

    my_free(a3);
    my_free(a1);
    void* b = my_malloc(10);
    void* a5 = my_malloc(1);
    void* cq = my_malloc(9);

    //printf("%s\n", *a1, a2);
    return 0;
}


