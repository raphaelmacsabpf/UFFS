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

void main()
{
    m_Lista lista;
    lista.count = 0;
    lista.first = NULL;
    lista.last = NULL;
    MenuLista(&lista);
    return 1;
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
        InsertionSort(lista);
    }
    else if(escolha == 6)
    {
        QuickSort(lista);
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
void ImprimeListaAoContrario(m_Lista * lista)
{
    printf("---Imprimindo Lista Ao Contrario---\n\n");
    m_Nodo * aux = lista->last;
    if(aux == NULL)
    {
        printf("Lista Vazia\n");
    }
    for(aux = lista->last; aux != NULL; aux = aux->previous)
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
    printf("Insertion Sort\n");
}
void QuickSort(m_Lista *lista)
{
    printf("Quick Sort\n");
}
