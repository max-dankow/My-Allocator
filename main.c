#include <stdio.h>
#include "my-allocator.h"

int main()
{
    //
    char* a2 = my_alloc(30);
    int* a1 = my_alloc(10);
    void* a3 = my_alloc(1);

    void* a4 = my_alloc(11);

    my_free(a3);
    my_free(a1);
    void* b = my_alloc(10);
    void* a5 = my_alloc(2);
    void* cq = my_alloc(9);

    //printf("%s\n", *a1, a2);
    return 0;
}


