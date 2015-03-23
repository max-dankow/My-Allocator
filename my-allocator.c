#include <my-allocator.h>

typedef struct Node
{
    struct Node *next, *prev;
} Node;

void *request_mem(size_t space_amount)
{
    void *allocated_mem = sbrk(space_amount);

    if (allocated_mem == ((void *) -1))
    {
        fprintf(stderr, "Can't move program break.\n");
        return NULL;
    }
    else
    {
        return allocated_mem;
    }
}

void *my_alloc(size_t space_amount)
{
    static void *in_node;

    if (in_node == NULL)
    {
        printf("First call.\n");

        //request 1 Mb block
        in_node = request_mem(1 << 20);

        //init new block
        Node *new_block = (Node *) in_node;
        new_block->next = NULL;
        new_block->prev = NULL;
    }
    else
    {
        //пройти по списку свободных
        //найти где нам хватит места
        //отрезать кусок
        //вставить остаток в список
        //иначе запросить еще и создать новый блок
        printf("Second call.\n");
    }

    return in_node;
}
