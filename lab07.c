#include <stdlib.h>
#include <stdio.h>

struct node {
  int data;
  struct node* next;
  struct node* prev;
};

typedef struct node node;

struct llist {
  node* head;
  node* tail;
};

typedef struct llist llist;

llist* criacao() {
  llist* L = malloc(sizeof(llist));
  L->head = malloc(sizeof(node));
  L->tail = malloc(sizeof(node));
  L->head->next = L->tail;
  L->tail->prev = L->head;
  L->head->prev = L->tail->next = NULL;
  return L;
}

/*
Função para imprimir os elementos de uma lista duplamente encadeada.
*/
void impressao(llist* L){
    node* p = L->head->next;
    while(p->next != NULL){
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

/*
Função que checa para uma posição pos qual a melhor origem de busca (head, nó da ultima busca ou tail),
imprime o valor em pos e a quantidade de nós percorridos para chegar nela 
e retorna o nó de pos para usar de referência na próxima busca
*/
node* busca(llist* L, int ini, int meio, int fim, int pos, node* aux){
    int dif1 = abs(ini-pos);
    int dif2 = abs(meio-pos);
    int dif3 = abs(fim-pos);
    node* p;
    
    if(dif1<=dif2 && dif1<dif3){ // procura partindo da cabeça
        int cont = 0;
        p = L->head->next;
        while(cont < dif1){
            p = p->next;
            cont+=1;
        }
        printf("%d %d\n", p->data, cont+1);
    }
    else if(dif2<dif1 && dif2<dif3){ // procura partindo da pos da última busca
        if(meio<=pos){ // se ultima busca foi numa pos antes de pos atual
            int cont = 0;
            p = aux;
            while(cont < dif2){
                p = p->next;
                cont+=1;
            }
            printf("%d %d\n", p->data, cont+1);
        }
        else{ // se ultima busca foi numa pos depois de pos atual
            int cont = 0;
            p = aux;
            while(cont < dif2){
                p = p->prev;
                cont+=1;
            }
            printf("%d %d\n", p->data, cont+1);
        }
    }
    else{ // procura partindo do rabo
        int cont = 0;
        p = L->tail->prev;
        while(cont < dif3){
            p = p->prev;
            cont+=1;
        }
        printf("%d %d\n", p->data, cont+1);
    }
    return p;
}

/*
Função para inserir um elemento no final de uma lista duplamente encadeada.
Retorna 1 se for bem sucedida ou 0 caso contrario.
*/
int insercao_final(llist* L, int data){
    node* n = malloc(sizeof(node));
    if(n == NULL) return 0;
    n->data = data;
    node* p = L->tail;
    n->prev = p->prev;
    n->next = p;
    p->prev->next = n;
    p->prev = n;
    return 1;
}

/*
Função para liberar toda a memória alocada dinamicamente ao longo do programa.
*/
void destruicao(llist* L){
    node* atual = L->head;
    node* next = NULL;
    while(atual != NULL){
        next = atual->next;
        free(atual);
        atual = next;
    }
    free(L);
}

int main(){
    int m,n,val;
    llist* L = criacao();
    
    scanf("%d", &m);
    for(int i=0; i<m; i++){
        scanf("%d", &val);
        insercao_final(L,val);
    }
    impressao(L);
    
    int last = 0;
    node* q = L->head->next;
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d", &val);
        q = busca(L,0,last,m-1,val,q);
        last = val;
    }
    destruicao(L);
}