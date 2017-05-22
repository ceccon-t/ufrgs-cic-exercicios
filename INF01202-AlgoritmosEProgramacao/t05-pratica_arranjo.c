/*
1. Manipulação de um arranjo de 10 elementos inteiros:
a) preencher o arranjo randomicamente, segundo exemplo abaixo;
b) imprimir os elementos do arranjo em uma só linha, separados por um asterisco;
c) ler um valor. Inserir este valor no início do arranjo, deslocando os elementos seguintes uma casa à direita. O último elemento é perdido.  Imprimir novamente;
d) substituir no arranjo os elementos de índice ímpar pelo valor deste índice. Imprimir novamente;
e) informar quantos elementos têm valor superior à media dos valores do arranjo;
*/

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#define NUM 10

int main() {
    int a[NUM];
    int VALOR_MAXIMO = 10;
    int i,r, valor, aux, acima_media = 0;
    float media = 0;
    
    srand(time(0));
    
    for (i=0; i < NUM; i++) {
        r = (int) (rand() / (double) RAND_MAX * (VALOR_MAXIMO+1));
        a[i] = r;
    }
    
    for (i=0;i<NUM;i++) {
        printf("%s%d", (i==0 ? "" : " * "), a[i]);
    }
    
    printf("\nDigite um valor a ser inserido no arranjo: ");
    scanf("%d", &valor);
    
    for (i=0; i < NUM; i++) {
        aux = a[i];
        a[i] = valor;
        valor = aux;
    }
    
    printf("\nNovo arranjo:\n");
    for (i=0;i<NUM;i++) {
        printf("%s%d", (i==0 ? "" : " * "), a[i]);
    }
    
    getchar();
    
    for (i = 0; i < NUM; i++) {
        if(i % 2) {
            a[i] = i;
        }
    }
    
    printf("\n\nArranjo com elementos de indice impares substituidos pelo indice:\n");
    for (i=0;i<NUM;i++) {
        printf("%s%d", (i==0 ? "" : " * "), a[i]);
    }
    
    
    for (i=0;i<NUM;i++) {
        media += a[i];
    }
    media = (media*1.0)/NUM;
    
    for (i=0;i<NUM;i++) {
        if(a[i] > media) {
            acima_media += 1;
        }
    }
    
    printf("\n\n%d elementos estao acima da media.\n", acima_media);

    
    printf("\nFim.\n");
    fflush(stdin);
    getchar();
    return 0;
}
