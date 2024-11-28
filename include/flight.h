#ifndef FLIGHT_H
#define FLIGHT_H

#include <stddef.h>
#include <ctype.h>

#define MAX_LEN 50

//== Structs

// Representação de um voo.
typedef struct
{
    char id[MAX_LEN]; //! Código único de um livro.
    unsigned fuel;
    unsigned time;
    unsigned short operation;
    unsigned short emergency;
    unsigned priority;
} Flight;

//== Aux functions

Flight *load_flights(char *file_name, Flight *flights, int *flights_amount);
unsigned calculate_priority(Flight flight);
Flight *insert(Flight *flights, Flight flight, int *flights_amount);
void deallocate(Flight *flights, int *flights_amount);

#endif
