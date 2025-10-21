#include<stdio.h>
#include<math.h>

int main(){
    int n,e,b;
    char a;
    int dir[200010];
    char letra[200010];
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        scanf("%d %c %d", &e,&a,&b);
        letra[e]=a;
        dir[e]=b;
    }
    int atual = 0;
    while(atual != 1){
        printf("%c", letra[atual]);
        atual = dir[atual];
    }
    printf("\n");
}