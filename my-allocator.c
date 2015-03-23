#include <my-allocator.h>

typedef struct Node
{
    struct Node *next, *prev;
    unsigned block_size;
} Node;

void *request_mem(unsigned space_amount)
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

void *my_alloc(unsigned space_amount)
{
    static void *in_node;

    if (in_node == NULL)
    {
        printf("First call.\n");

        //request 1 Mb block
        unsigned new_mem_size = 1 << 20;
        in_node = request_mem(new_mem_size);

        //init new block
        Node *new_block = (Node *) in_node;
        new_block->next = new_block;
        new_block->prev = new_block;
        new_block->block_size = new_mem_size;
    }
    else
    {
        Node *current_node = in_node;
        while (current_node != in_node)
        {
            if (current_node->block_size >= space_amount)
            {
                if (current_node->block_size - space_amount >= sizeof(Node))
                {
                    Node *new_block = (Node *) in_node;
                    new_block->next = current_node->next;
                    new_block->prev = current_node->prev;
                    new_block->block_size = current_node->block_size - space_amount;
                }
                else
                {
                    current_node->prev->next = current_node->next;
                    current_node->next->prev = current_node->prev;
                }
            }
            current_node = current_node->next;
        }

        printf("Second call.\n");
    }

    return in_node;
}
