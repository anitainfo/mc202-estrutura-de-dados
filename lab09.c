#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}node;

node* criacao_no(int data){
  node *atual = (node*)malloc(sizeof(node));
  atual->data = data;
  atual->left = NULL;
  atual->right = NULL;
  return atual;
}

/*
Função para criar recursivamente uma árvore em representação explícita 
dada uma árvore binária que armazena chaves naturais em representação implícita
*/
node* criacao_arvore(int* vet, int id, int n){
    if(id>n) return NULL;
    if(vet[id]==-1) return NULL;
    node *raiz = criacao_no(vet[id]);
    raiz->left = criacao_arvore(vet, 2*id, n);
    raiz->right = criacao_arvore(vet, (2*id)+1, n);
    return raiz;
}

/*
Função para imprimir o passeio de Euler de uma árvore e já liberar 
a memória alocada dinamicamente por cada nó
*/
void impressao_euler(node* raiz){
    printf("%d ", raiz->data);
    if(raiz->left!=NULL){
        impressao_euler(raiz->left);
        printf("%d ", raiz->data);
    }
    if(raiz->right!=NULL){
        impressao_euler(raiz->right);
        printf("%d ", raiz->data);
    }
    free(raiz);
}

int main()
{
    int n;
    scanf("%d", &n);
    while(n!=0){
        int vet[n+1];
        for(int i=1; i<=n; i++){
            scanf("%d", &vet[i]);
        }
        node *raiz = criacao_arvore(vet, 1, n);
        impressao_euler(raiz);
        printf("\n");
        scanf("%d", &n);
    }
    return 0;
}
