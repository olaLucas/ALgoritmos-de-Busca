#include <stdio.h>
#include <stdlib.h>

#define tamanho 10

typedef struct node
{
    int dado;
    int proxNodes;
    struct node * proximo;
} node;

typedef struct node * ptr_node;

void inicializar();
void exibir();
void menu();
void inserir();
void imprimeBusca();
void menuBuscar();
void excluir();
int getValor();
int definirChave();
ptr_node buscaArray();
ptr_node buscarLista();
ptr_node percorreLista();

void inicializar(node array[])
{
    int dado = 0;
    int chave = 0;

    for (int i = 0; i < tamanho; i++)
    {
        array[i].dado = 0;
        array[i].proxNodes = 0;
        array[i].proximo = NULL;
    }
}

ptr_node incicializarNode(ptr_node elemento)
{
    elemento = (ptr_node)malloc(sizeof(ptr_node));
    elemento->dado = 0;
    elemento->proximo = NULL;

    return elemento;
}

ptr_node percorreLista(ptr_node elemento)
{   
    elemento->proxNodes++;
    if (elemento->proximo == NULL)
    {
        elemento->proximo = incicializarNode(elemento);
        elemento = elemento->proximo;
        return elemento;
    }
    else
    {
        while (elemento->proximo != NULL)
        {
            elemento = elemento->proximo;
        }
    }
    
    elemento->proximo = incicializarNode(elemento);
    elemento = elemento->proximo;

    return elemento;
}

void exibir(node array[])
{

    printf("\n\n");
    for (int i = 0; i < tamanho; i++)
    {
        printf("[%d,(%d)", i, array[i].dado);
        if (array[i].proximo != NULL)
        {
            ptr_node navegador = &array[i];
            while (navegador->proximo != NULL)
            {
                printf(" : ");
                printf("(%d)", navegador->proximo->dado);
                navegador = navegador->proximo;
            }
        }

        printf("] ");
    }

    printf("\n");
}

int definirChave(int x)
{
    return (x * x) % 10;
}

void menu(node array[])
{
    int seletor = -1;
    while (seletor != 0)
    {
        //system("clear");
        printf("--------------| ELEMETOS |--------------\n");
        exibir(array);

        printf("\nSelecione uma opção: \n\n");
        printf("0. Sair \n");
        printf("1. Inserir dados.\n");
        printf("2. Buscar dados.\n");
        printf("3. Excluir dados.\n");

        printf("\n >>> ");
        scanf("%d", &seletor);

        switch (seletor)
        {
        case 0:
            return;
            break;

        case 1:
            inserir(array);
            break;

        case 2:
            menuBuscar(array);
            break;

        case 3:
            excluir(array);

        default:
            printf("Opção inválida! Tente novamente. \n\n");
            getchar();
            break;
        }
    }
}

int getValor()
{
    int num = -1;
    while (num != 0)
    {
        printf("\nInsira o valor: (0 = Sair)");
        printf("\n >>> ");
        scanf("%d", &num);

        if (num == 0)
        {
            return -1;
        }
        else
        {
            return num;
        }
    }
}

void inserir(node array[])
{
    int valor = getValor();
    if (valor == -1)
    {
        return;
    }

    int chave = definirChave(valor);

    if (array[chave].dado != 0)
    {
        ptr_node navegador = percorreLista(&array[chave]);
        navegador->dado = valor;
    }
    else
    {
        array[chave].dado = valor;
    }
}

void menuBuscar(node array[])
{
    int valor = getValor();
    if (valor == -1)
    {
        return;
    }
    else
    {
        int chave = definirChave(valor);
        ptr_node resultado = NULL;

        if (array[chave].dado == valor)
        {
            resultado = &array[chave];
        }
        else if (resultado == NULL && array[chave].proximo != NULL)
        {
            resultado = buscarLista(&array[chave], valor);
        }
        else
        {
            resultado = NULL;
        }
        
        imprimeBusca(resultado, chave);
    }
}

ptr_node buscarLista(ptr_node elemento, int valor)
{
    while (elemento->dado != valor)
    {
        if (elemento->proximo == NULL)
        {
            return NULL;
        }
        else
        {
            elemento = elemento->proximo;
        }
    }

    return elemento;
}

void imprimeBusca(ptr_node elemento, int indice)
{
    if (elemento == NULL)
    {
        printf("Elemento não encontrado! \n\n");
        getchar();
    }
    else
    {
        printf("Elemento encontrado: [%d, (%d)] \n\n", indice,elemento->dado);
        getchar();
    }
}

void excluir(node array[])
{
    int valor = getValor();
    if (valor == -1)
    {
        return;
    }
    
    int chave = definirChave(valor);

    if (array[chave].proximo != NULL)
    {
        int i = 0;
        int arrayLista[array[chave].proxNodes];
        ptr_node atual = NULL;
        ptr_node navegador = &array[chave];
        while (navegador->proximo != NULL)
        {
            atual = navegador;
            navegador = navegador->proximo;
            arrayLista[i] = navegador->dado;
            i++;
        }

        free(navegador);
        atual->proximo = NULL;

        atual = &array[chave];
        atual->proxNodes--;

        for (int j = 0; j < i; j++)
        {
            atual->dado = arrayLista[j];
            atual = atual->proximo;
        }
    }
    else if (array[chave].dado == valor)
    {
        array[chave].dado = 0;
    }
    else
    {
        printf("Valor não encontrado! \n\n");
        getchar();
        return;
    }
}

int main(void)
{
    int chave = 0;
    node array[tamanho];

    inicializar(array);
    menu(array);

    return 0;
}