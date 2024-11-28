#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include "flight.h"

Flight *load_flights(char *file_path, Flight *flights, int *flights_amount)
{
    // Abre o arquivo no modo leitura.
    FILE *input_file = fopen(file_path, "r");

    // Verifica se o arquivo foi aberto corretamente.
    if (!input_file)
    {
        // Exibe uma mensagem de erro caso o arquivo não possa ser lido.
        fprintf(stderr, "Unable to read file \"%s\": %s.\n", file_path, strerror(errno));
        return NULL; // Retorna NULL em caso de erro ao abrir o arquivo.
    }

    char linha[512]; // Buffer para ler cada linha do arquivo.
    Flight flight;   // Variável para armazenar os dados do livro.

    // Lê cada linha do arquivo até o final.
    while (fgets(linha, sizeof(linha), input_file))
    {
        int success = sscanf(linha, "%99[^,],%u,%u,%hu,%hu",
                             flight.id, &flight.fuel, &flight.time, &flight.operation, &flight.emergency);

        flight.priority = calculate_priority(flight);

        // Se a linha foi lida com sucesso (7 campos), insere o livro na árvore.
        if (success == 5)
            flights = insert(flights, flight, flights_amount);
    }

    // Fecha o arquivo após terminar a leitura.
    fclose(input_file);

    // Retorna a árvore binária com os livros carregados.
    return flights;
}

unsigned calculate_priority(Flight flight)
{
    return (1000 - flight.fuel) + (1440 - flight.time) + 500 * (flight.operation) + 500 * (flight.emergency);
}

Flight *insert(Flight *flights, Flight flight, int *flights_amount)
{
    if (flights == NULL)
        flights = malloc(sizeof(Flight));
    else
        flights = realloc(flights, sizeof(Flight) * (*flights_amount + 1));

    flights[*flights_amount] = flight;
    *flights_amount = *flights_amount + 1;

    return flights;
}

// Flight *create_flight(Flight *flights)
// {
// }

// Flight *delete_flight(Flight *flights)
// {
// }

// void deallocate(Flight *flights)
// {
//     // // Caso base: se o nó atual for NULL, não há nada a fazer
//     // if (root == NULL)
//     //     return;

//     // // Desaloca recursivamente o nó à esquerda da árvore
//     // deallocate(root->left);
//     // free(root->left);
//     // root->left = NULL;

//     // // Desaloca recursivamente o nó à direita da árvore
//     // deallocate(root->right);
//     // free(root->right);
//     // root->right = NULL;
// }
