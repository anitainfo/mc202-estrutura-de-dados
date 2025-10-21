#include <stdio.h>
#include<math.h>
#include<stdbool.h>
#include<stdlib.h>

/*
Função que retorna 0 se uma determinada data é válida e 1 caso contrário
Antes de 02/09/1752 -> ano bissexto %4
Depois de 02/09/1752 -> ano bissexto %4 && (!%100 || %400)
*/
bool check_valida(int dia, int mes, int ano){
    if(mes<1 || mes>12)return 1;
    if(ano<0001)return 1;
    if((mes==1 || mes==3 || mes==5 || mes==7 || mes==8 || mes==10 || mes==12)  && (dia<1 || dia>31)) return 1;
    else if((mes==4 || mes==6 || mes==9 || mes==11) && (dia<1 || dia>30)) return 1;
    else if(mes==2){
        if(dia<1 || dia>29) return 1;
        if(ano<=1752){
            if(ano%4!=0 && dia>28) return 1;
        }
        else{
            if(dia>28 && !(ano%4==0 && (ano%100!=0 || ano%400==0))) return 1;
        }
    }
    else if(ano==1752 && mes==9 && dia>2 && dia<14)return 1;
    return 0;
}

/*
Função que imprime o dia da semana correspondente a uma data, 
tomando o dia 'ini' como referência e sendo 1 - segunda-feira (até 7 - domingo)
*/
void imprime_dia(int ini, int soma, int dia, int mes, int ano){
    soma+=ini;
    soma%=7;
    if(soma==0) printf("%02d/%02d/%04d: domingo\n", dia, mes, ano);
    else if(soma==1) printf("%02d/%02d/%04d: segunda\n", dia, mes, ano);
    else if(soma==2) printf("%02d/%02d/%04d: terca\n", dia, mes, ano);
    else if(soma==3) printf("%02d/%02d/%04d: quarta\n", dia, mes, ano);
    else if(soma==4) printf("%02d/%02d/%04d: quinta\n", dia, mes, ano);
    else if(soma==5) printf("%02d/%02d/%04d: sexta\n", dia, mes, ano);
    else if(soma==6) printf("%02d/%02d/%04d: sabado\n", dia, mes, ano);
}

/*
Função que retorna a quantidade de dias que se passaram até 
o mês correspondente, com as regras de até 02/09/1752
*/
int conta_mes_antes(int mes, int ano){
    int total = 0;
    if(mes>=1)total+=31;
    if(mes>=2 && ano%4==0)total+=29;
    if(mes>=2 && ano%4!=0)total+=28;
    if(mes>=3)total+=31;
    if(mes>=4)total+=30;
    if(mes>=5)total+=31;
    if(mes>=6)total+=30;
    if(mes>=7)total+=31;
    if(mes>=8)total+=31;
    if(mes>=9)total+=30;
    if(mes>=10)total+=31;
    if(mes>=11)total+=30;
    if(mes>=12)total+=31;
    return total;
}

/*
Função que retorna a quantidade de dias que se passaram até 
o mês correspondente, com as regras de depois de 02/09/1752
*/
int conta_mes_depois(int mes, int ano){
    int total = 0;
    if(mes>=1)total+=31;
    if(mes>=2 && (ano%4==0 && (ano%100!=0 || ano%400==0)))total+=29;
    if(mes>=2 && !(ano%4==0 && (ano%100!=0 || ano%400==0)))total+=28;
    if(mes>=3)total+=31;
    if(mes>=4)total+=30;
    if(mes>=5)total+=31;
    if(mes>=6)total+=30;
    if(mes>=7)total+=31;
    if(mes>=8)total+=31;
    if(mes>=9)total+=30;
    if(mes>=10)total+=31;
    if(mes>=11)total+=30;
    if(mes>=12)total+=31;
    return total;
}

/*
Função que calcula a quantidade de dias que se passaram até 
a data correspondente, com as regras de até 02/09/1752, e
solicita impressão do dia da semana da data correpondente
*/
void conta_anos_antes(int dia, int mes, int ano){
    
    // total = dias_até_ano_anterior + dias_extras_bissexto + dias_até_mes_anterior + dia
    int total = ((ano-1)*365) + ((ano-1)/4) + conta_mes_antes(mes-1,ano) + dia;
    imprime_dia(5,total%7,dia,mes,ano);
}

/*
Função que calcula a quantidade de dias que se passaram até 
a data correspondente, com as regras de depois de 02/09/1752, 
e solicita impressão do dia da semana da data correpondente
*/
void conta_anos_depois(int dia, int mes, int ano){
    int total=0;
    if(ano==1752){ // se data até 31/12/1752
        if(mes==9){ // se data até 30/09/1752
            total = dia-13; // desconsidera dias da mudança de regra
        }
        else{ // ano = 1752, 9 < mes <= 12
            total = conta_mes_antes(mes-1,ano) + dia - 271; // desconsidera dias até fim do mes 9 
        }
    }
    else{ // ano > 1752
        // total = dias_até_ano_anterior + dias_extras_bissexto + dias_até_mes_anterior + dia + dias_em_1752_depois_da_mudança
        total = ((ano-1)*365) + ((ano-1)/4) - ((ano-1)/100) + ((ano-1)/400) + conta_mes_depois(mes-1,ano) + dia + 95;
    }
    imprime_dia(3,total%7,dia,mes,ano);
}

int main() {
    int d, m, a;
    scanf("%d %d %d", &d, &m, &a);
    while(d!=0 || m!=0 || a!=0){
        if(!check_valida(d,m,a)){ // checa se é uma data vállida
            if(a<1752 || (a==1752 && (m<9 || (m==9 && d<=2)))){ // se for antes da mudança de calendário
                conta_anos_antes(d,m,a);
            }
            else{ // se for depois da mudança de calendário
                conta_anos_depois(d,m,a);
            }
        }
        else{ // caso data inválida
            printf("%02d/%02d/%04d: invalida\n", d,m,a);
        }
        scanf("%d %d %d", &d, &m, &a);
    }
    return 0;
}