#include <stdio.h>
#include "my-allocator.h"

int main()
{
    //
    char* a2 = my_malloc(30);
    strcpy(a2, "test");

    printf("%s\n", a2);

    int* a1 = my_malloc(10);

    void* a3 = my_malloc(1);
    //my_free(a1);

    char *a33 = my_realloc(a2, 40);
    a2 = a33;
    strcpy(a2, "012345678901234567890");
    printf("%s\n", a33);

    a33 = my_realloc(a2, 1000);
    //a2 = a33;
    //strcpy(a2, "012345678901234567890");
    printf("%s\n", a33);

    void* b = my_malloc(10);
    my_free(a1);
    a3 = my_realloc(a3, 2);

    /*my_free(a3);
    void* b = my_malloc(10);
    void* a5 = my_malloc(1);
    void* cq = my_malloc(9);

    //my_free(a1);

    char *re_a2 = my_malloc(30);
    printf("%s\n", re_a2);
    void* a4 = my_malloc(113);

    my_free(a3);
    my_free(a1);
    void* b = my_malloc(10);
    void* a5 = my_malloc(1);
    void* cq = my_malloc(9);

    //printf("%s\n", *a1, a2);*/
    return 0;
}


