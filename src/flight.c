#include <ctype.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#include "flight.h"

/**
 * @brief Inicializa uma nova heap.
 *
 * Aloca memória para uma heap e inicializa o tamanho como zero.
 *
 * @return Heap* Ponteiro para a heap inicializada ou NULL se a alocação falhar.
 */
Heap *initialize()
{
    // Aloca memória para a heap
    Heap *heap = (Heap *)malloc(sizeof(Heap));

    // Verifica se a alocação foi bem-sucedida
    if (heap != NULL)
    {
        // Inicializa o tamanho da heap como zero
        heap->size = 0;
        return heap;
    }

    // Se a alocação falhar, retorna NULL
    return NULL;
}

/**
 * @brief Carrega os voos de um arquivo e insere na heap.
 *
 * Abre um arquivo especificado pelo caminho e lê os dados dos voos.
 * Para cada voo lido, calcula a prioridade e o insere na heap.
 *
 * @param file_path Caminho do arquivo contendo os dados dos voos.
 * @param heap Ponteiro para a heap onde os voos serão armazenados.
 */
bool load_flights(char *file_path, Heap *heap)
{
    // Tenta abrir o arquivo para leitura
    FILE *input_file = fopen(file_path, "r");

    // Se o arquivo não puder ser aberto, exibe uma mensagem de erro
    if (!input_file)
    {
        fprintf(stderr, "Unable to read file \"%s\": %s.\n", file_path, strerror(errno));
        return false; // Retorna caso haja erro ao abrir o arquivo
    }

    // Buffer para armazenar uma linha lida do arquivo
    char linha[512];
    Flight flight; // Variável para armazenar os dados do voo
    ushort operation;

    // Lê o arquivo linha por linha
    while (fgets(linha, sizeof(linha), input_file))
    {
        // Lê os dados do voo da linha
        int success = sscanf(linha, "%99[^,],%hu,%hu,%hu,%hu",
                             flight.id, &flight.fuel, &flight.time, &operation, &flight.emergency);

        // Converte o código da operação para o tipo correto
        flight.operation = (Operation)operation;

        // Calcula a prioridade do voo
        flight.priority = calculate_priority(flight);

        // Se a linha foi lida com sucesso (5 campos), insere o voo na heap
        if (success == 5)
            insert(heap, flight);
    }

    // Fecha o arquivo após terminar a leitura
    fclose(input_file);

    return true;
}

/**
 * @brief Calcula a prioridade de um voo.
 *
 * A prioridade é calculada com base no combustível, tempo de voo, operação e emergência.
 *
 * @param flight O voo cujo a prioridade será calculada.
 * @return unsigned Valor da prioridade calculada.
 */
unsigned calculate_priority(Flight flight)
{
    return (1000 - flight.fuel) + (1440 - flight.time) + 500 * (flight.operation) + 500 * (flight.emergency);
}

/**
 * @brief Insere um voo na heap.
 *
 * Insere o voo na heap de forma que a propriedade de Max-Heap seja mantida.
 * Caso a heap esteja cheia, a inserção não é realizada.
 *
 * @param heap Ponteiro para a heap.
 * @param flight O voo a ser inserido.
 */
void insert(Heap *heap, Flight flight)
{
    // Verifica se a heap atingiu a capacidade máxima
    if (heap->size == MAX_CAPACITY)
    {
        fprintf(stderr, "A capacidade máxima para voos foi atingida.\n");
        return; // Se a heap estiver cheia, não insere mais elementos
    }

    // Adiciona o voo ao final da heap
    heap->data[heap->size] = flight;

    // Índice do último elemento inserido
    size_t idx = heap->size;

    // Incrementa o tamanho da heap
    heap->size++;

    // Ajusta a posição do voo para manter a propriedade de Max-Heap
    while (idx > 0 && heap->data[idx].priority > heap->data[(idx - 1) / 2].priority)
    {
        // Troca o voo com o pai, se necessário
        swap(&heap->data[idx], &heap->data[(idx - 1) / 2]);
        // Atualiza o índice do voo
        idx = (idx - 1) / 2;
    }
}

/**
 * @brief Troca dois elementos de voo.
 *
 * Troca os valores de dois voos na heap.
 *
 * @param a Ponteiro para o primeiro voo.
 * @param b Ponteiro para o segundo voo.
 */
void swap(Flight *a, Flight *b)
{
    // Armazena temporariamente o valor de um voo
    Flight temp = *a;

    // Atribui o valor do segundo voo ao primeiro
    *a = *b;

    // Atribui o valor armazenado do primeiro voo ao segundo
    *b = temp;
}

/**
 * @brief Restaura a propriedade da Max-Heap.
 *
 * A função heapify ajusta a heap para garantir que o maior elemento
 * esteja na raiz e que a propriedade de Max-Heap seja mantida.
 *
 * @param heap Ponteiro para a heap.
 * @param idx O índice a partir do qual o ajuste da heap será feito.
 */
void heapify(Heap *heap, size_t idx)
{
    // Índices dos filhos esquerdo e direito
    size_t largest, left, right;

    largest = idx;
    left    = 2 * idx + 1;
    right   = 2 * idx + 2;

    // Verifica se o filho esquerdo existe e é maior que o nó atual
    if (left < heap->size && heap->data[left].priority > heap->data[largest].priority)
        largest = left;

    // Verifica se o filho direito existe e é maior que o nó atual
    if (right < heap->size && heap->data[right].priority > heap->data[largest].priority)
        largest = right;

    // Se o maior não for o índice atual, troca os elementos e chama recursivamente heapify
    if (largest != idx)
    {
        // Troca o elemento atual com o maior dos filhos
        swap(&heap->data[idx], &heap->data[largest]);
        // Chama heapify recursivamente para o filho trocado
        heapify(heap, largest);
    }
}

/**
 * @brief Remove o voo com a maior prioridade (raiz da heap).
 *
 * A função remove a raiz (maior prioridade) da heap e retorna o voo removido.
 * Após a remoção, a heap é ajustada para manter a propriedade de Max-Heap.
 *
 * @param heap Ponteiro para a heap.
 */
void pop(Heap *heap)
{
    // Verifica se a heap está vazia
    if (heap->size == 0)
    {
        fprintf(stderr, "Impossível remover elemento, a árvore está vazia.\n");
        return; // Se a heap estiver vazia, retorna NULL
    }

    // Ponteiro para o voo que será removido (raiz da heap)
    Flight *flight = &heap->data[0];

    // Substitui a raiz pelo último elemento
    heap->data[0] = heap->data[heap->size - 1];
    // Decrementa o tamanho da heap
    heap->size--;

    // Restaura a propriedade de Max-Heap
    heapify(heap, 0);
}

/**
 * @brief Obtém o voo no topo da heap.
 * 
 * Esta função retorna o voo que está no topo da heap (índice 0), sem removê-lo. 
 * Se a heap estiver vazia, exibe uma mensagem de erro e retorna NULL.
 * 
 * @param heap Ponteiro para a estrutura da heap.
 * 
 * @return Ponteiro para o voo no topo da heap ou NULL se a heap estiver vazia.
 */
Flight* top(Heap* heap)
{
    if (heap->size == 0)
    {
        fprintf(stderr, "Nao ha elementos a serem consutados.\n");
        return NULL;
    }

    return &heap->data[0];
}

/**
 * @brief Remove um voo da heap.
 * 
 * Esta função remove o voo identificado pelo `flight_id` da heap. Se o `flight_id` 
 * for NULL, ela remove o voo do topo da heap. Caso a heap esteja vazia ou o 
 * voo com o `flight_id` não seja encontrado, a função retorna NULL.
 * Após remover o voo, a função restaura a propriedade de Max-Heap, garantindo
 * que a estrutura de heap continue válida.
 * 
 * @param heap Ponteiro para a estrutura da heap.
 * @param flight_id Identificador do voo a ser removido. Se NULL, remove o topo da heap.
 * 
 * @return Ponteiro para o voo removido ou NULL se não for possível remover o voo.
 */
Flight *excluir(Heap *heap, char flight_id[MAX_LEN])
{
    // Verifica se a heap está vazia
    if (heap->size == 0)
    {
        fprintf(stderr, "Impossível remover elemento, a árvore está vazia.\n");
        return NULL; // Se a heap estiver vazia, retorna NULL
    }

    int index = -1;

    if (flight_id == NULL)
        index = 0;
    else
    {
        for (int i = 0; i < heap->size; i++)
            if (strcmp(heap->data[i].id, flight_id) == 0)
                index = i;

        if (index == -1)
            return NULL;
    }

    // Ponteiro para o voo que será removido (raiz da heap)
    Flight *flight = &heap->data[index];

    if (flight_id == NULL)
        heap->data[0] = heap->data[heap->size - 1];
    else
        for (int i = index; i < heap->size; i++)
            heap->data[i] = heap->data[i + 1];

    // Substitui a raiz pelo último elemento
    // Decrementa o tamanho da heap
    heap->size--;

    // Restaura a propriedade de Max-Heap
    heapify(heap, index);

    // Retorna o voo removido
    return flight;
}

/**
 * @brief Constrói a heap a partir de um array de dados.
 *
 * Este processo é chamado de "construção de heap" e é necessário para garantir que a
 * propriedade de Max-Heap seja mantida após a construção de uma heap a partir de dados desordenados.
 *
 * @param heap Ponteiro para a heap a ser construída.
 */
void build_heap(Heap *heap)
{
    // Inicia a partir do último nó não-folha
    size_t start_idx = heap->size / 2 - 1;

    // Aplica heapify de baixo para cima para ajustar todos os nós
    for (int i = start_idx; i >= 0; i--)
        heapify(heap, i);
}

/**
 * @brief Libera a memória alocada para a heap.
 *
 * Libera a memória alocada para a heap e define o ponteiro da heap como NULL.
 *
 * @param heap Ponteiro para o ponteiro da heap a ser desalocada.
 */
void deallocate(Heap **heap)
{
    // Libera a memória alocada para a heap
    free(*heap);
    // Define o ponteiro para NULL após liberar a memória
    *heap = NULL;
}
