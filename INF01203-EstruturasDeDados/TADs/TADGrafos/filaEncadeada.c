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

int contem(TipoDFila * descritor, TipoInfo desejado) {
    TipoFila * lista = descritor->prim;  // Trata a fila como uma lista para essa operacao
    while (lista != NULL) {
        if (lista->dado == desejado) return 1;
        lista = lista->elo;
    }
    return 0;
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

int insereComPrioridade(TipoDFila ** descritor, TipoInfo dado, int ordem) {
    TipoFila * novo = malloc(sizeof(TipoFila));
    TipoFila * atual;
    int encontrouPos = 0;

    if ( (*descritor)->prim == NULL ) { // Primeira insercao na fila
        novo->dado = dado;
        novo->elo = NULL;
        (*descritor)->prim = novo;
        (*descritor)->ult = novo;
    } else if ( (*descritor)->prim == (*descritor)->ult ) { // Nao precisa buscar posicao dentro da fila
        atual = (*descritor)->prim;
        novo->dado = dado;
        if ( (ordem == CRESCENTE) && atual->dado > dado ||
             (ordem == DECRESCENTE) && atual->dado < dado ) {
            novo->elo = atual;
            (*descritor)->prim = novo;
        } else {
            atual->elo = novo;
            novo->elo = NULL;
            (*descritor)->ult = novo;
        }
    } else { // Deve encontrar posicao dentro da fila

        atual = (*descritor)->prim;
        novo->dado = dado;

        if ( (ordem == CRESCENTE) && atual->dado > dado  ) {
            novo->elo = atual;
            (*descritor)->prim = novo;
        } else if ( (ordem == DECRESCENTE) && atual->dado < dado ) {
            novo->elo = atual;
            (*descritor)->prim = novo;
        } else {

            while (atual && !encontrouPos) {
                if( atual->dado == dado ) {
                    novo->elo = atual->elo;
                    atual->elo = novo;
                    if ( (*descritor)->ult == atual ) (*descritor)->ult = novo;
                    encontrouPos = 1;
//                } else if ( (ordem == DECRESCENTE) && atual->elo && (atual->elo->dado) < dado ) {
                } else if ( (ordem == CRESCENTE) && atual->elo && (atual->elo->dado) > dado ) {
                    novo->elo = atual->elo;
                    atual->elo = novo;
                    encontrouPos = 1;
                } else if ( (ordem == DECRESCENTE) && atual->elo && (atual->elo->dado < dado) ) {
                    novo->elo = atual->elo;
                    atual->elo = novo;
                    encontrouPos = 1;
                } else if (!atual->elo) {
                    atual->elo = novo;
                    novo->elo = NULL;
                    (*descritor)->ult = novo;
                    encontrouPos = 1;
                }
                atual = atual->elo;
            }

        }
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

