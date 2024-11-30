#include <stdlib.h>
#include <stdio.h>

#include "flight.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("Usage: fly <file.csv>\n");
        return EXIT_FAILURE;
    }

    Heap *heap = initialize();

    if (heap == NULL)
        return EXIT_FAILURE;

    bool success = load_flights(argv[1], heap);

    if (success)
        main_loop(heap);
    else 
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
