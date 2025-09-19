#include "item.h"

typedef struct item_
{
    float pesoItem;
    float valorItem;
}ITEM;

float get_valor(ITEM* item)
{
    return (item->valorItem);
}

float get_peso(ITEM* item)
{
    return (item->pesoItem);
}

bool item_apagar(ITEM **item)
{
    if (*item == NULL)
    {
        return false;
    }
    else
    {
        free (*item);
        *item = NULL;
        return true;
    }
    
}

ITEM *item_criar(float peso, float valor)
{
    ITEM *item = (ITEM *) malloc (sizeof(ITEM *));
    if (item == NULL)
    {
        return (NULL);
    }
    item->pesoItem = peso;
    item->valorItem = valor;
    return (item);
}