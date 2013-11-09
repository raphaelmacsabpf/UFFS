#include <stdio.h>

struct nodo
{
    int info;
    int color;
    struct nodo *father;
    struct nodo *left;
    struct nodo *right;
}typedef m_Nodo;
m_Nodo nil = (m_Nodo*)malloc(sizeof(m_Nodo));

int main()
{

    return 0;
}

void insert(m_Nodo *root,m_Nodo *father, int info)
{

}
