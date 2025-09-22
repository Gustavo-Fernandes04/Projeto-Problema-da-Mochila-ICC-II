#include <stdio.h>
#include "item.h"

typedef struct{
    float pesoMax;
    float valor;
    float peso;
    ITEM *itensArmazenados;
}MOCHILA;

int main(){
    int n;
    int pesoMochila;

    printf("Digite o número de itens: ");
    scanf("%d", &n);
    printf("\n");

    ITEM **itens = (ITEM**)malloc(sizeof(ITEM*) * n);
    if (itens == NULL){
        printf("Falha ao alocar memória para o vetor de itens\n");
        return 1;
    }

    printf("Digite o peso máximo da mochila: ");
    scanf("%d", &pesoMochila);
    printf("\n");

    printf("Digite os itens (peso | valor):\n");
    for (int i = 0; i < n; i++){
        int pesoTemp;
        int valorTemp;
        scanf("%d %d", &pesoTemp, &valorTemp);
        ITEM *it = item_criar(pesoTemp, valorTemp);
        itens[i] = it;
    }

    int comando;
    printf("Selecione o Algoritimo:\n");
    printf("1. Força Bruta\n");
    printf("2. Algoritimo Guloso\n");
    printf("3. Programação Dinâmica\n");

    scanf("%d", &comando);
    switch(comando)
    {
        case 1: 
        // Função algoritimo força bruta
        break;
        case 2:
        //Função algoritimo guloso
        break;
        case 3:
        // Função programação dinâmica
        break;
    }

    // Precisa de uma função no TAD item para apagar o item
    for (int i = 0; i < n; i++) {
        item_apagar(&itens[i]); 
    }
    free(itens);

    return 0;
}

int guloso()
{
    
}
