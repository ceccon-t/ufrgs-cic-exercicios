#include<stdio.h>
#include "avl.h"

int main() {
    AVL * arvore = inicializa_avl();
    int mostraNiveis = 1, ok = 1;


    printf("\n\n====================================================================\n\n");
    printf("\nArvore com fator 1:\n\n");

    arvore = destroi_avl(arvore);

    arvore = insere_abp(arvore, 42);
    arvore = insere_abp(arvore, 15);
    arvore = insere_abp(arvore, 6);
    arvore = insere_abp(arvore, 27);
    arvore = insere_abp(arvore, 20);
    arvore = insere_abp(arvore, 88);
    arvore = insere_abp(arvore, 63);
    arvore = insere_abp(arvore, 94);
    arvore = insere_abp(arvore, 57);
    arvore = insere_abp(arvore, 71);

    mostraNiveis = 1;

    lista_avl(arvore, PRE_ESQUERDA, mostraNiveis, 1);

    printf("\n\n--- Total de nodos: %d\n", totalNodos(arvore));

    printf("\n\n--- Fator da arvore: %d\n", fator_arvore(arvore));

    printf("\n\n====================================================================\n\n");
    printf("\nMesmos elementos da arvore anterior, agora AVL:\n\n");

    arvore = destroi_avl(arvore);

    arvore = insere_avl(arvore, 42, &ok);
    arvore = insere_avl(arvore, 15, &ok);
    arvore = insere_avl(arvore, 6, &ok);
    arvore = insere_avl(arvore, 27, &ok);
    arvore = insere_avl(arvore, 20, &ok);
    arvore = insere_avl(arvore, 88, &ok);
    arvore = insere_avl(arvore, 63, &ok);
    arvore = insere_avl(arvore, 94, &ok);
    arvore = insere_avl(arvore, 57, &ok);
    arvore = insere_avl(arvore, 71, &ok);

    mostraNiveis = 1;

    lista_avl(arvore, PRE_ESQUERDA, mostraNiveis, 1);

    printf("\n\n--- Total de nodos: %d\n", totalNodos(arvore));

    printf("\n\n--- Fator da arvore: %d\n", fator_arvore(arvore));

    printf("\n\n====================================================================\n\n");
    printf("\nArvore com fator 3:\n\n");

    arvore = destroi_avl(arvore);

    arvore = insere_abp(arvore, 42);
    arvore = insere_abp(arvore, 15);
    arvore = insere_abp(arvore, 27);
    arvore = insere_abp(arvore, 20);

    mostraNiveis = 1;

    lista_avl(arvore, PRE_ESQUERDA, mostraNiveis, 1);

    printf("\n\n--- Total de nodos: %d\n", totalNodos(arvore));

    printf("\n\n--- Fator da arvore: %d\n", fator_arvore(arvore));

    printf("\n\n====================================================================\n\n");
    printf("\nMesmos elementos da arvore anterior, agora AVL:\n\n");

    arvore = destroi_avl(arvore);

    arvore = insere_avl(arvore, 42, &ok);
    arvore = insere_avl(arvore, 15, &ok);
    arvore = insere_avl(arvore, 27, &ok);
    arvore = insere_avl(arvore, 20, &ok);

    mostraNiveis = 1;

    lista_avl(arvore, PRE_ESQUERDA, mostraNiveis, 1);

    printf("\n\n--- Total de nodos: %d\n", totalNodos(arvore));

    printf("\n\n--- Fator da arvore: %d\n", fator_arvore(arvore));

    printf("\n\n====================================================================\n\n");


    printf("\n--- FIM ---\n");
    return 0;
}
