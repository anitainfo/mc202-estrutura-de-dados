#include<stdio.h>
#include<math.h>

int main(){
    int n,x,y;
    scanf("%d", &n);
    int v[n+10];
    v[0]=0;
    int teste = 0;
    while(n!=0){
        for(int i=1; i<=n; i++)
        {
            scanf("%d %d", &x,&y);
            v[i]=v[i-1]+(x-y);
        }
        int maior_saldo=-1, id1=0,id2=0;
        for(int i=1; i<=n; i++){
            for(int j=i; j<=n; j++){
                if(v[j]-v[i-1]>=maior_saldo){
                    if(v[j]-v[i-1]>maior_saldo || (j-i)>id2-id1){
                        maior_saldo = v[j]-v[i-1];
                        id2=j;
                        id1=i;
                    }
                }
            }
        }
        printf("Teste %d\n", ++teste);
        if(maior_saldo>0){
            printf("%d %d\n\n", id1, id2);
        }
        else{
            printf("nenhum\n\n");
        }
        scanf("%d", &n);
    }
}