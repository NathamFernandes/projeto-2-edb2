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
    TAKEOFF, //! Decolagem.
    LANDING  //! Pouso.
} Operation;

// Representação de um voo.
typedef struct
{
    char id[MAX_LEN];       //! Código único de uma aeronave.
    ushort fuel;            //! Quantidade de gasolina de uma aeronave.
    ushort time;            //! Horario de chegada/partida de um voo.
    Operation operation;    //! Tipo de operação.
    ushort emergency;       //! Emergencia ou nao de um voo.
    ushort priority;        //! Prioridade de uma aeronave.
} Flight;

// Representação de uma Heap.
typedef struct
{
    Flight data[MAX_CAPACITY];  //! Vetor que armazena as aeronaves.
    size_t size;                //! Quantidade de aeronaves.
} Heap;

//== Aux functions.

// Troca duas aernaves de posição.
void swap(Flight *a, Flight *b);
// Constroi uma arvore heap a partir de um vetor.
void build_heap(Heap *heap);

//== Main functions.

// Inicializa a estrutura heap.
Heap *initialize();
// Carrega as aeronaves a partir de um arquivo.
bool load_flights(char *file_path, Heap *heap);
// Mantém a propriedade max-heap de uma arvore heap.
void heapify(Heap *heap, size_t idx);
// Calcula a prioridade de uma aeronave.
unsigned calculate_priority(Flight flight);
// Insere uma aeronave na arvore heap.
void insert(Heap *heap, Flight flight);
// Remove a aeronave de maior prioridade.
void pop(Heap *heap);
// Retorna a aernave de maior prioridade.
Flight* top(Heap* heap);
// Remove uma aernave especifica da heap.
Flight *excluir(Heap *heap, char flight_id[MAX_LEN]);
// Desaloca memoria da heap.
void deallocate(Heap **heap);

#endif
