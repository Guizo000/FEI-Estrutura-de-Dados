#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Vertice{
	int valor;
	struct Vertice* esq;
	struct Vertice* dir;
	struct Vertice* pai;
} Vertice;

typedef struct Arvore{
	Vertice* raiz;
	int qtde;
} Arvore;


//A travessia em ordem funciona na ordem ERD (esquerda, raíz, direita)
void in_ordem(Vertice *raiz) {
    if(raiz == NULL) return;
	in_ordem(raiz->esq);
	printf("%d ", raiz->valor);
	in_ordem(raiz->dir);
}

//A travessia em pre_ordem funciona na ordem RED (raíz, esquerda, direita)
void pre_ordem(Vertice *raiz) {
    if(raiz == NULL) return;
	printf("%d ", raiz->valor);
	pre_ordem(raiz->esq);
	pre_ordem(raiz->dir);
}

//A travessia em pos_ordem funciona na ordem EDR (esquerda, direita, raíz)
void pos_ordem(Vertice *raiz) {
    if(raiz == NULL) return;
	pos_ordem(raiz->esq);
	pos_ordem(raiz->dir);
	printf("%d ", raiz->valor);
}

Vertice *cria_vertice(int valor){
	Vertice* novo = malloc(sizeof(Vertice));
	novo->dir = NULL;
	novo->esq = NULL;
	novo->pai = NULL;
	novo->valor = valor;
	
	return novo;
}

Arvore *cria_arvore(){
	Arvore* arvore = malloc(sizeof(Arvore));
	arvore->raiz = NULL;
	arvore->qtde = 0;

	return arvore;
}

void inserir(Arvore* arvore, int valor){
	//Caso a árvore esteja vazia, cria o nó como raíz
	if(arvore->qtde == 0){
		arvore->raiz = cria_vertice(valor);
		arvore->qtde++;
		return;
	}

	Vertice* atual = arvore->raiz;
	Vertice* pai = NULL;

	//Procura um espaço vazio adequado na árvore pro valor
	while(atual != NULL){
		if(valor < atual->valor){
			pai = atual;
			atual = atual->esq;
		}else if(valor > atual->valor){
			pai = atual;
			atual = atual->dir;
		}else{
			return;
		}
	}

	//Cria o nó e faz as conexões necessária pra integridade da árvore
	Vertice* vertice = cria_vertice(valor);
	vertice->pai = pai;
	if(valor < pai->valor) pai->esq = vertice;
	else pai->dir = vertice;

	arvore->qtde++;
}

int remover_vertice(Arvore* arvore, Vertice* vertice) {
	if(vertice == NULL) return 1;

	//Caso 1: Nó a ser removido é folha
	if(vertice->dir == NULL && vertice->esq == NULL)
	{
		//Verifica se é raíz
		if(vertice->pai != NULL){
			/*
			Verifica se o nó  a ser removido é filho esquerdo ou direito do seu pai
			para tornar NULL a referencia do pai ao nó que vai ser apagado
			*/
			if(vertice->pai->dir == vertice) vertice->pai->dir = NULL; //Caso seja filho direito
			else vertice->pai->esq = NULL; //Caso seja filho esquerdo
		} else arvore->raiz = NULL;	//Caso seja raíz, torna a raiz nula
	}
	//Caso 2: Nó tem apenas filho esquerdo
	else if(vertice->dir == NULL && vertice->esq != NULL)
	{
		//Verifica se é raíz
		if(vertice->pai != NULL){
			/*
			Verifica em qual lado o nó a ser removido estava em relação a seu pai para
		    conectar o filho do nó a ser removido do lado certo
			*/
			if(vertice->pai->dir == vertice) vertice->pai->dir = vertice->esq; //Nó era filho direito
			else vertice->pai->esq = vertice->esq; //Nó era filho esquerdo
		}else arvore->raiz = vertice->esq; //Caso seja raíz, torna o último nó restante em raíz

		//Torna o pai do filho esquerdo no pai do nó a ser removido
		vertice->esq->pai = vertice->pai;
	}
	//Caso 3: Nó tem apenas filho direito -> praticamente igual ao caso 2
	else if(vertice->dir != NULL && vertice->esq == NULL)
	{
		//Verifica se é raíz
		if(vertice->pai != NULL){
			if(vertice->pai->dir == vertice) vertice->pai->dir = vertice->dir; //Nó era filho direito
			else vertice->pai->esq = vertice->dir; //Nó era filho esquerdo
		}else arvore->raiz = vertice->dir; //Caso seja raíz, torna o último nó restante em raíz

		vertice->dir->pai = vertice->pai;
	}
	//Caso 4: Nó tem dois filhos
	else
	{
		/*
		Encontra o predecessor do nó a ser removido (maior da subárvore esquerda, o que seria
		o mais a direita da subárvore esquerda)
		*/
		Vertice* pred = vertice->esq;
		//Percorre a subárvore esquerda ate chegar no mais a direita (maior)
        while (pred->dir != NULL) pred = pred->dir;
        
		//Copia o valor do predecessor pro vértice que seria removido
		vertice->valor = pred->valor;

		//Remove o predecessor (que agora terá no máximo um filho a esquerda)
		remover_vertice(arvore, pred);
		/*
		Return para evitar que o arvore->qtde-- e o free(vertice) seja feito duas vezes (nesse caso 
		ambos vão ser executados apenas na recursão, e n na chamada original)
		*/
		return 0;
	}

	//Apaga o nó
	free(vertice);
	//Decrementa a qtd da árvore
	arvore->qtde--;
	return 0;
}

Vertice *buscar_valor(Arvore* arvore, int valor){
	Vertice* atual = arvore->raiz;
	while(atual != NULL){
		if(valor < atual->valor){
			atual = atual->esq;
		}else if(valor > atual->valor){
			atual = atual->dir;
		}else{
			return atual;
		}
	}
	return NULL;
}


int main(void) {
	int dados[] = {5, 3, 8, 2, 4, 7, 9, 1, 6, 10};
  	Arvore *arvore = cria_arvore();
  	
	for(int i = 0; i < 10; i++){
		inserir(arvore, dados[i]);
		printf("Inseriu %d mostra em ordem -> ", dados[i]);
		in_ordem(arvore->raiz);
		printf("\n");
		printf("Inseriu %d mostra em pré-ordem -> ", dados[i]);
		pre_ordem(arvore->raiz);
		printf("\n");
		printf("Inseriu %d mostra em pós-ordem -> ", dados[i]);
		pos_ordem(arvore->raiz);
		printf("\n");
	}

	for(int i = 0; i < 10; i++){
		Vertice *vertice = buscar_valor(arvore, dados[i]);
		if(vertice != NULL){
			remover_vertice(arvore, vertice);
		}
		printf("Removeu %d mostra em ordem -> ", dados[i]);
		in_ordem(arvore->raiz);
		printf("\n");
		printf("Removeu %d mostra em pré-ordem -> ", dados[i]);
		pre_ordem(arvore->raiz);
		printf("\n");
		printf("Removeu %d mostra em pós-ordem -> ", dados[i]);
		pos_ordem(arvore->raiz);
		printf("\n");
	}

	free(arvore);
		
    return 0;
}
