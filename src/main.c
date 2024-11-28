#include <stdlib.h>
#include <stdio.h>

#include "flight.h"
#include "menu.h"

int main(int argc, char *argv[])
{
    Flight *flights = NULL;
    int flights_amount = 0;

    flights = load_flights(argv[1], flights, &flights_amount);

    if (flights == NULL)
        return EXIT_FAILURE;

    main_loop(flights, &flights_amount);

    // deallocate(library);
    // library = NULL;

    // return EXIT_SUCCESS;
}