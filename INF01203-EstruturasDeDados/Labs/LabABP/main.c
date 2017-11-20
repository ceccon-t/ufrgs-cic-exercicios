#include<stdio.h>
#include "abp.h"

int main() {
    ABP * arvore = inicializa_abp();
    int mostraNiveis;

    arvore = insere_abp(arvore, 8);
    arvore = insere_abp(arvore, 4);
    arvore = insere_abp(arvore, 9);
    arvore = insere_abp(arvore, 2);
    arvore = insere_abp(arvore, 6);
    arvore = insere_abp(arvore, 1);

    mostraNiveis = 0;

    lista_abp(arvore, PRE_ESQUERDA, mostraNiveis, 1);

    printf("\n");

    mostraNiveis = 1;

    lista_abp(arvore, PRE_ESQUERDA, mostraNiveis, 1);

    printf("\n\n--- Total de nodos: %d\n", totalNodos(arvore));

    printf("\n\n--- Total de folhas na arvore: %d\n", total_folhas(arvore));

    printf("\n--- FIM ---\n");
    return 0;
}
