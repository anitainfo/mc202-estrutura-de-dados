#include <stdio.h>
#include <math.h>

int main(){
    int n,a,b;
    char t;
    scanf("%d", &n); //leitura do 'n'
    int raiz = ceil(sqrt(n)); //define tamanho dos blocos
    int v[n], r[raiz+10];
    int id = 0;
    r[0] = 0; //zera soma do primeiro bloco

    /*
    Lê cada número do vetor e adiciona seu 
    valor à soma do bloco que ele pertence
    */
    for(int i=0; i<n; i++){
        scanf("%d", &v[i]);
        r[id]+=v[i];
        if((i+1)%raiz==0 && i!=0){ //checa se precisa trocar de bloco 
            id++;
            r[id] = 0;
        }
    }

    while(scanf("%c %d %d", &t, &a, &b)!=EOF){ //lê toda a entrada e processa cada operação
        if(t=='s'){ //operação do tipo 's'
            int pref=0;
            long long int res = 0;
            for(int i=a; i<=b; i++){
                /*
                Para cada elemento i no intervalo de 'a' a 'b' verifica se ele
                pertence a um bloco inteiramente contido no intervalo ou, caso contrário,
                soma apenas o valor do próprio elemento à resposta final
                */
                if(pref==0){ //existe parte à esquerda do 1º bloco
                    res += v[i];
                    if(((i+1)%raiz==0)){ //verifica se o próximo elemento é o 1º de um bloco
                        pref = 1;
                    }
                }
                else if((i+raiz-1)<=b){ //1º elemento de um bloco inteiramente contido no intervalo
                    res += r[i/raiz];
                    i += raiz-1; //soma a i a qtd de elementos num bloco (desconsidera i++)
                }
                else{ //existe parte à direita do último bloco
                    res += v[i];
                }
            }
            printf("%lld\n", res);
        }
        else if(t=='a'){ //operação tipo 'a'
            /*
            Altera o valor do bloco ao qual o elemento 'a' pertence
            (b-v[a]) e atualiza o valor de 'a' no vetor 
            */
            int div = floor(a/raiz);
            r[div]+=(b-v[a]);
            v[a]=b;
        }
    }
}