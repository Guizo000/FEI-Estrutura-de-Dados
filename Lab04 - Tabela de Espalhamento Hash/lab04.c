#include <stdio.h>
#include <stdlib.h>

#define tam_hash 11

typedef struct Celula{
    int valor;
    struct Celula* proximo;
}Celula;

typedef struct {
    Celula* inicio;
}Lista;

typedef struct {
    Lista* table[tam_hash];
}Hash;

Hash* start_hash(){
    /*
    Aloca espaço para o Hash a para a Lista em cada 
    posição do vetor Lista* table
    */
    Hash* hash = malloc(sizeof(Hash));
    printf("%d", sizeof(Celula));
    for(int i = 0; i < tam_hash; i++){
        hash->table[i] = malloc(sizeof(Lista));
        hash->table[i]->inicio = NULL;
    } 
    return hash;
}

void inserir_hash(Hash* hash, int valor){
    int pos = valor%tam_hash;
    //Verifica se ja existe uma celula na posição da lista a ser usada
    if(hash->table[pos]->inicio == NULL){
        //Cria primeira celula na posição da lista
        hash->table[pos]->inicio = malloc(sizeof(Celula));
        hash->table[pos]->inicio->valor = valor;
        hash->table[pos]->inicio->proximo = NULL;
    }else{
        //Percorre a lista encadeada ate achar a última posição para inserção
        Celula* celula = hash->table[pos]->inicio;
        while(celula->proximo != NULL){
            celula = celula->proximo;
        }
        celula->proximo = malloc(sizeof(Celula));
        celula->proximo->proximo = NULL;
        celula->proximo->valor = valor;
    } 
}

void remover_hash(Hash* hash, int valor){
    int pos = valor%tam_hash;
    Celula* atual = hash->table[pos]->inicio;
    Celula* anterior = NULL;

    /*
    Verifica se a celula atual n é nula (se o a atual for nulo significa que a lista foi percorrida 
    e o valor n foi encontrado ou que a lista esta vazia) e se o valor da celula é igual ao valor
    a ser removido (se for verdade, não há mais necessidade de percorrer a lista pois o valor foi encontrado)
    */

    while(atual != NULL && atual->valor != valor){
        anterior = atual;
        atual = atual->proximo;
    }

    //Valor não encontrado
    if(atual == NULL) return;

    if(anterior == NULL){ 
        //Anterior == null significa que o valor é o primeiro da lista
        hash->table[pos]->inicio = atual->proximo;
    } else {
        //Corrige a lista encadeada fazendo o anterior->proximo apontar para o proximo doq vai ser removido
        anterior->proximo = atual->proximo;
    }

    //Remove o valor
    free(atual);
}

void imprimir(Hash* hash){
    //Percorre o hash
    for(int i = 0; i < tam_hash; i++){
        //Verifica a lista na posição i esta vazia
        if(hash->table[i]->inicio != NULL){

            //imprime o primeiro valor da lista
            Celula* celula = hash->table[i]->inicio;
            printf("%d -> %d ", i, celula->valor);  

            //percorre o resto da lista
            while(celula->proximo != NULL){
                printf("%d ", celula->proximo->valor);
                celula = celula->proximo;
            }
            printf("\n");

        } 
    }
}

int main(void) {
    Hash* hash = start_hash();

    int valor;
    while(1){
        scanf("%d", &valor);
        if(valor == 0)
        break;
        inserir_hash(hash, valor);
    }
    imprimir(hash);

    while(1){
        scanf("%d", &valor);
        if(valor == 0)
        break;
        remover_hash(hash, valor);
    }
    imprimir(hash);  

    return 0;
}