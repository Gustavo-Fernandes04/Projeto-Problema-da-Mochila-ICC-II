#include "item.h"

typedef struct item_
{
    float pesoItem;
    float valorItem;
    int id;
}ITEM;

float get_valor(ITEM* item)
{
    return (item->valorItem);
}

int get_id(ITEM* item)
{
    return (item->id);
}

int get_peso(ITEM* item)
{
    return (item->pesoItem);
}

bool item_apagar(ITEM** item)
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

ITEM *item_criar(float peso, float valor, int id)
{
    ITEM *item = (ITEM *) malloc (sizeof(ITEM));
    if (item == NULL)
    {
        return (NULL);
    }
    item->pesoItem = peso;
    item->valorItem = valor;
    item->id = id;
    return (item);
}
