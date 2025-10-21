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
    printf("A: { ");
    node* p = L->head->next;
    if(p->next == L->tail){
        printf("%d }\n", p->data);
        return;
    }
    while(p->next->next != NULL){
        printf("%d, ", p->data);
        p = p->next;
    }
    printf("%d }\n", p->data);
}

/*
Função para inserir um elemento em qualquer posição de uma lista duplamente encadeada.
Retorna 1 se for bem sucedida ou 0 caso contrario.
*/
int insercao_geral(llist* L, int pos, int data){
    node* n = malloc(sizeof(node));
    if(n == NULL) return 0;
    n->data = data;
    node* p = L->head;
    while(pos > 0){
        p = p->next;
        pos--;
    }
    n->prev = p;
    n->next = p->next;
    p->next = n;
    n->next->prev = n;
    return 1;
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
Função para substituir uma lista duplamente encadeada por uma sublista 
em um intervalo de ini até fim da lista duplamente encadeada inicial.
Retorna 1 se for bem sucedida ou 0 caso contrario.
*/
int extrai_sublista(llist* L, int ini, int fim){
    if(ini <= fim){
        if(L->head){
            int cont = 0;
            node* p = L->head->next;
            while(cont < ini){
                p = p->next;
                free(p->prev);
                cont+=1;
            }
            L->head->next = p;
            p->prev = L->head;
            fim-=ini;
            while(fim > 0){
                p = p->next;
                fim-=1;
            }
            if(p == L->tail){
                return 1;
            }
            node* limpa = p->next;
            while(limpa->next != NULL){
                limpa = limpa->next;
                free(limpa->prev);
            }
            p->next = L->tail;
            L->tail->prev = p;
        }else{
            return 0;
        } 
    }else{ // ini > fim
        if(L->head){
            int cont = 0;
            node* p = L->head->next;
            while(cont < ini){
                p = p->next;
                cont+=1;
            }
            node* limpa = p->next;
            while(limpa->next!=NULL){
                limpa = limpa->next;
                free(limpa->prev);
            }
            L->head->next = p;
            while(ini > fim){
                node* aux = p->next;
                p->next = p->prev;
                p->prev = aux;
                p = p->next;
                ini-=1;
            }
            limpa = p->prev;
            if(limpa!=L->head){
                while(limpa->prev != L->head){
                    limpa = limpa->prev;
                    free(limpa->next);
                }
                free(limpa);
            }
            L->tail->prev = p;
            p->prev = p->next;
            p->next = L->tail;
            L->head->next->prev = L->head;
        }else{
            return 0;
        }
    }
    return 1;
}

/*
Função para extrair uma sublista em um intervalo de ini até fim da lista duplamente encadeada 
inicial e inserir essa sublista na posição pos da lista duplamente encadeada inicial
Retorna 1 se for bem sucedida ou 0 caso contrario.
*/
int extrai_sublista_e_substitui(llist* L, int ini, int fim, int pos){
    llist* Extra = criacao();
    if(ini <= fim){
        if(L->head){
            int cont = 0;
            node* p = L->head->next;
            while(cont < ini){
                p = p->next;
                cont+=1;
            }
            while(ini<=fim){
                insercao_final(Extra,p->data);
                p = p->next;
                ini+=1;
            }
            cont = 0;
            p = L->head->next;
            while(cont < pos){
                p = p->next;
                cont+=1;
            }
            p->prev->next = Extra->head->next;
            Extra->head->next->prev = p->prev;
            Extra->tail->prev->next = p;
            p->prev = Extra->tail->prev;
        }else{
            return 0;
        } 
    }else{ // ini > fim
        if(L->head){
            int cont = 0;
            node* p = L->head->next;
            while(cont < ini){
                p = p->next;
                cont+=1;
            }
            while(ini >= fim){
                insercao_final(Extra,p->data);
                p = p->prev;
                ini-=1;
            }
            cont = 0;
            p = L->head->next;
            while(cont < pos){
                p = p->next;
                cont+=1;
            }
            p->prev->next = Extra->head->next;
            Extra->head->next->prev = p->prev;
            Extra->tail->prev->next = p;
            p->prev = Extra->tail->prev;
        }else{
            return 0;
        }
    }
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
    int a,x,y,z;
    char c;
    llist* L = criacao();
    while(getchar()!='{');
    do{
        scanf("%d", &a);
        insercao_final(L,a);
    } while(getchar() == ',');
    while(getchar()!='\n');
    scanf("%c", &c);
    while(c!='f'){
        if(c=='s'){
            scanf(" A[%d..%d]\n", &x,&y);
            extrai_sublista(L,x,y);
            impressao(L);
        }
        else{
            scanf(" A[%d..%d] %d\n", &x,&y,&z);
            extrai_sublista_e_substitui(L,x,y,z);
            impressao(L);
        }
        scanf("%c", &c);
    }
    destruicao(L);
}