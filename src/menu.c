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

        // Tratamento.
        if (option == 0)
            return;

        if (option < 0 || option > 7)
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
            // handle_book_search(library);
            break;
        case 3:
            // library = handle_books_import(library);
            break;
        case 4:
            handle_flights_show(heap);
            break;
        case 5:
            deallocate(&heap);
            break;
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

    printf("\n0 - Encerrar programa\n1 - Inserir um novo voo\n2 - Remover um voo\n3 - Alterar informacoes de um voo\n4 - Exibir todos os voos\n5 - Carregar voos por CSV\n7 - Fechar controle de trafego aereo\n\nOpcao: ");

    scanf("%d", &option);

    return option;
}
