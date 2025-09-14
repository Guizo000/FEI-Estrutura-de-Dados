#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define LEN 10 

typedef struct {
	int valores[LEN];
	int qtde;
} heap;

int filho_esq(int pai){
	return 2*pai + 1;
}

int filho_dir(int pai){
	return 2*pai + 2;
}

int pai(int filho){
	return (filho-1)/2;
}

int ultimo_pai(heap *h){
	return h->qtde/2 - 1;
}

//Peneira de cima para baixo
void peneirar(heap *h, int pai){
	int esq = filho_esq(pai);
    int dir = filho_dir(pai);
    //Assume que o maior é o pai, ate fazer as comparações
    int maior = pai;

   
    //Verifica se o maior é o pai ou o filho esquerdo
    if(esq < h->qtde && h->valores[esq] > h->valores[maior]) maior = esq;
    /*
    Verifica se o maior é o (pai ou filho esquerdo dependendo do if anterior) ou o filho direito
    */
    if(dir < h->qtde && h->valores[dir] > h->valores[maior]) maior = dir;
    
    /*
    Caso o pai seja o maior o heap está correto e não há necessidade de 
    correções, caso um dos filhos seja maior, é feita correção e nova 
    chamada de peneirar
    */
    if(pai != maior){
        //Inverte o lugar do pai com o filho maior
        int val_pai = h->valores[pai];
        h->valores[pai] = h->valores[maior];
        h->valores[maior] = val_pai;
        peneirar(h, maior);
    }
}

//Peneira de baixo para cima
void peneirar_para_cima(heap *h, int filho_idx){
    /*
    Verifica se o filho está na posição 0 (primeira posição, logo n precisa peneirar) ou abaixo (números negativos n são aceitos)
    */
	if(filho_idx <= 0) return;

    //Pega a posição do pai 
    int pai_idx = pai(filho_idx);

    /*
    Verifica se o valor do filho é maior que o do pai, 
    se sim prossegue para correção, se n retorna
    */
    if(h->valores[filho_idx] > h->valores[pai_idx]){
        //Inverte a posição do pai com o filho
        int val_pai_idx = h->valores[pai_idx];
        h->valores[pai_idx] = h->valores[filho_idx];
        h->valores[filho_idx] = val_pai_idx;
        //Chama peneirar_para_cima novamente, para verificar se há necessidade de mais correção
        peneirar_para_cima(h, pai_idx);
    }
}


void construir(heap *h){
    int u = ultimo_pai(h);
    for(int i = u; i >= 0; i--){
        peneirar(h, i);
    }
}

void inserir(heap *h, int valor){
    if(h->qtde < LEN){
        //Insere o valor na primeira posição disponivel do heap
        h->valores[h->qtde] = valor;
        //Chama peneirar_para_cima para corrigir posiçao se necessário
        peneirar_para_cima(h, h->qtde);
        //Incrementa a qtd de valores no heap
        h->qtde++;
    }
}

void remover(heap *h){
    //Verifica se o heap não está vazio
	if(h->qtde > 0){
        //Troca-se o elemento da raíz, índice 0, com o último elemento do heap
        int val = h->valores[0];
        h->valores[0] = h->valores[h->qtde-1];
        h->valores[h->qtde-1] = val;
        
        //Decrementa qtd
        h->qtde--;

        //Caso o elemento removido não foi o último chama peneirar
        if(h->qtde > 0) peneirar(h, 0);
    }
}


void mostrar(heap *h){
	for(int i = 0; i < h->qtde; i++){
        printf("%d ", h->valores[i]);
    }
    printf("\n");
}



int main(void) {
	heap *h = malloc(sizeof(heap));
	h->qtde = 0;
	
	
	// TESTE 1: Inserção e visualização
	printf("--- TESTE 1: Inserção de elementos ---\n");
	
	for(int i = 1; i <= 10; i++){
		inserir(h, i);
		printf("Inserido %d: ", i);
		mostrar(h);
	}
	
	
	// TESTE 2: Remoção sucessiva
	printf("\n--- TESTE 2: Remoção de elementos ---\n");
	printf("Removendo em ordem de prioridade:\n");
	
	while(h->qtde > 0) {
		int max = h->valores[0];
		printf("Removendo máximo %d: ", max);
		remover(h);
		mostrar(h);
	}
	

	free(h);	
	return 0;
}