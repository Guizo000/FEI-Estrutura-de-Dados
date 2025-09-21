#include <stdio.h>
#include <stdlib.h>

typedef struct Vertice {
    int valor;
    struct Vertice *esq;
    struct Vertice *dir;
    struct Vertice *pai;
} Vertice;

typedef struct Arvore {
    Vertice *raiz;
    int qtde;
} Arvore;

//Retorna maior entre a e b
int max(int a, int b) {
    return (a >= b) ? a : b;
}

//Retorna altura de um dado vértice
int altura(Vertice *no) {
    //Caso o nó seja null retorna -1, q vai ser compensado com o +1 no fim do return
    if (no == NULL) return -1;
    return max(altura(no->esq), altura(no->dir)) + 1;
}

//Retorna o fator de balanceamento de um dado nó
int fatorBalanceamento(Vertice *no) {
    return altura(no->dir) - altura(no->esq);
}

void rotacaoEsquerda(Arvore *arvore, Vertice *x) {
    printf("Rotacao Esquerda em %d \n", x->valor);
    Vertice *temp_pai = NULL;
    if(x->pai != NULL) temp_pai = x->pai;
    Vertice *temp_dir = x->dir;

    //Consertando conexões do vértice x (vértice desbalanceado)
    x->dir = x->dir->esq;
    x->pai = temp_dir;

    //Consertando conexões do vértice x->dir->esq (caso ele exista)
    if(x->dir != NULL) x->dir->pai = x;

    //Consertando conexões do vértice x->dir
    temp_dir->esq = x;
    temp_dir->pai = temp_pai;

    //Caso temp_pai (pai do x) seja nulo, x era raíz 
    if(temp_pai == NULL)
    {
        //Atualiza para nova raíz x->dir
        arvore->raiz = temp_dir;
    }
    else
    {
        //Caso x n seja raíz, conserta conexão do pai de x, com seu novo filho
        if(temp_pai->dir == x) temp_pai->dir = temp_dir;
        else temp_pai->esq = temp_dir;
    }

}

void rotacaoDireita(Arvore *arvore, Vertice *x) {
    printf("Rotacao Direita em %d \n", x->valor);
    Vertice *temp_pai = NULL;
    if(x->pai != NULL) temp_pai = x->pai;
    Vertice *temp_esq = x->esq;

    //Consertando conexões do vértice x (vértice desbalanceado)
    x->esq = x->esq->dir;
    x->pai = temp_esq;

    //Consertando conexões do vértice x->esq->dir (caso ele exista)
    if(x->esq != NULL) x->esq->pai = x;

    //Consertando conexões do vértice x->esq
    temp_esq->dir = x;
    temp_esq->pai = temp_pai;

    //Caso temp_pai (pai do x) seja nulo, x era raíz 
    if(temp_pai == NULL)
    {
        //Atualiza para nova raíz x->dir
        arvore->raiz = temp_esq;
    }
    else
    {
        //Caso x n seja raíz, conserta conexão do pai de x, com seu novo filho
        if(temp_pai->dir == x) temp_pai->dir = temp_esq;
        else temp_pai->esq = temp_esq;
    }

}

void balancear(Arvore *arvore, Vertice *x) {
    //Cacula o fator de balanceamento do nó e seus filhos
    int fator = fatorBalanceamento(x);
    int fator_esq = x->esq == NULL ? 0 : fatorBalanceamento(x->esq);
    int fator_dir = x->dir == NULL ? 0 : fatorBalanceamento(x->dir);
    //Verifica se já esta balanceado
    if(fator <= 1 && fator >= -1) return;
    //Caso 1 - "Linha reta para direita" (árvore desbalanceada pra direita)
    else if(fator >= 2 && fator_dir >= 0)
    {
        rotacaoEsquerda(arvore, x);
    }
    //Caso 2 - Árvore desbalanceada pra direita
    else if(fator >= 2 && fator_dir < 0)
    {
        //Rotação direita pra deixar na forma do caso 1
        rotacaoDireita(arvore, x->dir);
        //Rotação pra esquerd agr que esta na forma do caso 1
        rotacaoEsquerda(arvore, x);
    }
    //Caso 3 - Caso 1 Espelhado
    else if(fator <= -2 && fator_esq <= 0)
    {
        rotacaoDireita(arvore, x);
    }
    //Caso 4 - Caso 2 Espelhado
    else if(fator <= -2 && fator_esq > 0)
    {
        rotacaoEsquerda(arvore, x->esq);
        rotacaoDireita(arvore, x);
    }

}

int inserir(Arvore *arvore, int valor) {
    Vertice *novo = malloc(sizeof(Vertice));
    novo->valor = valor;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->pai = NULL;
    
    Vertice *pai = NULL;
    Vertice *atual = arvore->raiz;
    
    while (atual != NULL) {
        pai = atual;
        if (valor <= atual->valor) {
            atual = atual->esq;
        } else {
            atual = atual->dir;
        }
    }
    
    novo->pai = pai;
    if (pai != NULL) {
        if (valor <= pai->valor) {
            pai->esq = novo;
        } else {
            pai->dir = novo;
        }
    } else {
        arvore->raiz = novo;
    }
    arvore->qtde++;
    
    Vertice *temp = novo->pai;
    while (temp != NULL) {
        balancear(arvore, temp);
        temp = temp->pai;
    }
    return 1;
}

void imprimirArvore(Vertice *no, char *prefixo, int ultimo) {
    if (no == NULL) return;
    
    printf("%s", prefixo);
    printf(ultimo ? "└── " : "├── ");
    printf("%d\n", no->valor);
    
    char novoPrefixo[256];
    sprintf(novoPrefixo, "%s%s", prefixo, ultimo ? "    " : "│   ");
    
    int temEsq = (no->esq != NULL);
    int temDir = (no->dir != NULL);
    
    if (temDir && temEsq) {
        imprimirArvore(no->dir, novoPrefixo, 0);
        imprimirArvore(no->esq, novoPrefixo, 1);
    } else if (temDir) {
        imprimirArvore(no->dir, novoPrefixo, 1);
    } else if (temEsq) {
        imprimirArvore(no->esq, novoPrefixo, 1);
    }
}

void inOrdem(Vertice *raiz) {
    if (raiz != NULL) {
        inOrdem(raiz->esq);
        printf("%d ", raiz->valor);
        inOrdem(raiz->dir);
    }
}

void posOrdem(Vertice *raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esq);
        posOrdem(raiz->dir);
        printf("%d ", raiz->valor);
    }
}

void testeInsere(Arvore *arvore, int valor) {
    printf("\n--- INSERINDO %d ---\n", valor);
    inserir(arvore, valor);
    
    if (arvore->raiz == NULL) {
        printf("Arvore vazia\n");
    } else {
        imprimirArvore(arvore->raiz, "", 1);
    }
    
    printf("In-Ordem: ");
    inOrdem(arvore->raiz);
    printf("\nPós-Ordem: ");
    posOrdem(arvore->raiz);
    printf("\nTotal: %d nos\n", arvore->qtde);
}

int main(void) {
    Arvore *arvore = malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    arvore->qtde = 0;
    
    testeInsere(arvore, 21);
    testeInsere(arvore, 26);
    testeInsere(arvore, 30);
    testeInsere(arvore, 9);
    testeInsere(arvore, 4);
    testeInsere(arvore, 14);
    testeInsere(arvore, 28);
    testeInsere(arvore, 18);
    testeInsere(arvore, 15);
    testeInsere(arvore, 10);
    testeInsere(arvore, 2);
    testeInsere(arvore, 3);
    testeInsere(arvore, 7);
    
    printf("\n=== ARVORE FINAL ===\n");
    imprimirArvore(arvore->raiz, "", 1);
    
    return 0;
}