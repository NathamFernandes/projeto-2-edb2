#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "handlers.h"
#include "flight.h"

#define HORIZONTAL_LINE_LENGTH 97
#define ID_COLUMN_LENGTH 15
#define FUEL_COLUMN_LENGTH 15
#define TIME_COLUMN_LENGTH 15
#define OPERATION_COLUMN_LENGHT 15
#define EMERGENCY_COLUMN_LENGTH 15
#define PRIORITY_COLUMN_LENGTH 15

/**
 * @brief Desenha uma linha horizontal de caracteres '-'.
 *
 * Esta função imprime uma linha de caracteres '-' de comprimento
 * definido pela constante HORIZONTAL_LINE_LENGTH, seguida por uma
 * quebra de linha. Usada para separar seções na saída da tabela.
 */
static void draw_horizontal_line()
{
    for (size_t i = 0; i < HORIZONTAL_LINE_LENGTH; i++)
        printf("-");
    printf("\n");
}

/**
 * @brief Desenha o cabeçalho da tabela.
 *
 * Esta função chama a função `draw_horizontal_line()` para desenhar uma
 * linha horizontal no topo da tabela e, em seguida, imprime o cabeçalho
 * com os títulos das colunas ("Id", "Title", "Author", "Genre", "Publisher",
 * "Year", "Pages"). Após a impressão do cabeçalho, outra linha horizontal
 * é desenhada no final.
 */
static void draw_table_header()
{
    draw_horizontal_line();

    printf("|");
    printf(" %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n",
           ID_COLUMN_LENGTH - 2, "Id",
           FUEL_COLUMN_LENGTH - 2, "Combustivel",
           TIME_COLUMN_LENGTH - 2, "Tempo",
           OPERATION_COLUMN_LENGHT - 2, "Operacao",
           EMERGENCY_COLUMN_LENGTH - 2, "Emergencia",
           PRIORITY_COLUMN_LENGTH - 2, "Prioridade");

    draw_horizontal_line();
}

/**
 * @brief Desenha uma linha da tabela com os dados de um livro.
 *
 * Esta função imprime uma linha da tabela com os dados de um livro,
 * incluindo o ID, título, autor, gênero, editora, ano de publicação
 * e número de páginas. Ela usa a largura definida para cada coluna
 * para garantir que a formatação da tabela esteja alinhada corretamente.
 * Após imprimir a linha, a função `draw_horizontal_line()` é chamada
 * para desenhar uma linha horizontal ao final.
 *
 * @param book O livro cujos dados serão exibidos na linha da tabela.
 */
static void draw_row(Flight flight)
{
    printf("|");
    printf(" %-*s | %-*u | %-*u | %-*s | %-*s | %-*u |\n",
           ID_COLUMN_LENGTH - 2, flight.id,
           FUEL_COLUMN_LENGTH - 2, flight.fuel,
           TIME_COLUMN_LENGTH - 2, flight.time,
           OPERATION_COLUMN_LENGHT - 2, flight.operation == TAKEOFF ? "Decolagem" : "Pouso",
           EMERGENCY_COLUMN_LENGTH - 2, flight.emergency ? "Sim" : "Nao",
           PRIORITY_COLUMN_LENGTH - 2, flight.priority);

    draw_horizontal_line();
}

/**
 * @brief Lida com a inserção de um novo livro na biblioteca.
 *
 * @param library O nó raiz da biblioteca.
 */
void handle_flight_insert(Heap *heap)
{
    Flight new_flight;
    char aux_string[MAX_LEN];

    char keys[5][64] = {
        {"ID"},
        {"Combustivel"},
        {"Tempo"},
        {"Decolagem (D) ou Pouso (P)?"},
        {"Emergencia? S/N"},
    };

    printf("%s: ", keys[0]);
    scanf("%63s", (char *)new_flight.id);

    printf("%s: ", keys[1]);
    scanf("%hu", (ushort *)&new_flight.fuel);
    getchar();

    printf("%s: ", keys[2]);
    scanf("%hu", (ushort *)&new_flight.time);
    getchar();

ATTR3:

    printf("%s: ", keys[3]);
    scanf("%63s", aux_string);

    if (strcmp(aux_string, "D") == 0)
        new_flight.operation = TAKEOFF;
    else if (strcmp(aux_string, "P") == 0)
        new_flight.operation = LANDING;
    else
        goto ATTR3;

ATTR4:

    printf("%s: ", keys[4]);
    scanf("%63s", aux_string);

    if (strcmp(aux_string, "S") == 0)
        new_flight.emergency = 1;
    else if (strcmp(aux_string, "N") == 0)
        new_flight.emergency = 0;
    else
        goto ATTR4;

    new_flight.priority = calculate_priority(new_flight);

    insert(heap, new_flight);
}

void handle_flight_excluir(Heap *heap)
{
    char aux_string[MAX_LEN];
    printf("ID do Voo para remover: ");
    scanf("%63s", aux_string);

    excluir(heap, aux_string);
}

void handle_flight_edit(Heap *heap)
{
    char aux_string[MAX_LEN];
    printf("ID do Voo para editar: ");
    scanf("%63s", aux_string);
}

Heap *handle_flights_import(Heap *heap)
{
}

/**
 * @brief Lida com a exibição dos livros da biblioteca.
 *
 * @param library O nó raiz da heap.
 */
void handle_flights_show(Heap *heap)
{
    draw_table_header();
    for (int i = 0; i < heap->size; i++)
        draw_row(heap->data[i]);
}