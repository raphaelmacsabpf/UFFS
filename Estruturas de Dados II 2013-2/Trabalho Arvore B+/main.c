#include <stdio.h>
#include <stdlib.h>

#define BTORDER 2
#define PAGE_LENGTH BTORDER * 2 + 1
#define LEAF 1
#define TRUE 1
#define FALSE 0
#define FILENAME "arvore.tree"
#define MAX_INTEGER 4294967295



//STRUCTS
typedef struct tbplus
{
    int active;
    unsigned int adress;
    unsigned int father;
    unsigned int pointers[PAGE_LENGTH];
    unsigned int keys[PAGE_LENGTH];
    unsigned int next;
    int numitems;
    int type;

}tbplus;

//PROTOTYPES
tbplus* disk_read(FILE *fp);
void disk_write(FILE *fp,tbplus *tree);

//PROGRAM
int main()
{
    //TEMP
    time_t thetime;
    srand((unsigned) time(&thetime));
    //TEMP

    int op = 1;
    while(op != 0)
    {
        printf("Choose any option\n\n1-Insert\n2-Remove\n3-Print\n0-Exit\n");
        scanf("%d",&op);
        switch(op)
        {
            case 1:
            {
                int key;
                FILE *fp = fopen(FILENAME,"a+b");
                printf("Type a key to insert\n");
                scanf("%d",&key);
                tbplus_insert(fp,key);
                fclose(fp);
                break;
            }
            case 2:

                break;
            case 3:

                break;
        }
    }

    return 0;
}

tbplus* disk_read(FILE *fp)
{
    tbplus *tree;
    tree = (tbplus*) malloc(sizeof(tbplus));
    fread(tree,sizeof(tbplus),1,fp);
    return tree;
}
void disk_write(FILE *fp,tbplus *tree)
{
    fwrite(tree,sizeof(tbplus),1,fp);
}

void tbplus_insert(FILE *fp,int key)
{
    //CREATE SUB-TREE
    tbplus newsubtree;
    newsubtree.adress = 0;
    newsubtree.active = TRUE;
    newsubtree.father = 0;
    newsubtree.type = LEAF;
    newsubtree.numitems = 0;
    newsubtree.next = 0;
    int i;
    for(i = 0; i < PAGE_LENGTH; i++)
    {
        newsubtree.pointers[i] = MAX_INTEGER;
        newsubtree.keys[i] = MAX_INTEGER;
    }

    //FIND THE RIGHT POSITION TO INSERT
    fseek(fp,0,2);//TOP OF FILE
    if(ftell(fp) == 0)//EMPTY TREE
    {
        newsubtree.keys[0] = key;
        newsubtree.active = TRUE;
        newsubtree.numitems ++;
        newsubtree.adress = ftell(fp);
        disk_write(fp,&newsubtree);
    }
    else
    {
        fseek(fp,0,0);
        tbplus *auxread;
        int founded = FALSE;
        do
        {
            auxread = disk_read(fp);
            if(auxread->type == LEAF)
            {
                if(!KeyExistsOnLeaf(auxread,key))
                {
                    fclose(fp);
                    fp = fopen(FILENAME,"r+b");
                    auxread->keys[auxread->numitems] = key;
                    auxread->numitems ++;
                    BubbleSort(auxread->keys,auxread->pointers);
                    printf("NUM ITEMS == %d\n\n e adrress = %d",auxread->numitems,auxread->adress);
                    if(auxread->numitems == PAGE_LENGTH)//VERIFICA SE EXCEDEU O NÚMERO DE ITENS NESTA ARVORE
                    {
                        Cision(fp,auxread);
                    }
                    else
                    {
                        fseek(fp,auxread->adress,0);
                        disk_write(fp,auxread);
                        printf("AAAAAAAAAAAAAAAAAAAAAA   2\n\n");
                    }
                    fclose(fp);
                    fp = fopen(FILENAME,"a+b");
                }
                founded = TRUE;
            }
            else
            {
                int prox = 0;
                while(key > auxread->keys[prox] && prox < PAGE_LENGTH-1)
                    prox ++;
                fseek(fp,auxread->pointers[prox],0);
                printf("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA 3");
            }

        }while(!founded);
        printf("INFOS\n\nACTIVE = %d\nKEYS[0] = #   %d   #\n KEYS[1] = #   %d   #\n  KEYS[2] = #   %d   #\n KEYS[3] = #   %d   #\n KEYS[4] = #   %d   #\n\nTYPE = %d\n",auxread->active,auxread->keys[0],auxread->keys[1],auxread->keys[2],auxread->keys[3],auxread->keys[4],auxread->type);
        free(auxread);
    }
}
void Cision(FILE *fp, tbplus *node)
{
    if(node->numitems == PAGE_LENGTH)
    {
        tbplus *newfather = (tbplus*)malloc(sizeof(tbplus));
        newfather->active = TRUE;
        newfather->type = !LEAF;
        newfather->keys[0] = node->keys[(PAGE_LENGTH)/2];
        newfather->numitems = 0;
        newfather->pointers[0] = node->adress;

        tbplus *newbrother = (tbplus*)malloc(sizeof(tbplus));
        newbrother->active = TRUE;
        newbrother->type = LEAF;
        unsigned int less[PAGE_LENGTH];
        int numless = 0;
        int nummore = 0;
        unsigned int more[PAGE_LENGTH];
        int i;
        for(i = 0; i < PAGE_LENGTH; i++)
        {
            if(node->keys[i] < newfather->keys[0])
            {
                less[numless] = node->keys[i];
                numless++;
                printf("Adicionou no less\n");
            }
            else
            {
                more[nummore] = node->keys[i];
                nummore++;
                printf("Adicionou no more\n");
            }
        }
    }
}
void BubbleSort(unsigned int keys[PAGE_LENGTH],unsigned int pointers[PAGE_LENGTH])
{
    int i,j;
    for(i = 0; i < PAGE_LENGTH; i++)
    {
        for(j = 0; j < PAGE_LENGTH; j++)
        {
            if(keys[j] > keys[i] && keys[i] != MAX_INTEGER && keys[j] != MAX_INTEGER)
            {
                int aux,aux2;
                aux = keys[i];
                keys[i] = keys[j];
                keys[j] = aux;
                aux2 = pointers[i];
                pointers[i] = pointers[j];
                pointers[j] = aux2;
            }
        }
    }
}
int KeyExistsOnLeaf(tbplus *leaf,int key)
{
    int i, founded = FALSE;
    for(i = 0; i < PAGE_LENGTH-1; i++)
    {
        if(leaf->keys[i] == key)
            founded = TRUE;
    }
    return founded;
}
