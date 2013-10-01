#include <stdio.h>

struct nodo
{
    int info;
    struct nodo *father;
    struct nodo *left;
    struct nodo *right;
}typedef m_Nodo;

int main()
{
    m_Nodo *tree = NULL;
    insert(&tree,&tree,1);
    insert(&tree,&tree,2);
    insert(&tree,&tree,3);
    insert(&tree,&tree,4);
    return 0;
}

void insert(m_Nodo *root,m_Nodo *father, int info)
{
    if(root == NULL)
    {
        root = (m_Nodo *)malloc(sizeof(m_Nodo));
        root->father = father;
        root->left = NULL;
        root->right = NULL;
        root->info = info;
    }
    else
        if(info < root->info)
            insert(root->left,root,info);
        else
            insert(root->right,root,info);
}
