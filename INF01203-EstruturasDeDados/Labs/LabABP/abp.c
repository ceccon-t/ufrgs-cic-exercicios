#include "abp.h"
#ifndef NULL
    #define NULL (void *) 0
#endif // NULL


// FUNCOES
ABP * inicializa_abp () {
    return NULL;
}

ABP * insere_abp(ABP * raiz, int chave) {
    ABP * novo;

    if (!raiz) {
        novo = malloc(sizeof(ABP));
        novo->chave = chave;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    } else {
        if (chave < raiz->chave) {
            raiz->esq = insere_abp(raiz->esq, chave);
        } else {
            raiz->dir = insere_abp(raiz->dir, chave);
        }
        return raiz;
    }

}

void printa_info_abp(ABP * nodo, int mostraNiveis, int nivel) {
    int i;
    if (nodo) {
        if (mostraNiveis) {
            for (i = 0; i < nivel; i++) {
                printf("=");
            }
        }
        printf("%d\n", nodo->chave);
    } /* else {
        printf("NULL\n");
    } */
}

void lista_abp(ABP * raiz, int caminhamento, int mostraNiveis, int nivel) {


    switch(caminhamento) {

        case PRE_ESQUERDA:
            printa_info_abp(raiz, mostraNiveis, nivel);
            if (raiz) {
                lista_abp(raiz->esq, PRE_ESQUERDA, mostraNiveis, nivel+1);
                lista_abp(raiz->dir, PRE_ESQUERDA, mostraNiveis, nivel+1);
            }
            break;

        case CENTRAL_ESQUERDA:
            if (raiz)
                lista_abp(raiz->esq, CENTRAL_ESQUERDA, mostraNiveis, nivel+1);
            printa_info_abp(raiz, mostraNiveis, nivel);
            if (raiz)
                lista_abp(raiz->dir, CENTRAL_ESQUERDA, mostraNiveis, nivel+1);
            break;

        case POS_ESQUERDA:
            if (raiz) {
                lista_abp(raiz->esq, POS_ESQUERDA, mostraNiveis, nivel+1);
                lista_abp(raiz->dir, POS_ESQUERDA, mostraNiveis, nivel+1);
            }
            printa_info_abp(raiz, mostraNiveis, nivel);
            break;

        case PRE_DIREITA:
            printa_info_abp(raiz, mostraNiveis, nivel);
            if (raiz) {
                lista_abp(raiz->dir, PRE_DIREITA, mostraNiveis, nivel+1);
                lista_abp(raiz->esq, PRE_DIREITA, mostraNiveis, nivel+1);
            }
            break;

        case CENTRAL_DIREITA:
            if (raiz)
                lista_abp(raiz->dir, CENTRAL_DIREITA, mostraNiveis, nivel+1);
            printa_info_abp(raiz, mostraNiveis, nivel);
            if (raiz)
                lista_abp(raiz->esq, CENTRAL_DIREITA, mostraNiveis, nivel+1);
            break;

        case POS_DIREITA:
            if (raiz) {
                lista_abp(raiz->dir, POS_DIREITA, mostraNiveis, nivel+1);
                lista_abp(raiz->esq, POS_DIREITA, mostraNiveis, nivel+1);
            }
            printa_info_abp(raiz, mostraNiveis, nivel);
            break;

    }

}

ABP * destroi_abp(ABP * raiz) {

    if (raiz) {
        destroi_abp(raiz->esq);
        destroi_abp(raiz->dir);
        free(raiz);
    }

    return NULL;

}

//  LAB
int totalNodos(ABP * raiz) {
    if (raiz) {
        return totalNodos(raiz->esq) + totalNodos(raiz->dir) + 1;
    } else {
        return 0;
    }
}

/*
// Revisao P2
int total_folhas(ABP * raiz) {
    //int eh_folha;  // Vai receber 1 se nodo for folha, 0 se nao for (ou seja, "a contribuicao do nodo para o num. total de folhas")

    if (raiz) {  // Se a arvore nao for NAO-VAZIA (raiz nao eh NULL), calcula o total de arvores

        if ( (raiz->dir == NULL) && (raiz->esq == NULL) ) {  // Se ambos os filhos do nodo forem NULL, nodo eh folha
            //eh_folha = 1;
            return 1;
        } else {
            //eh_folha = 0;
            return total_folhas(raiz->esq) + total_folhas(raiz->dir);
        }

        //return eh_folha + total_folhas(raiz->esq) + total_folhas(raiz->dir);

    } else {  // Se a arvore for VAZIA, nao tem folhas
        return 0;
    }
*/
// Revisao P2
int total_folhas(ABP * raiz) {

    if (raiz) {  // Se a arvore nao for NAO-VAZIA (raiz nao eh NULL), continua calculando o total de arvores

        if ( (raiz->dir == NULL) && (raiz->esq == NULL) ) {  // Se ambos os filhos do nodo forem NULL, nodo eh folha
            return 1;
        } else {  // Se nao forem ambos NULL, nodo nao eh folha e deve-se calcular o total de folhas nas suas sub-arvores
            return total_folhas(raiz->esq) + total_folhas(raiz->dir);
        }

    } else {  // Chegou no final dessa sub-arvore, nao ha mais folhas
        return 0;
    }


}
