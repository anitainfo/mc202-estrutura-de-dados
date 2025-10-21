#include<stdio.h>
#include<math.h>

int main(){
    int n,m,x,y;
    int teste = 0;
    scanf("%d %d", &m,&n);
    while(n!=0 || m!=0){
        int v[m][n],f[m][n];
        int total_col=0, total_lin=0;
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                scanf("%d", &v[i][j]);
            }
        }
        scanf("%d %d", &x, &y);
        while(x!=0 || y!=0){
            total_col+=x;
            total_lin+=y;
            scanf("%d %d", &x, &y);
        }
        total_lin*=(-1);
        total_col%=n;
        total_lin%=m;
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                int nova_lin=i+total_lin;
                int nova_col=j+total_col;
                if(nova_lin>=m){
                    nova_lin=total_lin-(m-1-i)-1;
                }
                else if(nova_lin<0){
                    nova_lin=(m-1)+(total_lin+i)+1;
                }
                if(nova_col>=n){
                    nova_col=total_col-(n-1-j)-1;
                }
                else if(nova_col<0){
                    nova_col=n-1+(total_col+j)+1;
                }
                f[nova_lin][nova_col]=v[i][j];
            }
        }
        printf("Teste %d\n", ++teste);
        for(int i=0; i<m; i++){
            for(int j=0; j<n; j++){
                if(j!=n-1)printf("%d ", f[i][j]);
                else printf("%d", f[i][j]);
            }
            printf("\n");
        }
        printf("\n");
        scanf("%d %d", &m,&n);
    }
}