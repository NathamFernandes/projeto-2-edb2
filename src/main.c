#include <stdlib.h>
#include <stdio.h>

#include "flight.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    Heap *heap = initialize();
    load_flights(argv[1], heap);

    if (heap == NULL)
        return EXIT_FAILURE;

    printf("Heap: \n");
    for (size_t i = 0; i < heap->size; i++)
    {
        printf("%hu ", heap->data[i].priority);
    }
    printf("\n");

    main_loop(heap);

    deallocate(&heap);

    return EXIT_SUCCESS;
}
