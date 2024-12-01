#ifndef HANDLERS_H
#define HANDLERS_H

#include "flight.h"

void handle_flight_insert(Heap *heap);
void handle_flight_excluir(Heap *heap);
void handle_flight_edit(Heap *heap);
void handle_flights_show(Heap *heap);
void handle_flights_import(Heap *heap);
void handle_flights_show(Heap *heap);
void handle_next_flight(Heap *heap);

#endif
