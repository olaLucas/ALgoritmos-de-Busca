#include <stdio.h>
#include <stdlib.h>

#define tamanho 10

void inicializar(int array[]);
void exibir(int array[]);
int buscar(int array[], int chave, int inicio, int fim);
void swap(int * x, int * y);
void quick();
int sort();

void inicializar(int array[])
{
    for (int i = 0; i < tamanho; i++)
    {
        array[i] = rand() % 50;
    }
}

void exibir(int array[])
{
    printf("\n\n");
    printf("Array: [ ");
    for (int i = 0; i < tamanho; i++)
    {
        printf("%d ", array[i]);
    }
    printf("]");
    printf("\n");
}

int buscar(int array[], int chave, int inicio, int fim)
{   
    int meio = (fim + inicio) / 2;
    while (inicio <= fim)
    {
        meio = (fim + inicio) / 2;
        if (array[meio] == chave)
        {
            return meio;
        }
        else if (array[meio] < chave){
            inicio = meio + 1;
        }
        else
        {
            fim = meio - 1;
        }
    }

    return -1;    
}

int main(void)
{
    int fim = tamanho - 1;
    int inicio = 0;
    int chave = -1;
    int array[tamanho];

    inicializar(array);
    exibir(array);
    quick(array, inicio, tamanho - 1);
    exibir(array);

    printf("Qual valor gostaria de buscar? \n\n>>> ");
    scanf("%d", &chave);

    chave = buscar(array, chave, inicio, fim);

    if (chave != -1)
    {
        printf("Indice: %d | Valor: %d \n\n", chave, array[chave]);    
    }else{
        printf("\nValor não encontrado! \n\n");
    }
    
    return 0;
}

void quick(int array[], int inicio, int fim)
{
    if (inicio > fim)
    {
        return;
    }

    int pivo = sort(array, inicio, fim);
    quick(array, inicio, pivo - 1);
    quick(array, pivo + 1, fim);
}

int sort(int array[], int inicio, int fim)
{ 
    int pivo = fim;
    int barraAmarela = 0;

    barraAmarela = inicio;
    for (int barraRoxa = inicio; barraRoxa < fim; barraRoxa++)
    {
        if (array[barraRoxa] < array[pivo])
        {
            swap(&array[barraRoxa], &array[barraAmarela]);
            barraAmarela++;
        }
    }

    swap(&array[pivo], &array[barraAmarela]);
    return barraAmarela;
}

void swap(int * x, int * y)
{
    int swap = *x;
    *x = *y;
    *y = swap;
}