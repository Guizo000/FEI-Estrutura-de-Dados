#include <stdio.h>
#include <stdlib.h>

// Estrutura de uma célula da lista duplamente ligada
typedef struct Celula {
	int valor;					// Valor armazenado na célula
	struct Celula *proximo;		// Ponteiro para o próximo elemento
	struct Celula *anterior;	// Ponteiro para o elemento anterior
} Celula;

// Estrutura da fila com ponteiros para início e fim
typedef struct {
	Celula *head;	// Ponteiro para o primeiro elemento (início da fila)
	Celula *tail;	// Ponteiro para o último elemento (fim da fila)
	int qtde;		// Contador de elementos na fila
} Queue;

// Cria uma nova célula com o valor especificado
Celula *cria_celula(int valor){
	Celula *nova = malloc(sizeof(Celula));
    nova->valor = valor;
    nova->proximo = NULL;
    nova->anterior = NULL;
    return nova;
}

Queue *cria_queue(){
	Queue *nova = malloc(sizeof(Queue));
    nova->qtde = 0;
    nova->head = NULL;
    nova->tail = NULL;
    return nova;
}

// Operação ENQUEUE: insere elemento no final da fila (FIFO)
void enqueue(Queue *queue, int valor){
    printf("Inserido %d: ", valor);
	Celula *nova = cria_celula(valor);
    nova->anterior = queue->tail;
    if(queue->tail == NULL){
        queue->head = nova;
        queue->tail = nova;
        queue->qtde++;
        return;
    } 
    queue->tail->proximo = nova;
    queue->tail = nova;
    queue->qtde++;
    return;
}

// Operação DEQUEUE: remove elemento do início da fila (FIFO)
int dequeue(Queue *queue){
    if(queue->qtde == 0){
        return -1;
    }
    int valor = queue->head->valor;
	printf("Valor removido: %d, ", valor);

    Celula* temp = queue->head;

    queue->head = queue->head->proximo;
    if (queue->head != NULL)
        queue->head->anterior = NULL;
    else
        queue->tail = NULL; // Se esvaziou a fila

    free(temp); // Libera a célula removida
    queue->qtde--;

    return valor;
}

// Exibe todos os elementos da fila (do início ao fim)
void show(Queue *queue){
    Celula *celula = queue->head;
	for(int i = 0; celula != NULL; i++){
        printf("%d ", celula->valor);
        celula = celula->proximo;
    }
    printf("\n");
}

int main(void) {
	// Implementar
	Queue *queue = cria_queue();
    int valor[] = {10, 2, 0, 4, 5, 5, 6, 2, 8, 1, 9};

    printf("=== INSERINDO ELEMENTOS === \n");
    for(int i = 0; i <= 10; i++){
        enqueue(queue, valor[i]);
        show(queue);
    }

    printf("\n=== REMOVENDO ELEMENTOS === \n");
    for(int i = 0; i <= 10; i++){
        dequeue(queue);
        printf("Fila restante: ");
        show(queue);
    }
    
	return 0;
}