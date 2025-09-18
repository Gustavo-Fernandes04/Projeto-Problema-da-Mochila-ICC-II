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