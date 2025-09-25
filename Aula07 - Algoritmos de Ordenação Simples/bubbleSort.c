#include <stdlib.h>
#include <stdio.h>


void bubbleSort(int* v, int tam){
    for(int i = 0; i < tam; i++)
    {
        for(int j = tam-1; j > i; j--)
        {
            if(v[j] < v[j-1])
            {
                int placeHolder = v[j];
                v[j] = v[j-1];
                v[j-1] = placeHolder;
            }
        }
    }
}

void printArray(int* v, int tam){
    for(int i = 0; i < tam; i++){
        printf("%d ", v[i]);
    }
    printf("\n");
}

int main(){
    int tam_v = 10;
    int v[tam_v];

    for(int i = 0; i < 10; i++)
    {
        int valor;
        scanf("%d", &valor);
        v[i] = valor;
    }

    printArray(v, tam_v); 
    bubbleSort(v, tam_v);
    printArray(v, tam_v);
}