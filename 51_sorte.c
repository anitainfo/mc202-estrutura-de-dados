#include<stdio.h>
#include<math.h>

int repete(int num){
    int v[11];
    for(int i=0; i<=9; i++){
        v[i]=0;
    }
    while(num>0){
        int alg = num%10;
        if(v[alg]!=0)return 1;
        v[alg]=1;
        num/=10;
    }
    return 0;
}

int main(){
    int n,m;
    int cont = 0;
    scanf("%d %d", &n, &m);
    for(int i=n; i<=m; i++){
        int aux = repete(i);
        if(aux==0){
            cont++;
        }
    }
    printf("%d\n", cont);
}