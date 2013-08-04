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
m_Nodo *QuickSort(m_Lista *lista, m_Nodo *left, m_Nodo *right);
m_Nodo *partition(m_Lista *lista, m_Nodo *left, m_Nodo *right, m_Nodo *pivot);
m_Nodo *GetNodoByIndex(m_Lista *lista, int index);
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
        lista = QuickSort(lista,lista->first, lista->last);
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
    printf("----Insertion Sort----\n");
    int i,j;
    m_Nodo *aux;
    m_Nodo *anterior = aux;
    for(j = 0; j < lista->count; j++)
    {
        for(i = 0, aux = lista->first; i < lista->count; i++, anterior = aux,aux = aux->next)
        {
            while((i != 0) && (aux->info < anterior->info))
            {
                SwapNodos(lista,anterior,aux);
                aux = anterior;
            }
        }
    }
}
m_Nodo *QuickSort(m_Lista *lista, m_Nodo *left, m_Nodo *right)
{
    printf("DEBUG0\n");
    if(GetIndex(lista, left) < GetIndex(lista,right))
    {
        m_Nodo *pivot = GetNodoByIndex(lista, lista->count / 2);
        printf("%d   %d",GetIndex(lista, left),GetIndex(lista, right));
        m_Nodo *q = partition(lista, left, right,pivot);
        printf("DEBUG2\n");
		QuickSort(lista, left, q->previous);
		printf("DEBUG3\n");
		QuickSort(lista, q->next, right);
		printf("DEBUG4\n");
    }
    printf("DEBUG5\n");
    return lista;
}
m_Nodo *partition(m_Lista *lista, m_Nodo *left, m_Nodo *right, m_Nodo *pivot)
{
    m_Nodo *pos, *i;
    SwapNodos(lista,pivot, right);
    pos = left;
    for(i = left; GetIndex(lista, i) < GetIndex(lista, right); i = i->next)
    {
        if(i->info < right->info)
        {
            SwapNodos(lista, i, pos);
            pos = pos->next;
        }
    }
    SwapNodos(lista, right,pos);
    return pos;
}
/*
m_Nodo *partition(m_Lista *nLista, m_Nodo *p, m_Nodo *r)
{
	if (p == NULL || r == NULL || nLista == NULL) return NULL;

	m_Nodo *i = p->previous, *j = p;
	int x = r->info, aux;
	while((j->next != NULL) && (j != r) && (p->next!=NULL)){
		if(j->info <= x){
			i = p;
			aux = i->info;
			i->info = j->info;
			j->info = aux;
			p = p->next;
		}
		j = j->next;
	}
	if((i == NULL && p->previous==NULL)||(i->previous == NULL)){		// Pivô menor que todos || lista andou somente uma posição
		aux = p->info;
		p->info = x;
		r->info = aux;
		return p;
	}
	aux = i->next->info;
	i->next->info = x;
	r->info = aux;
	return i->next;
}*/

void swap(m_Nodo *nodo1, m_Nodo *nodo2)
{
    int aux = nodo1->info;
    nodo1->info = nodo2->info;
    nodo2->info = aux;
}
void SwapNodos(m_Lista *lista, m_Nodo *left, m_Nodo *right)
{
	left->next = right->next;
	right->previous = left->previous;
	if(left->next != NULL)
		left->next->previous = left;
	else
		lista->last = left;
	if(right->previous != NULL)
		right->previous->next = right;
	else
		lista->first = right;
	left->previous = right;
	right->next = left;
}
int GetIndex(m_Lista *lista, m_Nodo *nodo)
{
    int i;
    m_Nodo *aux;
    for(i = 0, aux = lista->first; aux != nodo; i++)
    {
         aux = aux->next;
    }
    return i;
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
