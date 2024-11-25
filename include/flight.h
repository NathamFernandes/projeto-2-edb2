#ifndef FLIGHT_H
#define FLIGHT_H

#include <stddef.h>
#include <ctype.h>

#define MAX_LEN 50
#define TRUE 1

//== Aliases

// typedef size_t hash_t;

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

// Representaçãp de um nó da árvore.
typedef struct node
{
    Flight flight;      //! Dado guardado pelo nó da árvore.
    struct node *left;  //! Ponteiro para o filho esquerdo do nó.
    struct node *right; //! Ponteiro para o filho direito do nó.
} Node;

//== Aux functions

// Cria um novo nó na árvore.
Node *create_node(const Flight flight);

//== Main functions

// Inicializa uma árvore vazia.
Node *initialize();
// // Carrega os livros de um arquivo .csv.
// Node *load_books(const char *file_path, Node *root);
// // Insere um livro na árvore.
// void insert(Node **root, const Book book);
// // Busca por todos os livros de um determinado gênero.
// void search_by_genre(Node *root, const char *genre, void (*print)(const Book book));
// // Lista todos os livros da árvore.
// void show_books(Node *root, void (*print)(const Book));
// // Desaloca toda a árvore binária.
// void deallocate(Node *root);

#endif
