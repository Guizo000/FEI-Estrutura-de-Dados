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
	// Implementar
}

// Cria uma nova fila vazia
Queue *cria_queue(){
	// Implementar
}

// Operação ENQUEUE: insere elemento no final da fila (FIFO)
void enqueue(Queue *queue, int valor){
	// Implementar
}

// Operação DEQUEUE: remove elemento do início da fila (FIFO)
int dequeue(Queue *queue){
	// Implementar
}

// Exibe todos os elementos da fila (do início ao fim)
void show(Queue *queue){
	// Implementar
}

int main(void) {
	// Implementar
	
	return 0;
}