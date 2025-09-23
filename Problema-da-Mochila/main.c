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
    MOCHILA mochila; //criei a mochila
    mochila.pesoMax = pesoMochila;

    printf("Digite os itens (peso | valor):\n");
    for (int i = 0; i < n; i++){
        int pesoTemp;
        int valorTemp;
        scanf("%d %d", &pesoTemp, &valorTemp);
        ITEM *it = item_criar(pesoTemp, valorTemp);
        itens[i] = it; //itens[] é um vetor de ITEM* 
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
/*
No guloso eu vou pegar os itens armazenados no vetor
e criar um vetor paralelo com a razão valor/peso
vou loopar pelo vetor procurando o maior e vou adicionando
enquanto isso vou verificando se passa do peso maximo usando um acumulador do peso e comparando com o pesomax
*/
ITEM **guloso(ITEM **itens, MOCHILA mochila, int n) 
{
    float razoes[n];
    for (int i = 0; i < n; i++) //loop que cria o vetor paralelo de razoes
    {
        float valor = get_valor(itens[i]);
        float peso = get_peso(itens[i]);
        razoes[i] = valor / peso;
    }
    float pesoAcumulado; //vai somando o peso adicionado
    int mochilaCheia = 0; //booleano que indica se ainda é possivel encher a mochila ou nao
    do //loop que percorre o vetor procurando a maior razao
    {
        /* tenho que pensar em como remover do vetor os itens usados, acho que é mais facil fazer uma struct com item, razao e numero
        fazendo isso um vetor ordenado pelas razoes e ai ir pegando pela ordem*/
        
    } while (!mochilaCheia);
}