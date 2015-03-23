#include <my-allocator.h>

static const char IS_FREE = 1;
static const char NOT_FREE = 0;

static const unsigned mem_to_request = 100;

void *in_node;

//16 bytes
typedef struct Header
{
    unsigned block_size;
    char is_free;
    struct Header *next, *prev;
} Header;

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

void print_mem_list(Header *in_node)
{
    //printf("MEMORY\n");
    Header *current_node = in_node;

    while (current_node != NULL)
    {
        printf("\033[35m%p - %d(HEADER)\033[0\n", current_node, sizeof(Header));

        if (current_node->is_free == IS_FREE)
            printf("\033[32m%p - %d(FREE)\033[0m\n\n", (char*)current_node + sizeof(Header), current_node->block_size);
        else
            printf("\033[31m%p - %d(ALLOC)\033[0m\n\n", (char*)current_node + sizeof(Header), current_node->block_size);
        current_node = current_node->next;
    }
    printf("\n");
}

void *my_alloc(unsigned space_amount)
{
    printf("\033[0mALLOC: %d\033[0m\n", space_amount);
    //static void *in_node;

    if (in_node == NULL)
    {
        //printf("First call.\n");

        //request 1 Mb block
        //unsigned new_mem_size = /*1 << 20*/ 200;
        in_node = request_mem(mem_to_request);

        if (in_node == NULL)
        {
            return NULL;
        }

        //init new block
        Header *new_block = (Header*) in_node;
        new_block->next = NULL;
        new_block->prev = NULL;
        new_block->is_free = IS_FREE;
        new_block->block_size = mem_to_request - sizeof(Header);
    }

    //print_mem_list(in_node);

    Header *current_node = in_node;

    while (current_node != NULL)
    {
        if (current_node->is_free == IS_FREE && current_node->block_size >= space_amount)
        {
            if (current_node->block_size - space_amount > sizeof(Header))
            {
                //printf("%d", sizeof(Header));
                Header *new_block = (Header*) ((char*) (current_node) + sizeof(Header) + space_amount);

                new_block->next = current_node->next;
                new_block->prev = current_node;
                new_block->block_size = current_node->block_size - space_amount - sizeof(Header);
                new_block->is_free = IS_FREE;

                current_node->next = new_block;
                current_node->block_size = space_amount;
            }

            current_node->is_free = NOT_FREE;
            print_mem_list(in_node);
            in_node = in_node;
            return (char*)current_node + sizeof(Header);
        }

        current_node = current_node->next;
    }

    //printf("Second call.\n");


    fprintf(stderr, "No free memory.");

    Header *new_block = request_mem(mem_to_request);

    if (new_block == NULL)
        return NULL;



    new_block->next = NULL;
    new_block->prev = NULL;
    new_block->is_free = IS_FREE;
    new_block->block_size = mem_to_request - sizeof(Header);

    return NULL;
}

void my_free(void *ptr)
{
    Header *block = (Header*) ((char*)ptr - sizeof(Header));
    printf("\033[0mFREE: %d\033[0m\n", block->block_size);
    block->is_free = IS_FREE;

    //merge
    if ((block->next != NULL && block->next->is_free == IS_FREE) &&
        (block->prev != NULL && block->prev->is_free == IS_FREE))
    {
        block->prev->block_size += block->block_size +
                                   block->next->block_size +
                                   sizeof(Header) + sizeof(Header);

        block->prev->next = block->next->next;

        if (block->next->next != NULL)
            block->next->next->prev = block->prev;
    }
    else
    {
        if (block->next != NULL && block->next->is_free == IS_FREE)
        {
            block->block_size += block->next->block_size +
                                       sizeof(Header);

            block->next = block->next->next;

            if (block->next->next != NULL)
                block->next->next->prev = block;
        }

        if (block->prev != NULL && block->prev->is_free == IS_FREE)
        {
            block->prev->block_size += block->block_size +
                                       sizeof(Header);

            block->prev->next = block->next;

            if (block->next != NULL)
                block->next->prev = block->prev;
        }
    }

    print_mem_list(in_node);
}
