#include <stdio.h>
#include <time.h>
#include "item.h"

typedef struct mochila_{
    int pesoMax;
    float valor;
    int peso;
    int nItensArmazenados;
    ITEM **itensArmazenados;
}MOCHILA;

//struct vai armazenar um item, sua razao peso/valor
typedef struct noguloso_ {
    ITEM* item;
    float razao;
}NOGULOSO;

MOCHILA *programacao_dinamica(ITEM **itens, int pesoMax, int nItens);
MOCHILA *guloso(ITEM **itens, int pesoMax, int n);
MOCHILA *brute_force(ITEM **itens, int pesoMax, int n, int indexItem);
void bruteforce_recursao(MOCHILA *mochilaAtual, MOCHILA *mochilaMelhor, int indexItem, ITEM **itens, int n);
void quicksort(NOGULOSO *noguloso, int inf, int sup);
float maior (float a, float b);

int main(){
    int nItens;
    int pesoMochila;

    printf("Digite o número de itens: ");
    scanf("%d", &nItens);
    printf("\n");

    ITEM **itens = (ITEM**)malloc(sizeof(ITEM*) * nItens);
    if (itens == NULL){
        printf("Falha ao alocar memória para o vetor de itens\n");
        return 1;
    }

    printf("Digite o peso máximo da mochila: ");
    scanf("%d", &pesoMochila);
    printf("\n");
    MOCHILA *mochila = NULL;

    printf("Digite os itens (peso valor):\n");
    for (int i = 0; i < nItens; i++){
        int pesoTemp;
        float valorTemp;
        scanf("%d %f", &pesoTemp, &valorTemp);
        ITEM *it = item_criar(pesoTemp, valorTemp, i + 1);
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
        {
            mochila = brute_force(itens, pesoMochila, nItens, 0);
            break;
        }
        case 2:
        {
            mochila = guloso(itens, pesoMochila, nItens);
            break;
        }
        case 3:
        {
            mochila = programacao_dinamica(itens, pesoMochila, nItens);
            break;
        }
    }
    printf("\nOs itens que devem ser armazenados na mochila são:\n");
    for (int i = 0; i < mochila->nItensArmazenados; i++)
    {
        printf("Item \"%d\", de peso %d e valor %.04f\n", get_id(mochila->itensArmazenados[i]), get_peso(mochila->itensArmazenados[i]), get_valor(mochila->itensArmazenados[i]));
    }

    // Precisa de uma função no TAD item para apagar o item
    for (int i = 0; i < nItens; i++) {
        item_apagar(&itens[i]); 
    }
    
    free(itens);
    free(mochila->itensArmazenados);
    free(mochila);
    mochila = NULL;
    return 0;
}

// Função auxiliar para calcular o maior entre 2 números
float maior(float a, float b){
    if (a > b){
        return a;
    }
    else{
        return b;
    }
}

//algoritmo para ordenar o vetor noguloso de modo decrescente com base nas razoes valor/peso
void quicksort(NOGULOSO *noguloso, int inf, int sup)
{
    NOGULOSO aux;
    int meio = (inf + sup) / 2;
    float pivo = noguloso[meio].razao;
    int i = inf;
    int j = sup;
    do{
        while(noguloso[i].razao < pivo)
        {
            i++;
        }
        while(noguloso[j].razao > pivo)
        {
            j--;
        }
        if (i <= j)
        {
            aux = noguloso[i];
            noguloso[i] = noguloso[j];
            noguloso[j] = aux;
            i++;
            j--;
        }
    }while (i < j);
    //chamadas recursivas
    if (inf < j) {
        quicksort(noguloso, inf, j);
    }
    if (i < sup) {
        quicksort(noguloso, i, sup);
    }
}

MOCHILA *brute_force(ITEM **itens, int pesoMax, int n, int indexItem) //no inicio, IndexItem vai ser o item inicial (vai valer 0)
{
    clock_t inicio, fim; //marca de tempo
    double tempoExec; //marca o tempo de execução
    inicio = clock();
    //cria mochila que armazenara a melhor mochila ate entao
    MOCHILA *mochilaMelhor = (MOCHILA *)malloc(sizeof(MOCHILA));
    mochilaMelhor->valor = 0;
    mochilaMelhor->peso = 0;
    mochilaMelhor->nItensArmazenados = 0;
    mochilaMelhor->pesoMax = pesoMax;
    mochilaMelhor->itensArmazenados = (ITEM**) malloc (sizeof(ITEM*) * n);
    //cria mochila que sera operada a cada passo
    MOCHILA *mochilaAtual = (MOCHILA *)malloc(sizeof(MOCHILA));
    mochilaAtual->pesoMax = pesoMax;
    mochilaAtual->valor = 0;
    mochilaAtual->peso = 0;
    mochilaAtual->nItensArmazenados = 0;
    mochilaAtual->itensArmazenados = (ITEM**) malloc (sizeof(ITEM*) * n);
    bruteforce_recursao(mochilaAtual, mochilaMelhor, indexItem, itens, n);
    //libera a mochila atual, deixando apenas a melhor mochila
    free(mochilaAtual->itensArmazenados);
    free(mochilaAtual);
    fim = clock();
    tempoExec = ((double)(fim - inicio)/CLOCKS_PER_SEC);
    printf("Tempo de execucao: %lf",tempoExec);
    return mochilaMelhor;
}

void bruteforce_recursao(MOCHILA *mochilaAtual, MOCHILA *mochilaMelhor, int indexItem, ITEM **itens, int n) //mochilaMelhor vai sendo enchida com o tempo
{
    if (indexItem == n) //caso base (acabou os itens a serem verificados)
    {
        if(mochilaAtual->valor > mochilaMelhor->valor) //se a mochila atual for a nova melhor, bota ela como melhor
        {
            mochilaMelhor->valor = mochilaAtual->valor;
            mochilaMelhor->peso = mochilaAtual->peso;
            mochilaMelhor->nItensArmazenados = mochilaAtual->nItensArmazenados;
            for (int i = 0; i < mochilaAtual->nItensArmazenados; i++)
            {
                mochilaMelhor->itensArmazenados[i] = mochilaAtual->itensArmazenados[i];
            }
        }
        return;
    }
    bruteforce_recursao(mochilaAtual, mochilaMelhor, indexItem + 1, itens, n); //recursao para o caso em que nao se escolhe o item
    if (mochilaAtual->peso + get_peso(itens[indexItem]) <= mochilaAtual->pesoMax) //se for possivel adicionar o item, chama a recursao com o item incluido
    {
        mochilaAtual->itensArmazenados[mochilaAtual->nItensArmazenados] = itens[indexItem];
        mochilaAtual->peso += get_peso(itens[indexItem]);
        mochilaAtual->valor += get_valor(itens[indexItem]);
        mochilaAtual->nItensArmazenados++;
        bruteforce_recursao(mochilaAtual, mochilaMelhor, indexItem + 1, itens, n);
        mochilaAtual->nItensArmazenados--; //desfazekmos a adicao para nao afetar os outros ramos da recursao
        mochilaAtual->peso -= get_peso(itens[indexItem]);
        mochilaAtual->valor -= get_valor(itens[indexItem]);
    }
}  

MOCHILA *guloso(ITEM **itens, int pesoMax, int n)
{
    clock_t inicio, fim; //marca de tempo
    double tempoExec; //marca o tempo de execução
    inicio = clock();
    MOCHILA* mochila = (MOCHILA*)malloc (sizeof(MOCHILA));
    mochila->pesoMax = pesoMax;
    mochila->valor = 0;
    mochila->peso = 0;
    mochila->nItensArmazenados = 0;
    mochila->itensArmazenados = (ITEM**)malloc(sizeof(ITEM*) * n); //aloca meoria temporariamente para operar nos itens armazenados
    if (mochila->itensArmazenados == NULL)
    {
        printf("Erro: Sem espaço para alocacao de memoria.\n");
        return mochila; // Retorna a mochila vazia em caso de falha
    }
    NOGULOSO noguloso[n];
    for (int i = 0; i < n; i++) //loop que cria o vetor de structs
    {
        //bota os itens dentro dos nos e no vetor
        noguloso[i].item = itens[i];
        noguloso[i].razao = get_valor(itens[i]) / get_peso(itens[i]);
    }
    /*ALGORITMO DE ORDENAÇÃO MOMENT*/
    int infInicial = 0;
    int supInicial = n - 1;
    quicksort(noguloso, infInicial, supInicial);
    for (int i = n - 1; i >= 0; i--)//percorre de tras pra frente pq o vetor foi ordenado em ordem crescente
    {
    /*nItensArmazenados é usado como indíce pois a quantidade de itens na mochila
    sempre sera igual ao index do item que estará sendo operado no momento*/
        if (mochila->pesoMax >= mochila->peso + get_peso(noguloso[i].item)) //verifica se o peso estoura o pesomax da mochila antes de adicionar o item
        {
            mochila->itensArmazenados[mochila->nItensArmazenados] = noguloso[i].item; //armazena o item na mochila
            mochila->valor+= get_valor(noguloso[i].item); //vai somando o valor total da mochila
            mochila->peso+= get_peso(noguloso[i].item); //vai somando o peso total da mochila
            mochila->nItensArmazenados += 1; //contador de itens dentro da mochila
        }   
    }
    fim = clock();
    tempoExec = ((double)(fim - inicio)/CLOCKS_PER_SEC);
    printf("Tempo de execucao: %lf",tempoExec);
    return mochila;
}

MOCHILA *programacao_dinamica(ITEM **itens, int pesoMax, int nItens){

    clock_t inicio, fim; //marca de tempo
    double tempoExec; //marca o tempo de execução
    inicio = clock();
    
    // Criação da tabela da programação dinâmica
    float **dp = (float **)malloc((nItens + 1) * sizeof(float *));
    if (dp == NULL){
        return NULL;
    }
    for (int i = 0; i <= nItens; i++){
        dp[i] = (float *)malloc((pesoMax + 1) * sizeof(float));
        if (dp[i] == NULL) {
            while(--i >= 0) free(dp[i]);
            free(dp);
            return NULL;
        }
    }

    // Preenchimento da tabela da dp
    for (int i = 0; i <= nItens; i++){
        for (int j = 0; j <= pesoMax; j++){
            // Sub-problema base (mochila com capacidade nula ou quantidade nula de itens)
            if (i == 0 || j == 0){
                dp[i][j] = 0;
            }
            else if(get_peso(itens[i-1]) <= j){
                 /*Se o item atual tem o peso menor ou igual ao da mochila do sub-problema, temos a opção de incluir o item ou não, tudo depende se o valor total ao incluir ele é maior ou menor do que a solução anterior (sem incluir) */ 
                float valorPegar = get_valor(itens[i-1]) + dp[i-1][j - get_peso(itens[i-1])];
                float valorNPegar = dp[i-1][j];
                dp[i][j] = maior(valorPegar, valorNPegar);
            }
            else{
                // Se o item atual não pode ser inserido, o melhor resultado é o anterior
                dp[i][j] = dp[i-1][j];
            }
        }
    }

    // Obtendo os itens da melhor solução e o peso dela
    float valorDaSolucao = dp[nItens][pesoMax];
    int pesoTotal = 0;
    int cap = pesoMax;

    // Contar quantos itens fazem parte da solução ótima.
    int nItensSolucao = 0;
    for (int i = nItens; i > 0 && cap > 0; i--){
        if (dp[i][cap] != dp[i-1][cap]){
            nItensSolucao++;
            cap -= get_peso(itens[i-1]);
        }
    }

    // Criando a mochila da melhor solução
    MOCHILA *melhorMochila = (MOCHILA*) malloc(sizeof(MOCHILA));
    if (melhorMochila == NULL){
        printf("Erro ao alocar memoria para a melhor mochila (DP)\n");
        for (int i = 0; i <= nItens; i++){
            free(dp[i]);
        }
        free(dp);
        return NULL;
    }

    // Criando o array de itens da solução
    melhorMochila->itensArmazenados = (ITEM**) malloc(nItensSolucao * sizeof(ITEM*)); 
    if (melhorMochila->itensArmazenados == NULL){
        printf("Erro ao alocar memória para o array de itens da melhor mochila (DP)\n");
        for (int i = 0; i <= nItens; i++){
            free(dp[i]);
        }
        free(dp);
        free(melhorMochila);
        return NULL;
    }

    // Preenchendo a melhor mochila
    melhorMochila->pesoMax = pesoMax;
    melhorMochila->valor = valorDaSolucao;

    // Encontrando os itens da melhor mochila e preenchendo o array interno
    cap = pesoMax;
    int k = 0; // Índice para o array 'itensArmazenados'
    pesoTotal = 0; // Inicializa o acumulador de peso

    for (int i = nItens; i > 0 && cap > 0; i--){
        // Se o valor na célula atual é diferente da célula de cima, significa que a inclusão do item foi feita e ele faz parte da melhor solução
        if (dp[i][cap] != dp[i-1][cap]){
            // Adição do item e seu peso
            melhorMochila->itensArmazenados[k] = itens[i-1];
            pesoTotal += get_peso(itens[i-1]);
            
            cap -= get_peso(itens[i-1]);
            k++;
        }
    }
    
    // Atribui o peso total e o número de itens armazenados na melhor mochila
    melhorMochila->peso = pesoTotal;
    melhorMochila->nItensArmazenados = nItensSolucao;

    // Liberar a memória da tabela DP
    for (int i = 0; i <= nItens; i++) {
        free(dp[i]);
    }
    free(dp);
    fim = clock();
    tempoExec = ((double)(fim - inicio)/CLOCKS_PER_SEC);
    printf("Tempo de execucao: %lf",tempoExec);
    return melhorMochila;
}