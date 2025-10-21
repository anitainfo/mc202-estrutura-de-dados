#include<stdio.h>
#include<math.h>
#include<stdbool.h>
#include<stdlib.h>

// struct para armazenar coordenadas e valor correspondente
struct tripla {
    int linha;
    int coluna;
    int valor;
};

// Função de comparação para ordenar struct por ordem de linhas e depois colunas
int cmp(const void *a, const void *b)
{
    if (((struct tripla *) a)->linha != ((struct tripla *) b)->linha) {
        return ((struct tripla *) a)->linha - ((struct tripla *) b)->linha;
    }
    return ((struct tripla *) a)->coluna - ((struct tripla *) b)->coluna;
}

int main()
{
    int k, i, j;
    scanf("%d", &k);
    
    // Aloca memória dinâmica para armazenar as coordenadas e vetores a e c
    struct tripla *coord = (struct tripla *)malloc(k*sizeof(struct tripla));
    int *a = (int *)malloc(k*sizeof(int));
    int *c = (int *)malloc(k*sizeof(int));
    
    /*
    Lê as coordenadas e valores da entrada e salva os maiores números 
    de linha e coluna para saber tamanho mínimo da matriz
    */
    int m = 0, n = 0;
    for (int i = 0; i < k; i++) {
        scanf("%d %d %d", &coord[i].linha, &coord[i].coluna, &coord[i].valor);
        m = fmax((coord[i].linha) + 1, m);
        n = fmax((coord[i].coluna) + 1, n);
    }
    
    // Alocação de memória dinâmica para armazenar vetor r 
    int *r = (int *)malloc((m+1)*sizeof(int));
    
    // Ordena struct de coordenadas primeiro por linha depois por coluna
    qsort(coord, k, sizeof(struct tripla), cmp);
    
    // Insere dados correspondentes nos vetores a, c e r já com struct ordenada
    int last = -1;
    for (int i = 0; i < k; i++) {
        a[i] = coord[i].valor; // a -> própio valor do elemento correspondente
        c[i] = coord[i].coluna; // c -> própria coluna do elemento correspondente
        
        // r -> se for uma linha nova coloca o índice atual como 1º elemento da linha (r[linha] = i)
        if (last != coord[i].linha)
            r[coord[i].linha] = i;
            
        /*
        Se for uma linha com distância > 1 da última linha (last):
            -> linhas entre elas são apenas de 0's, então cada 
               uma recebe o mesmo valor da linha atual
        */
        if (coord[i].linha != last && coord[i].linha != (last + 1)) {
            for (int j = last + 1; j < coord[i].linha; j++) {
                r[j] = r[coord[i].linha];
            }
        }
        last = coord[i].linha; // Atualiza índice da última linha vista
    }
    r[m] = k; // Última posição de r guarda a quantidade total de elementos != 0
    
    // Libera memória alocada dinamicamente para as coordenadas
    free(coord); 
    
    // Consulta das coordenadas em que se deseja recuperar um elemento
    scanf("%d %d", &i, &j);
    while (i != -1 || j != -1) {
        
        // Se estiver fora da matriz mínima
        if (i >= m || j >= n) {
            printf("(%d,%d) = 0\n", i, j);
            scanf("%d %d", &i, &j);
            continue;
        }
        
        // Determina o intervalo ocupado pelos elementos da linha i em C e A
        int dif = r[i + 1] - r[i];
        
        int ok = 0;
        
        // Coluna solicitada é procurada de C[r[i]] até C[r[i]+dif-1]
        for (int k = r[i]; k < r[i] + dif; k++) {
            if (c[k] == j) { // Se j existe em C, imprime elemento 
                printf("(%d,%d) = %d\n", i, j, a[k]);
                ok = 1;
                break;
            }
        }
        if (ok == 0) { // Se j não existe em C, imprime 0
            printf("(%d,%d) = 0\n", i, j);
        }
        scanf("%d %d", &i, &j);
    }
    
    // Libera memória alocada dinamicamente para os vetores a, c e r
    free(a);
    free(c);
    free(r);

    return 0;
}
