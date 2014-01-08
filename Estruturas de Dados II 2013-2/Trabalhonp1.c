#include <stdlib.h>
#include <stdio.h>
#define VERMELHO 1
#define PRETO 0

typedef struct Node{
	struct Node *father;
	struct Node *left;
	struct Node *right;
	int key;
	int cor;
	int nivel;
}Node;

typedef struct Tree {
	struct Node *root;
	struct Node *nil;
}Tree;

void insert(Tree *tree, int valor);
void delete(Tree *tree, int key);
void search(Tree *tree, int key);
void showTree(Tree * tree, Node *n);
void inorder(Tree *tree, Node *n);
void print(Tree *tree, Node *n, int nivel);
void level(Tree *tree, Node *n, int level);
void atualizaLevel(Tree *tree, Node *n, int nivel);
void verify(Tree *tree);
void removeFixup(Tree *tree, Node *x);
void insertFixUp(Tree *tree, Node *z);
void rightRotate(Tree *tree, Node *y);
void leftRotate(Tree *tree, Node *y);
Tree *inicializar(Tree *tree);
Node *min(Tree *tree, Node *root);
Node *successor(Tree *tree, Node *n);

int main(){
	int op = 1, key;
	struct Tree *tree = NULL;
	tree = inicializar(tree);
	while(op != 0){
		printf("\n1 - Inserir\n2 - Remover\n3 - Mostrar in-order\n4 - Imprimir nível\n5 - Buscar\n6 - Imprimir árvore em sua estrutura\n7 - Verificar propriedades\n0 - Sair\n");
		scanf("%d", &op);
		switch (op){
			case 1:
				printf("Entre com o valor a ser inserido:  ");
				scanf("%d", &key);
				insert(tree, key);
				break;
			case 2:
				printf("Entre com a chave a ser removida: ");
				scanf("%d", &key);
				delete(tree, key);
				printf("\n");
				break;
			case 3:
				printf("\nLista de nodos da árvore in-order:\n\n");
				inorder(tree, tree->root);
				printf("\n\n");
				break;
			case 4:
				printf("Entre com o nível: ");
				scanf("%d", &key);
				printf("\n");
				atualizaLevel(tree, tree->root, 0);
				level(tree, tree->root, key);
				printf("\n\n");
				break;
			case 5:
				printf("Entre com a chave a ser buscada: ");
				scanf("%d", &key);
				search(tree, key);
				break;
			case 6:
				printf("\n\n");
				print(tree, tree->root, 1);
				printf("\n\n");
				break;
			case 7:
				printf("\n");
				verify(tree);
				printf("\n\n");
				break;
		}
	}
	
	return 0;
}
void delete(Tree *tree, int key){
	Node *x, *y, *z, *nil = tree->nil, *root = tree->root;

	z = tree->root;
	while(z != nil){	//Busca da chave
		if (z->key == key)
			break;
		else if (z->key > key)
			z = z->left;
		else
			z = z->right;
	}
	if (z == nil)
		return;
	
	y = ((z->left == nil) || (z->right == nil)) ? z : successor(tree, z);
  	x = (y->left == nil) ? y->right : y->left;
	
	x->father = y->father;

	if(y->father == NULL){
		tree->root = x;
	}else{
		if(y == y->father->left)
			y->father->left = x;
		else // y == y->father->right
			y->father->right = x;
	}

	if(y != z){
		if (z == root && y->right == nil){
			y->father = nil;
			z->key = y->key;
			if (root->left->cor == PRETO){
				root->left->cor = VERMELHO;
				//removeFixup(tree, z->left);
			}
			return;
		}
		if((y == successor(tree, z)) && (y->left == nil) && (y->right == nil) && (z != root)){
			z->key = y->key;
			//removeFixup(tree, z);
			return;
		}
		
		if(y->cor == PRETO) removeFixup(tree, x);
		
		y->left = z->left;
		y->right = z->right;
		y->father = z->father;
		z->left->father = z->right->father = y;

		if(z->father == NULL){ // sucessor é uma folha!
			z->key = y->key;
			return;
		}

		y->cor = z->cor;
		if (z == z->father->left)
		    z->father->left = y; 
		else
		    z->father->right = y;
		//free(z);
	}else if (y->cor == PRETO)
		removeFixup(tree, x);

	free(y);
	
}

void removeFixup(Tree *tree, Node *x){
	Node *w, *root = tree->root->left;
	
	while(x != root && x->cor == PRETO){
		if(x == x->father->left){
			w = x->father->right;
			if(w->cor == VERMELHO){
				w->cor = PRETO;
				x->father->cor = VERMELHO;
				leftRotate(tree, x->father);
				w = x->father->right;
			}
			if(w->left->cor == PRETO && w->right->cor == PRETO){
				w->cor = VERMELHO;
				x = x->father;
			}
			else{
				if(w->right->cor == PRETO){
					w->left->cor = PRETO;
					w->cor = VERMELHO;
					rightRotate(tree, w);
					w = x->father->right;
				}
				w->cor = x->father->cor;
				x->father->cor = PRETO;
				w->right->cor = PRETO;
				leftRotate(tree, x->father);
				x = root;
			}
		}
		else{
			w = x->father->left;
			if(w->cor == VERMELHO){
				w->cor = PRETO;
				x->father->cor = VERMELHO;
				rightRotate(tree, x->father);
				w = x->father->left;
			}
			if(w->right->cor == PRETO && w->left->cor == PRETO){
				w->cor = VERMELHO;
				x = x->father;
			}
			else{
				if(w->left->cor == PRETO){
					w->right->cor = PRETO;
					w->cor = VERMELHO;
					leftRotate(tree, w);
					w = x->father->left;
				}
				w->cor = x->father->cor;
				x->father->cor = PRETO;
				w->left->cor = PRETO;
				rightRotate(tree, x->father);
				x = root;
			}
		}
	}
	if (x == tree->nil){
		tree->root = tree->nil;
		return;
	}
	x->cor = PRETO;
}
void atualizaLevel(Tree *tree, Node *n, int nivel){
	if (n != tree->nil) {
		n->nivel = nivel;
		atualizaLevel(tree, n->left, nivel+1);
		atualizaLevel(tree, n->right, nivel+1); 
    }
}
void level(Tree * tree, Node *n, int nivel){
	if (n != tree->nil) {
	if(n->nivel == nivel)
		printf("%d ", n->key);
	level(tree, n->left, nivel);
	level(tree, n->right, nivel); 
    }
}
void verify(Tree *tree){

}
void print(Tree *tree, Node *n, int nivel){
    int i;
    if(n == tree->nil)
        return;
    print(tree, n->right, nivel+1);
    for(i = 1; i < nivel; i++)
        printf("       ");
    if (n->cor == PRETO)
        printf("[%d] <´\n", n->key);
    else
    	printf("(%d) <´\n", n->key);
     print(tree, n->left, nivel+1);     
}

void inorder(Tree *tree, Node *n){
    if (n != tree->nil) {
       inorder(tree, n->left);
       printf("%d ", n->key);
       inorder(tree, n->right); 
    }
}

void search(Tree *tree, int k){
	Node *n;

	n = tree->root;
	while(n != tree->nil){
		if (n->key == k){
			printf("True\n");
			return;
		}
		else if (n->key > k)
			n = n->left;
		else
			n = n->right;
	}
	printf("False\n");
}

Tree *inicializar(Tree *tree){
	Node *aux;
	tree = (Tree *) malloc(sizeof(Tree)); //Aloca a árvore
	aux = tree->nil = (Node *) malloc(sizeof(Node)); 
	aux->father = aux->left = aux->right = aux; //Faz pai e filhos apontar pra nil
	aux->cor = PRETO; //Todo nil é preto
	aux->key = 0;

	tree->root = tree->nil;

	return tree;
}

void insert(Tree *tree, int valor){
	Node *x, *y, *z, *nil = tree->nil;

	z = (Node *) malloc(sizeof(Node));
	z->key = valor;
	z->left = z->right = nil; // Filhos nulos e pretos

	if(tree->root == nil){
		z->cor = PRETO;
		tree->root = z;
		return;
	}
	x = y = tree->root;

	while(x != nil){
		y = x;
		if(x->key == z->key)
			return;
		if(x->key > z->key)
			x = x->left;
		else
			x = x->right;
	}
	z->father = y;
	if(valor < y->key)
		y->left = z;
	else
		y->right = z;

	z->cor = VERMELHO; //Todo nodo inserido é vermelho
	insertFixUp(tree, z);

}

void insertFixUp(Tree *tree, Node *z){
	Node *y;

	while(z->father != NULL && z->father->cor == VERMELHO){
		if (z->father == z->father->father->left){
			y = z->father->father->right;
			if (y->cor == VERMELHO){
				z->father->cor = PRETO;
				y->cor = PRETO;
				z->father->father->cor = VERMELHO;
				z = z->father->father;
			}
			else {
				if (z == z->father->right){
					z = z->father;
					leftRotate(tree, z);
				}
				z->father->cor = PRETO;
				z->father->father->cor = VERMELHO;
				rightRotate(tree, z->father->father);
			}
		}
		else{
			y = z->father->father->left;
  			if(y->cor == VERMELHO){
   				z->father->cor = PRETO;
    			y->cor = PRETO;
    			z->father->father->cor = VERMELHO;
    			z = z->father->father;
  			}
  			else{
		        if(z == z->father->left){
		        	z = z->father;
		        	rightRotate(tree, z);
		        }
		        z->father->cor = PRETO;
		        z->father->father->cor = VERMELHO;
		        leftRotate(tree, z->father->father);
  			}
		}
	}
	tree->root->cor = PRETO;
}
void rightRotate(Tree *tree, Node *y) {
	Node *x = y->left, *father = y->father;
	x->father = y->father;
	y->father = x;

	if(father) {
		if(father->right == y) {
			father->right = x;
		} else if(father->left == y) {
			father->left = x;
		}
	} else {
		tree->root = x;
	}
	if(x->right) {
		y->left = x->right;
		y->left->father = y;
	} else {
		y->left=tree->nil;
	}
	x->right = y;
}

void leftRotate(Tree *tree, Node *y) {
	Node *x = y->right, *father = y->father;
	x->father = y->father;
	y->father = x;

	if(father) {
		if(father->right == y) {
			father->right = x;
		} else if (father->left == y) {
			father->left = x;
		}
	} else {
		tree->root = x;
	}
	if(x->left) {
		y->right = x->left;
		y->right->father = y;
	} else {
		y->right = tree->nil;
	}	
	x->left = y;
}
Node *min(Tree *tree, Node *root){
  while(root->left != tree->nil)
    root = root->left;
  return root;
}
Node *successor(Tree *tree, Node *n){
	Node *p = n->father;

	if(n->right != tree->nil)
		n = min(tree, n->right);
	else{ 
		while(p != tree->nil && n == p->right){
			n = p;
			p = n->father;
		}
		n = p;
	}
	return n;
}