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
 * @brief Desenha o cabeçalho da tabela com os nomes das colunas.
 * 
 * Esta função exibe uma linha horizontal seguida de uma linha de cabeçalho
 * contendo os títulos das colunas: ID, Combustível, Tempo, Operação, Emergência,
 * Prioridade. Em seguida, é exibida uma outra linha horizontal para formatar
 * a tabela.
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
 * @brief Desenha uma linha de voo na tabela.
 * 
 * Esta função exibe uma linha de dados referente a um voo na tabela, com a
 * formatação correta de cada coluna. As informações mostradas incluem o ID do voo,
 * o combustível restante, o tempo de voo, a operação (decolagem ou pouso),
 * o estado de emergência e a prioridade do voo.
 * 
 * @param flight O voo a ser exibido.
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
 * @brief Manipula a inserção de um novo voo na fila de prioridade.
 * 
 * Esta função solicita ao usuário as informações do voo (ID, combustível, tempo,
 * operação e emergência) e cria um novo objeto de voo. O voo é inserido na estrutura
 * de dados `heap` após calcular sua prioridade.
 * 
 * @param heap A estrutura de dados heap onde o voo será inserido.
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

/**
 * @brief Manipula a exclusão de um voo da fila de prioridade.
 * 
 * Esta função remove o voo com maior prioridade da estrutura de dados heap.
 * 
 * @param heap A estrutura de dados heap da qual o voo será removido.
 */
void handle_flight_excluir(Heap *heap)
{
    pop(heap);
}

/**
 * @brief Exibe o próximo voo na fila de prioridade.
 * 
 * Esta função exibe o próximo voo que será processado, ou seja, o voo com a maior
 * prioridade na estrutura de dados heap. A função também exibe o cabeçalho da tabela
 * antes de exibir os dados do voo.
 * 
 * @param heap A estrutura de dados heap da qual o voo será mostrado.
 */
void handle_next_flight(Heap* heap)
{
    Flight *next = top(heap);

    draw_table_header();

    if (heap != NULL)
        draw_row(*next);
}

/**
 * @brief Manipula a edição de um voo existente na fila de prioridade.
 * 
 * Esta função solicita ao usuário o ID do voo a ser editado e, se o voo existir,
 * permite que o usuário altere seus atributos (combustível, tempo, operação, emergência).
 * Após as alterações, o voo é reinserido na estrutura de dados heap.
 * 
 * @param heap A estrutura de dados heap onde o voo será editado.
 */
void handle_flight_edit(Heap *heap)
{
    char aux_string[MAX_LEN];
    printf("ID do Voo para editar: ");
    scanf("%63s", aux_string);

    Flight *flight = excluir(heap, aux_string);

    if (flight == NULL)
    {
        printf("\nEdit invalida!\n");
        return;
    }

    strcpy((*flight).id, aux_string);

    char keys[5][64] = {
        {"Combustivel"},
        {"Tempo"},
        {"Decolagem (D) ou Pouso (P)?"},
        {"Emergencia? S/N"},
    };

    printf("%s: ", keys[0]);
    scanf("%hu", (ushort *)&(*flight).fuel);
    getchar();

    printf("%s: ", keys[1]);
    scanf("%hu", (ushort *)&(*flight).time);
    getchar();

ATTR3:

    printf("%s: ", keys[2]);
    scanf("%63s", aux_string);

    if (strcmp(aux_string, "D") == 0)
        (*flight).operation = TAKEOFF;
    else if (strcmp(aux_string, "P") == 0)
        (*flight).operation = LANDING;
    else
        goto ATTR3;

ATTR4:

    printf("%s: ", keys[3]);
    scanf("%63s", aux_string);

    if (strcmp(aux_string, "S") == 0)
        (*flight).emergency = 1;
    else if (strcmp(aux_string, "N") == 0)
        (*flight).emergency = 0;
    else
        goto ATTR4;

    (*flight).priority = calculate_priority(*flight);

    insert(heap, *flight);
}

/**
 * @brief Exibe todos os voos na fila de prioridade.
 * 
 * Esta função exibe todos os voos na estrutura de dados heap. Para cada voo,
 * é exibida uma linha da tabela com os dados do voo. O cabeçalho da tabela também
 * é exibido antes dos dados dos voos.
 * 
 * @param heap A estrutura de dados heap onde os voos são armazenados.
 */
void handle_flights_show(Heap *heap)
{
    draw_table_header();
    if (heap != NULL) {
        for (int i = 0; i < heap->size; i++)
            draw_row(heap->data[i]);
    }
}
