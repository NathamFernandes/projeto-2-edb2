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
void main_loop(Flight *flights, int *flights_amount)
{
    int option;

    while (1)
    {
        // Pega a opção do usuário.
        option = render_first_menu();

        // Tratamento.
        if (option == 0)
            return;

        if (option < 0 || option > 5)
        {
            printf("\nOpcao invalida!\n");
            continue;
        }

        // Handlers.
        switch (option)
        {
        case 1:
            // library = handle_new_book(library);
            break;
        case 2:
            // handle_book_search(library);
            break;
        case 3:
            // library = handle_books_import(library);
            break;
        case 4:
            handle_flights_show(flights, *flights_amount);
            break;
        case 5:
            deallocate(flights, flights_amount);
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

    printf("\n0 - Encerrar programa\n1 - Inserir um novo voo (not working)\n2 - Buscar livro por prioridade (not working)\n3 - Carregar voos por CSV (not working)\n4 - Exibir voos\n5 - Excluir voos\n\nOpcao: ");

    scanf("%d", &option);

    return option;
}