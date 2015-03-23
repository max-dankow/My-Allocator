#include <stdio.h>
#include "my-allocator.h"

int main()
{
    int* a1 = my_alloc(10);
    *a1 = 707;
    char* a2 = my_alloc(30);
    //a2[0] = 'Q';
    //a2[1] = 'T';
    //a2[2] = '\n';
    scanf("%s", a2);
    void* a3 = my_alloc(24);
    void* a4 = my_alloc(11);
    my_free(a3);
    void* b = my_alloc(5);
    void* a5 = my_alloc(2);
    my_free(a2);
    void* cq = my_alloc(9);

    printf("%s\n", *a1, a2);
    return 0;
}


