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
    /*
    Anterior da nova célula passa a apontar para
    o penúltimo, queue->tail, que apontava para o último antes dessa inserção
    */
    nova->anterior = queue->tail;

    /*
    Verifica se existe algum elemento na queue
    e caso n exista, faz os ponteiros head e tail da queue
    apontarem pra nova célula (primeira e única da queue)
    */
    if(queue->tail == NULL){
        queue->head = nova;
        queue->tail = nova;
        queue->qtde++;
        return;
    }

    /*
    Caso ja exista algum elemento na queue faz o queue->tail->proximo(faz com que o antigo último e atual penúltimo passe a apontar para a nova celula, atual ultima) e a queue->tail apontar para a célula nova  
    */
    queue->tail->proximo = nova;
    queue->tail = nova;
    queue->qtde++;
    return;
}

// Operação DEQUEUE: remove elemento do início da fila (FIFO)
int dequeue(Queue *queue){
    // Verifica se a queue está vazia
    if(queue->qtde == 0){
        return -1;
    }

    // Printa o valor a ser removido
    int valor = queue->head->valor;
	printf("Valor removido: %d, ", valor);

    /*
    Cria um ponteiro para guardar o endereço da celula a ser removida, ja que precisaremos fazer queue->head apontar para queue->head->proximo
    antes da remoção
    */
    Celula* temp = queue->head;

    //Faz a queue->head apontar para o novo primeiro
    queue->head = queue->head->proximo;

    /*
    Verifica se o queue->head->proximo é NULL, se for, significa que so existem um elemento na queue
    */
    if (queue->head != NULL)
        //queue->head->anterior passa a ser NULL pois agora é o primeiro
        queue->head->anterior = NULL;
    else
        //queue->tail passa a ser NULL, pois o último elemento foi removido
        queue->tail = NULL; // Esvaziou a queue

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