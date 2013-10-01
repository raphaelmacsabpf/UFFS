/*---------------------------------------------------
-----------------------------------------------------
----Trabalho feito por Raphael Machado dos Santos----
----E-mail: raphaelmacsa@gmail.com-------------------
-----------------------------------------------------
---------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>

struct nodo {
    int info;
    struct nodo *next;
    struct nodo *previous;
}typedef m_Nodo; //Estrutura dos nodos da lista ligada.

typedef struct {
    m_Nodo *first;
    m_Nodo *last;
    int count;
}m_Lista; //Estrutura da lista ligada.

//Prototipos
m_Nodo *GetNodoByIndex(m_Lista *lista, int index);
void MenuLista(m_Lista *lista);
void ImprimeLista(m_Lista * lista);
void RemoveLista(m_Lista *lista,int id);
void LimpaLista(m_Lista *lista);
void InsereLista(m_Lista *lista, int novo);
void InsertionSort(m_Lista *lista);
void QuickSort(m_Lista *lista, int start, int end);
int RepartirLista(m_Lista *lista, int left, int right);
void Swap(m_Nodo *nodo1, m_Nodo *nodo2);
m_Nodo *GetNodoByIndex(m_Lista *lista, int index);
int GetNodoInfoByIndex(m_Lista *lista, int index);

int main()
{
    m_Lista lista;
    lista.count = 0;
    lista.first = NULL;
    lista.last = NULL;
    int i = 0;
    MenuLista(&lista);
    return 0;
}
void MenuLista(m_Lista *lista)
{
    int escolha;
    printf("Escolha uma opcao\n\n\
            1 - Inserir Elemento\n\
            2 - Excluir Elemento\n\
            3 - Limpar a Lista\n\
            4 - Listar o conteudo\n\
            5 - Insertion Sort\n\
            6 - Quicksort\n\n");
    scanf("%d",&escolha);
    if(escolha == 1)
    {
        int valor;
        printf("Digite um valor para inserir\n");
        scanf("%d",&valor);
        InsereLista(lista,valor);
    }
    else if(escolha == 2)
    {
        int valor;
        printf("Digite um valor para remover\n");
        scanf("%d",&valor);
        RemoveLista(lista,valor);
    }
    else if(escolha == 3)
    {
        LimpaLista(lista);
    }
    else if(escolha == 4)
    {
        ImprimeLista(lista);
    }
    else if(escolha == 5)
    {
        printf("----Insertion Sort----\n");
        InsertionSort(lista);
    }
    else if(escolha == 6)
    {
        printf("----Quick Sort----\n");
        QuickSort(lista,0, (lista->count)-1);
    }
    else if(escolha == 7)
    {
        BubbleSort(lista);
    }
    MenuLista(lista);
}
void ImprimeLista(m_Lista * lista)
{
    printf("---Imprimindo Lista---\n\n");
    m_Nodo * aux = lista->first;
    if(aux == NULL)
    {
        printf("Lista Vazia\n");
    }
    for(aux = lista->first; aux != NULL; aux = aux->next)
    {
        printf("Elemento = %d\n\n",aux->info);
    }
    printf("----------------------\n");
}
int ProcurarExistencia(m_Lista *lista, int id)
{
    if(lista->first == NULL)
    {
        return 0;
    }
    m_Nodo *aux;
    for(aux = lista->first; aux != NULL; aux = aux->next)
    {
        if(aux->info == id)
        {
            return 1;
        }
    }
}
void RemoveLista(m_Lista *lista,int id)
{
    if(ProcurarExistencia(lista,id) == 1)
    {
        m_Nodo *aux;
        for(aux = lista->first; aux != NULL; aux = aux->next)
        {
            if(aux->info == id)
                break;

        }
        if(lista->first == lista->last)
        {
            lista->first = NULL;
            lista->last = NULL;
            lista->count = 0;

        }
        else
            if(aux == lista->first)
            {
                lista->first = lista->first->next;
                lista->first->previous = NULL;
                lista->count --;
                free(aux);
            }
            else if(aux == lista->last)
            {
                lista->last = lista->last->previous;
                lista->last->next = NULL;
                lista->count --;
                free(aux);
            }
            else
            {
                aux->previous->next = aux->next;
                aux->next->previous = aux->previous;
                lista->count --;
                free(aux);
            }
    }
    else
    {
        printf("Informacao nao existente");
    }
}
void LimpaLista(m_Lista *lista)
{
    m_Nodo * aux = lista->first;
    m_Nodo * aux2;
    if(aux == NULL)
    {
        printf("Lista Vazia\n");
    }
    while(aux != NULL)
    {
            aux2 = aux;
            aux = aux->next;
            free(aux2);
    }
    lista->first = lista->last = NULL;
    lista->count = 0;
}
void InsereLista(m_Lista *lista, int novo)
{
    m_Nodo *nodo;
    nodo = (m_Nodo *) malloc(sizeof(m_Nodo));
    if(!nodo)
        printf("Falta de memoria\n");
    nodo->info = novo;
    if(lista->count == 0)
    {
        lista->first = nodo;
        lista->count = 1;
        lista->first->previous = NULL;
        lista->first->next = NULL;
        lista->last = nodo;
    }
    else
    {
        m_Nodo * aux;
        aux = lista->last;
        aux->next = nodo;
        aux->next->next = NULL;
        lista->last = aux->next;
        aux->next->previous = aux;
        lista->count++;
    }
}
void InsertionSort(m_Lista *lista)
{
    int i;
    m_Nodo *aux = lista->first;
    for(i = 0; aux != NULL; i++, aux = aux->next)
    {
        while((i != 0) &&(aux->info < aux->previous->info))
        {
            Swap(aux,aux->previous);
            i--;
            aux = aux->previous;
        }
    }
}
void SelectionSort(m_Lista *lista)
{
    m_Nodo *aux, *aux2, *min;
    for(aux = lista->first; aux != NULL; aux = aux->next)
    {
        min = aux;
        if(aux->next != NULL)
        {
            for(aux2 = aux->next; aux2 != NULL; aux2 = aux2->next)
            {
                if(aux2->info < min->info)
                {
                    min = aux2;
                }
            }
            if(min != aux)
                Swap(min, aux);
        }
    }
}
void BubbleSort(m_Lista *lista)
{
    m_Nodo *aux, *aux2;
    int temp;
    for(aux = lista->first; aux != NULL; aux = aux->next)
    {
        if(aux->next != NULL)
        {
            for(aux2 = aux->next; aux2 != NULL; aux2 = aux2->next)
            {
                if(aux2->info < aux->info)
                {
                    temp = aux2->info;
                    aux2->info = aux->info;
                    aux->info = temp;
                }
            }
        }
    }
}


















void newBubbleSort(m_Lista *lista)
{
    m_Nodo *aux, *aux2;
    for(aux = lista->first; aux != NULL; aux = aux->next)
    {
        if(aux->next != NULL)
        {
            for(aux2 = aux->next; aux2 != NULL; aux2 = aux2->next)
            {
                if(aux2->info < aux->info)
                {
                    Swap(aux,aux2);
                }
            }
        }

    }
}
void AnewSelectionSort(m_Lista *lista)
{

    m_Nodo *aux, *aux2, *min;
    for(aux = lista->first; aux != NULL; aux = aux->next)
    {
        min = aux;
        if(aux->next != NULL)
        {
            for(aux2 = aux->next; aux2 != NULL; aux2 = aux2->next)
            {
                if(aux2->info < min->info)
                {
                    printf("novo\n");
                    min = aux2;
                }
            }
            if(min != aux)
            {
                Swap(min,aux);
            }
        }
    }
}
void newSelectionSort(m_Lista *lista)
{
    m_Nodo *aux, *aux2, *min;
    for(aux = lista->first; aux != NULL; aux = aux->next)
    {
        min = aux;
        if(aux->next != NULL)
        {
            for(aux2 = aux->next; aux2 != NULL; aux2 = aux2->next)
            {
                if(aux2->info < min->info)
                {
                    min = aux2;
                }
            }
            if(min != aux)
            {
                Swap(min,aux);
            }
        }
    }
}








void QuickSort(m_Lista *lista, int start, int end)
{
    int r;
    if(start < end)
    {
        r = RepartirLista(lista, start, end);
		QuickSort(lista, start, r-1);
		QuickSort(lista, r+1, end);
    }
}
int RepartirLista(m_Lista *lista, int left, int right)
{
    int i,j;
    i = left;
    for(j = left + 1; j <= right; j++)
    {

        if(GetNodoInfoByIndex(lista,j) < GetNodoInfoByIndex(lista,left))
        {
            i++;
            Swap(GetNodoByIndex(lista,i), GetNodoByIndex(lista,j));
        }
    }
    Swap(GetNodoByIndex(lista,left),GetNodoByIndex(lista,i));
    return i;
}
void Swap(m_Nodo *nodo1, m_Nodo *nodo2)
{
    if(nodo1 != NULL && nodo2 != NULL)
    {
        int aux = nodo1->info;
        nodo1->info = nodo2->info;
        nodo2->info = aux;
    }
}
m_Nodo *GetNodoByIndex(m_Lista *lista, int index)
{
    m_Nodo *aux;
    int i;
    for(i = 0, aux = lista->first; aux != NULL; aux = aux->next, i++)
    {
        if(i == index)
            return aux;
    }
    return NULL;
}
int GetNodoInfoByIndex(m_Lista *lista, int index)
{
    m_Nodo *aux;
    int i;
    for(i = 0, aux = lista->first; aux != NULL; aux = aux->next, i++)
    {
        if(i == index)
            return aux->info;
    }
    return 0;
}
