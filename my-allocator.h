#include <unistd.h>
#include <stdio.h>
#include <string.h>

void *my_malloc(unsigned space_amount);
void my_free(void *ptr);
void *my_calloc(unsigned space_amount);
