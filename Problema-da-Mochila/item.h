#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct item_ ITEM;

float get_valor(ITEM* item);
int get_peso(ITEM* item);
bool item_apagar(ITEM** item);
ITEM *item_criar(float peso, float valor);