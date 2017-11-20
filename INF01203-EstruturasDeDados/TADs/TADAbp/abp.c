#include "abp.h"
#ifndef NULL
    #define NULL (void *) 0
#endif // NULL


// FUNCOES
ABP * inicializa_abp () {
    return NULL;
}

ABP * insere_abp(ABP * raiz, int chave, char info) {
    ABP * novo;

    if (!raiz) {
        novo = malloc(sizeof(ABP));
        novo->chave = chave;
        novo->info = info;
        novo->esq = NULL;
        novo->dir = NULL;
        return novo;
    } else {
        if (chave < raiz->chave) {
            raiz->esq = insere_abp(raiz->esq, chave, info);
        } else {
            raiz->dir = insere_abp(raiz->dir, chave, info);
        }
        return raiz;
    }

}

void printa_info_abp(ABP * nodo) {
    if (nodo) {
        printf("%c (%d)\n", nodo->info, nodo->chave);
    } else {
        printf("NULL\n");
    }
}

void lista_abp(ABP * raiz, int caminhamento) {

    switch(caminhamento) {

        case PRE_ESQUERDA:
            printa_info_abp(raiz);
            if (raiz) {
                lista_abp(raiz->esq, PRE_ESQUERDA);
                lista_abp(raiz->dir, PRE_ESQUERDA);
            }
            break;

        case CENTRAL_ESQUERDA:
            if (raiz)
                lista_abp(raiz->esq, CENTRAL_ESQUERDA);
            printa_info_abp(raiz);
            if (raiz)
                lista_abp(raiz->dir, CENTRAL_ESQUERDA);
            break;

        case POS_ESQUERDA:
            if (raiz) {
                lista_abp(raiz->esq, POS_ESQUERDA);
                lista_abp(raiz->dir, POS_ESQUERDA);
            }
            printa_info_abp(raiz);
            break;

        case PRE_DIREITA:
            printa_info_abp(raiz);
            if (raiz) {
                lista_abp(raiz->dir, PRE_DIREITA);
                lista_abp(raiz->esq, PRE_DIREITA);
            }
            break;

        case CENTRAL_DIREITA:
            if (raiz)
                lista_abp(raiz->dir, CENTRAL_DIREITA);
            printa_info_abp(raiz);
            if (raiz)
                lista_abp(raiz->esq, CENTRAL_DIREITA);
            break;

        case POS_DIREITA:
            if (raiz) {
                lista_abp(raiz->dir, POS_DIREITA);
                lista_abp(raiz->esq, POS_DIREITA);
            }
            printa_info_abp(raiz);
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
