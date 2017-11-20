#include "filaEncadeada.h"
#ifndef NULL
    #define NULL (void *) 0
#endif

TipoDFila * inicializa() {
    TipoDFila * descritor = malloc(sizeof(TipoDFila));

    descritor->prim = NULL;
    descritor->ult = NULL;

    return descritor;
}

void printaElemento(TipoInfo dado) {
    printf("\n-- Elemento: %d\n", dado);
}

void printaFila(TipoDFila * descritor) {
    TipoFila * fila = descritor->prim;
    if (fila) {
        while (fila) {
            printaElemento(fila->dado);
            fila = fila->elo;
        }
    } else {
        printf("\n---- FILA VAZIA ----\n");
    }
}

int vazia(TipoDFila * descritor) {
    if (descritor->prim) {
        return 0;
    } else {
        return 1;
    }
}

TipoInfo consulta(TipoDFila * descritor) {
    if (!vazia(descritor)) {
        return descritor->prim->dado;
    } else {
        return -1;
    }
}

int insere(TipoDFila ** descritor, TipoInfo dado) {
    TipoFila * novo = malloc(sizeof(TipoFila));

    novo->dado = dado;

    novo->elo = NULL;

    if ((*descritor)->ult) {
        (*descritor)->ult->elo = novo;
    }

    (*descritor)->ult = novo;

    if ((*descritor)->prim == NULL) {
        (*descritor)->prim = novo;
    }

    return 1;
}

int remover(TipoDFila ** descritor, TipoInfo * dado) {
    TipoFila * aux = (*descritor)->prim;

    if (!vazia(*descritor)) {
        *dado = aux->dado;
        if ( (*descritor)->prim == (*descritor)->ult ) {
            (*descritor)->prim = NULL;
            (*descritor)->ult = NULL;
        } else {
            (*descritor)->prim = aux->elo;
        }
        free(aux);
        return 1;
    } else {
        return 0;
    }
}

void destroi(TipoDFila ** descritor) {
    TipoFila * fila = (*descritor)->prim, *aux;

    while (fila) {
        aux = fila;
        fila = fila->elo;
        free(aux);
    }

    //free(*descritor);
    (*descritor)->prim = NULL;
    (*descritor)->ult = NULL;
}

