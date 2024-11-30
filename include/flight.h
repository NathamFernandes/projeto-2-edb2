#ifndef FLIGHT_H
#define FLIGHT_H

#include <stddef.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LEN 6
#define MAX_CAPACITY 50

//== Structs/Enums

typedef unsigned short ushort;
typedef enum
{
    TAKEOFF,
    LANDING
} Operation;

// Representação de um voo.
typedef struct
{
    char id[MAX_LEN]; //! Código único de um livro.
    ushort fuel;
    ushort time;
    Operation operation;
    ushort emergency;
    ushort priority;
} Flight;

typedef struct
{
    Flight data[MAX_CAPACITY];
    size_t size;
} Heap;

//== Aux functions

void swap(Flight *a, Flight *b);

Heap *initialize();
bool load_flights(char *file_path, Heap *heap);
void heapify(Heap *heap, size_t idx);
void build_heap(Heap *heap);
unsigned calculate_priority(Flight flight);
void insert(Heap *heap, Flight flight);
void pop(Heap *heap);
Flight* top(Heap* heap);
void deallocate(Heap **heap);
// static char *strlower(const char *str);
Flight *excluir(Heap *heap, char flight_id[MAX_LEN]);

#endif
