#include <stdio.h>
#include <stdlib.h>

typedef struct node{
    int data;
    int id;
    int prof;
    struct node* left;
    struct node* right;
}node;

node* criacao_no(int data, int i) {
  node *atual = (node*)malloc(sizeof(node));
  atual->data = data;
  atual->id = i;
  atual->prof = 0;
  atual->left = NULL;
  atual->right = NULL;
  return atual;
}

/*
Função para imprimir os nós de uma árvore cartesiana separando-os por níveis de profundidade da mesma.
*/
void impressao_arvore(node *raiz){
  node *queue[100000];
  int ini=0, fim=0, last_prof = 0;
  queue[ini] = raiz;
  fim+=1;
  while(ini<fim){
      node *atual = queue[ini];
      if(atual->prof!=last_prof) printf("\n"); // se for de um nível diferente, pula linha
      printf("%d ", atual->id);
      last_prof = atual->prof;
      if(atual->left!=NULL){ // se tem filho na esquerda
        queue[fim] = atual->left;
        atual->left->prof = atual->prof+1;
        fim+=1;
      } 
      if(atual->right!=NULL){ // se tem filho na direita
        queue[fim] = atual->right;
        atual->right->prof = atual->prof+1;
        fim+=1;
      } 
      ini+=1;
  }
  printf("\n");
}

/*
Função para criar uma árvore cartesiana com o auxílio de uma pilha.
*/
node* criacao_arvore(int vet[], int n){
    node *raiz = criacao_no(vet[0],0);
    node *pilha[100000];
    int topo = 0;
    pilha[topo] = raiz;
    for(int i=1; i<n; i++) {
        node *atual = criacao_no(vet[i],i);
        node *last = NULL;
        while((topo>=0) && (pilha[topo]->data>vet[i])){ // desempilha enquanto topo for maior que vet[i]
            last = pilha[topo];
            topo-=1;
        }
        if(topo>=0) pilha[topo]->right = atual; // atual vira filho direito do topo da pilha
        else raiz = atual; // atual vira raiz da árvore
        atual->left = last; // último nó desempilhado vira filho esquerdo de vet[i]
        topo+=1;
        pilha[topo] = atual;
    }
    return raiz;
}

int main()
{
    int n;
    scanf("%d", &n);
    while(n!=0){
        int vet[n];
        for(int i=0; i<n; i++){
            scanf("%d", &vet[i]);
        }
        node *raiz = criacao_arvore(vet,n);
        impressao_arvore(raiz);
        printf("\n");
        scanf("%d", &n);
    }
    return 0;
}
