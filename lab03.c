#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>

int main(){
    int k, e,teste=0;
    int ops[10010];
    char palavras[25][110];
    char desculpas[10010][110],desc_minusculas[10010][110];
    while(scanf("%d %d\n", &k, &e)!=EOF){
        int cont[10010];

        /*
        Reinicia o vetor de palavras e lê as palavras-chave na entrada
        */
        for(int i=0; i<k; i++){
            memset(palavras[i],' ',strlen(palavras[i]));
            scanf("%s", palavras[i]);
        }
        scanf("\n");

        /*
        Lê as desculpas na entrada, transforma todos os caracteres em minúsculas
        e salva em uma outra matriz de caracteres (desc_minusculas)
        */
        for(int i=0; i<e; i++){
            scanf("%[^\n]", desculpas[i]);
            int j=0;
            while(j<strlen(desculpas[i])){
                desc_minusculas[i][j] = tolower(desculpas[i][j]);
                j++;
            }
            scanf("\n");
        }

        /*
        Passa por cada desculpa e checa a ocorrência de cada palavra
        ->Se encontrar, altera o 1ª caractere dela para não encontrá-la novamente e 
        checa se a palavra é válida na frase
            ->Se é válida, adiciona 1 a cont[] da desculpa correspondente
            ->Se não é válida, salva o índice do 1ª caractere alterado p/ 
            desaltar no final (pode ser a substring de uma próxima palavra 
            ainda não procurada)
        Guarda em 'maior' o maior nº de ocorrências encontrado
        */ 
        int maior = 0;
        for(int i=0; i<e; i++){
            cont[i]=0;
            int erros=0;
            int j=0;
            while(j<k){
                // *achou -> ponteiro para 1ª ocorrência da palavra
                char *achou = strstr(desc_minusculas[i],palavras[j]); 
                if(achou!=NULL){ // se a palavra ocorre na desculpa
                    char ant=*(achou-1); // ponteiro p/ caractere anterior à 1ª letra da palavra encontrada
                    char prox=*(achou+strlen(palavras[j])); // ponteiro p/ próximo caractere depois da última letra da palavra encontrada
                    desc_minusculas[i][achou-desc_minusculas[i]]='C'; //altera 1º caractere da ocorrência
                    
                    // checa se ant e prox são caracteres não alfabético
                    if(((ant<65) || (ant>90 && ant<97) || (ant>122)) && ((prox<65) || (prox>90 && prox<97) || (prox>122))){
                        cont[i]++;
                    }else{
                        ops[erros]=achou-desc_minusculas[i]; // guarda índice alterado
                        erros++;
                    }
                }else{
                    j++;
                    /*
                    Passa pelo vetor de índices alterados incorretamente 
                    e troca eles para o caractere antigo 
                    */ 
                    for(int k=0; k<erros; k++){
                        desc_minusculas[i][ops[k]]=tolower(desculpas[i][ops[k]]);
                    }
                }
            }
            maior = fmax(maior,cont[i]); // verifica se a desculpa teve mais ocorrências
        }

        /*
        Passa por todas as desculpas e imprime aquelas que possuem o nº de ocorrências
        equivalente a 'maior' (maior nº de ocorrências)
        */
        printf("Conjunto de desculpas #%d\n", ++teste);
        for(int i=0; i<e; i++){
            if(cont[i]==maior){
                printf("%s\n",desculpas[i]);
            }
            memset(desculpas[i],' ',strlen(desculpas[i])); // reinicia vetor de desculpas[i]
            memset(desc_minusculas[i],' ',strlen(desc_minusculas[i])); // reinicia vetor de desc_minusculas[i]
        }
        printf("\n");
    }
}