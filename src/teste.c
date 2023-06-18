#include <stdio.h>
#include <time.h>

// Deve-se adicionar a biblioteca stdlib para poder trabalhar com alocação dinâmica
#include <stdlib.h>

void preencher_vetores(int vet[], int tam);
void imprimir_vetores(int vet[], int tam);

int main()
{

    // O primeiro passo é criar uma variável capaz de armazenar um endereço de memória do tipo que se deseja fazer alocação dinâmica. Vamos criar duas para ilustrar o malloc e o calloc.
    int *vet1, *vet2;

    // Algumas outras variáveis que vamos utilizar
    int tam1 = 7, adicional = 0;
    srand(time(NULL) + 485);

    // Em seguida, fazer uma primeira alocação estática para ser possível armazenar os primeiros valores(poderá ser expandido posteriormente)
    // Há duas opções básicas, malloc e calloc. Malloc recebe somente a quantidade total de bytes, enquanto calloc recebe a quantidade do que se quer e o tamanho em bytes dele. Nesse caso, para que seja alocada a quantidade de bytes certa em malloc, usa-se o sizeof(tipo):
    vet1 = malloc(tam1 /*quantidade do que se quer armazenar*/ * /*vezes*/ sizeof(int) /*o seu tamanho*/);
    vet2 = calloc(tam1, sizeof(int));

    preencher_vetores(vet1, tam1);
    preencher_vetores(vet2, tam1);

    printf("vet 1: ");
    imprimir_vetores(vet1, tam1);

    printf("vet 2: ");
    imprimir_vetores(vet2, tam1);
    printf("\n");

    // Agora, vamos realocar segundo a nossa necessidade. Na realocação, vamos buscar na memória uma área que tenha o espaço desejado e copiar o que havia na antiga área na nova área. Realloc recebe como argumentos o ponteiro antigo e a nova quantidade em bytes e retorna o ponteiro da primeira posição da nova área.
    printf("Digite quanto a mais deseja alocar para o vet 1: ");
    scanf("%d", &adicional);
    tam1 += adicional;

    vet1 = realloc(vet1, tam1 * sizeof(int));
    preencher_vetores(vet1, tam1);
    printf("vet 1(apos realloc): ");
    imprimir_vetores(vet1, tam1);

    free(vet2);
    vet2 = NULL;

    return 0;
}

void preencher_vetores(int vet[], int tam)
{
    int i = 0;

    for (i = 0; i < tam; i++)
    {
        vet[i] = rand() % 10;
    }
}

void imprimir_vetores(int vet[], int tam)
{
    int i = 0;

    for (i = 0; i < tam; i++)
    {
        printf("%d ", vet[i]);
    }
    printf("\n");
}
#include <stdio.h>
#include <time.h>

// Deve-se adicionar a biblioteca stdlib para poder trabalhar com alocação dinâmica
#include <stdlib.h>

void preencher_vetores(int vet[], int tam);
void imprimir_vetores(int vet[], int tam);

int main()
{

    // O primeiro passo é criar uma variável capaz de armazenar um endereço de memória do tipo que se deseja fazer alocação dinâmica. Vamos criar duas para ilustrar o malloc e o calloc.
    int *vet1, *vet2;

    // Algumas outras variáveis que vamos utilizar
    int tam1 = 7, adicional = 0;
    srand(time(NULL) + 485);

    // Em seguida, fazer uma primeira alocação estática para ser possível armazenar os primeiros valores(poderá ser expandido posteriormente)
    // Há duas opções básicas, malloc e calloc. Malloc recebe somente a quantidade total de bytes, enquanto calloc recebe a quantidade do que se quer e o tamanho em bytes dele. Nesse caso, para que seja alocada a quantidade de bytes certa em malloc, usa-se o sizeof(tipo):
    vet1 = malloc(tam1 /*quantidade do que se quer armazenar*/ * /*vezes*/ sizeof(int) /*o seu tamanho*/);
    vet2 = calloc(tam1, sizeof(int));

    preencher_vetores(vet1, tam1);
    preencher_vetores(vet2, tam1);

    printf("vet 1: ");
    imprimir_vetores(vet1, tam1);

    printf("vet 2: ");
    imprimir_vetores(vet2, tam1);
    printf("\n");

    // Agora, vamos realocar segundo a nossa necessidade. Na realocação, vamos buscar na memória uma área que tenha o espaço desejado e copiar o que havia na antiga área na nova área. Realloc recebe como argumentos o ponteiro antigo e a nova quantidade em bytes e retorna o ponteiro da primeira posição da nova área.
    printf("Digite quanto a mais deseja alocar para o vet 1: ");
    scanf("%d", &adicional);
    tam1 += adicional;

    vet1 = realloc(vet1, tam1 * sizeof(int));
    preencher_vetores(vet1, tam1);
    printf("vet 1(apos realloc): ");
    imprimir_vetores(vet1, tam1);

    free(vet2);
    vet2 = NULL;

    return 0;
}

void preencher_vetores(int vet[], int tam)
{
    int i = 0;

    for (i = 0; i < tam; i++)
    {
        vet[i] = rand() % 10;
    }
}

void imprimir_vetores(int vet[], int tam)
{
    int i = 0;

    for (i = 0; i < tam; i++)
    {
        printf("%d ", vet[i]);
    }
    printf("\n");
}