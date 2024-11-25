#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "handlers.h"

#define HORIZONTAL_LINE_LENGTH 139
#define ID_COLUMN_LENGTH 22
#define TITLE_COLUMN_LENGTH 35
#define AUTHOR_COLUMN_LENGTH 28
#define GENRE_COLUMN_LENGHT 20
#define PUBLISHER_COLUMN_LENGTH 12
#define YEAR_COLUMN_LENGTH 5
#define PAGES_COLUMN_LENGTH 5

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
    printf(" %-*s | %-*s | %-*s | %-*s | %-*s | %-*s | %-*s |\n", 
       ID_COLUMN_LENGTH - 2,        "Id", 
       TITLE_COLUMN_LENGTH - 2,     "Title", 
       AUTHOR_COLUMN_LENGTH - 2,    "Author", 
       GENRE_COLUMN_LENGHT - 2,     "Genre", 
       PUBLISHER_COLUMN_LENGTH - 2, "Publisher", 
       YEAR_COLUMN_LENGTH - 2,      "Year", 
       PAGES_COLUMN_LENGTH - 2,     "Pages");

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
static void draw_row(Book book)
{
    printf("|");
    printf(" %-*zu | %-*s | %-*s | %-*s | %-*s | %-*u | %-*u |\n", 
       ID_COLUMN_LENGTH - 2,        book.id, 
       TITLE_COLUMN_LENGTH - 2,     book.title, 
       AUTHOR_COLUMN_LENGTH - 2,    book.author, 
       GENRE_COLUMN_LENGHT - 2,     book.genre, 
       PUBLISHER_COLUMN_LENGTH - 2, book.publisher, 
       YEAR_COLUMN_LENGTH - 2,      book.year, 
       PAGES_COLUMN_LENGTH,         book.pages);

    draw_horizontal_line();
}
/**
 * @brief Lida com a inserção de um novo livro na biblioteca.
 *
 * @param library O nó raiz da biblioteca.
 */
Node *handle_new_book(Node *library)
{
    Book new_book;
    char keys[6][64] = {
        {"Titulo"},
        {"Autor"},
        {"Genero"},
        {"Publicador"},
        {"Paginas"},
        {"Ano"},
    };

    void *attributes[6] = {
        new_book.title,
        new_book.author,
        new_book.genre,
        new_book.publisher,
        &new_book.pages,
        &new_book.year,
    };

    new_book.id = generate_id();

    for (int i = 0; i < 6; i++)
    {
        printf("%s: ", keys[i]);

        if (i < 4)
            scanf("%63s", (char *)attributes[i]);
        else
            scanf("%d", (int *)attributes[i]);
    }

    if (library == NULL)
    {
        Node *new_node = create_node(new_book);
        library = new_node;
        return library;
    }

    insert(&library, new_book);

    return library;
}

/**
 * @brief Lida com a procura de livros pelo gênero na biblioteca.
 *
 * @param library O nó raiz da biblioteca.
 */
void handle_book_search(Node *library)
{
    char genre[64];
    getchar();

    printf("Genero para pesquisa: ");
    scanf("%63[^\n]", genre);

    draw_table_header();
    search_by_genre(library, genre, draw_row);
}

/**
 * @brief Lida com a importação de novos livros para a biblioteca.
 *
 * @param library O nó raiz da biblioteca.
 */
Node *handle_books_import(Node *library)
{
    char path[128] = "seeders/";
    char extension[8] = ".csv";
    char file[64];
    getchar();

    printf("Nome do arquivo (apenas) para importacao: ");
    scanf("%63[^\n]", file);

    strcat(path, file);
    strcat(path, extension);

    printf("%s", path);

    library = load_books(path, library);

    return library;
}

/**
 * @brief Lida com a exibição dos livros da biblioteca.
 *
 * @param library O nó raiz da biblioteca.
 */
void handle_books_show(Node *library)
{
    draw_table_header();
    show_books(library, draw_row);
}
