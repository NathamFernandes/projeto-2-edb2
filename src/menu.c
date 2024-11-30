#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "flight.h"

/**
 * @brief Loop do programa.
 *
 * @param flights O ponteiro para o vetor de voos.
 * @param flights_amount O tamanho do vetor.
 */
void main_loop(Heap *heap)
{
    int option;

    while (1)
    {
        // Pega a opção do usuário.
        option = render_first_menu();

        if (option < 1 || option > 6)
        {
            printf("\nOpcao invalida!\n");
            continue;
        }

        // Handlers.
        switch (option)
        {
        case 1:
            handle_flight_insert(heap);
            break;
        case 2:
            handle_flight_excluir(heap);
            break;
        case 3:
            handle_flight_edit(heap);
            break;
        case 4:
            handle_flights_show(heap);
            break;
        case 5:
            handle_next_flight(heap);
            break;
        case 6:
            deallocate(&heap);
            return;
        }
    }
}

/**
 * @brief Handler da opção do usuário.
 *
 * @return A opção.
 */
int render_first_menu()
{
    int option;

    printf("\n1 - Inserir um novo voo\n2 - Remover voo de maior prioridade\n3 - Alterar informacoes de um voo\n4 - Exibir todos os voos\n5 - Consultar proximo voo\n6 - Fechar controle de trafego aereo\n\nOpcao: ");

    scanf("%d", &option);

    return option;
}
