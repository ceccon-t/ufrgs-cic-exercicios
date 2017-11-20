/* OPERACOES */
#include "deque.h"

#ifndef NULL
    #define NULL (void *) 0
#endif // NULL

TipoDescDeque * inicializa() {
    TipoDescDeque * descritor = malloc(sizeof(TipoDescDeque));

    descritor->prim = NULL;
    descritor->ult = NULL;

    return descritor;
}

int vazio(TipoDescDeque * descritor) {
    return descritor->prim == NULL;
}

void printaElemento(TipoInfo elemento) {
    printf("--\nELEMENTO: \n-\n");
    printf("Valor: %d\n", elemento);
    printf("-\n--");
}


void listar(TipoDescDeque * descritor) {
    TipoDeque * deque;

    printf("\n--- LISTAR: ---\n");

    if (descritor->prim) {
        deque = descritor->prim;
        while(deque) {
            printaElemento(deque->info);
            deque = deque->prox;
        }
    } else {
        printf("\nDeque vazio.\n");
    }

    printf("\n---------------\n");

}

void listarInverso(TipoDescDeque * descritor) {
    TipoDeque * deque;

    printf("\n--- LISTAR: ---\n");

    if (descritor->prim) {
        deque = descritor->ult;
        while(deque) {
            printaElemento(deque->info);
            deque = deque->ant;
        }
    } else {
        printf("\nDeque vazio.\n");
    }

    printf("\n---------------\n");

}

int insereInicio(TipoDescDeque ** descritor, TipoInfo info) {
    TipoDeque * novo = malloc(sizeof(TipoDeque));

    novo->info = info;
    novo->ant = NULL;
    novo->prox = (*descritor)->prim;
    if ((*descritor)->prim) {
        (*descritor)->prim->ant = novo;
    } else { // Deque vazio
        (*descritor)->ult = novo;
    }
    (*descritor)->prim = novo;
    return 1;
}


int insereFim(TipoDescDeque ** descritor, TipoInfo info) {
    TipoDeque * novo = malloc(sizeof(TipoDeque)), *aux;

    novo->info = info;
    novo->prox = NULL;

    if ( (*descritor)->ult ) {
        novo->ant = (*descritor)->ult;
        (*descritor)->ult->prox = novo;
        (*descritor)->ult = novo;
    } else { // Deque vazio
        (*descritor)->prim = novo;
        (*descritor)->ult = novo;
    }

    return 1;
}

int insere(TipoDescDeque ** descritor, TipoInfo info, int lado) {
    if (lado == INICIO) {
        return insereInicio(descritor, info);
    } else {
        return insereFim(descritor, info);
    }
}

TipoInfo consulta(TipoDescDeque * descritor, int lado) {

    if (!descritor->prim) {
        return -1;
    } else {
        if (lado == INICIO) {
            return descritor->prim->info;
        } else {
            return descritor->ult->info;
        }
    }

}

TipoInfo removerPrimeiro(TipoDescDeque ** descritor) {
    TipoDeque * aux;
    TipoInfo removido;

    if (!vazio(*descritor)) {
        removido = (*descritor)->prim->info;
        aux = (*descritor)->prim;
        (*descritor)->prim = aux->prox;
        if (aux->prox == NULL) { // Deque so tinha um elemento, agora deve ficar vazio
            (*descritor)->ult = NULL;
        } else {
            (*descritor)->prim->ant = NULL;
        }
        free(aux);
        return removido;
    } else {
        return -1;
    }

}

TipoInfo removerUltimo(TipoDescDeque ** descritor) {
    TipoDeque * aux;
    TipoInfo removido;

    if (!vazio(*descritor)) {
        removido = (*descritor)->ult->info;
        aux = (*descritor)->ult;
        if (aux == (*descritor)->prim) { //Deque so tinha um elemento, deve ficar vazio
            (*descritor)->prim = NULL;
        }
        (*descritor)->ult = aux->ant;
        (*descritor)->ult->prox = NULL;
        free(aux);
        return removido;
    } else {
        return -1;
    }

}

TipoInfo remover(TipoDeque ** descritor, int lado) {

    if (lado == INICIO) {
        removerPrimeiro(descritor);
    } else {
        removerUltimo(descritor);
    }
}


void destroi(TipoDescDeque ** descritor) {
    TipoDeque * deque, * aux;

    deque = (*descritor)->prim;

    while (deque) {
        aux = deque;
        deque = deque->prox;
        free(aux);
    }

    (*descritor)->prim = NULL;
    (*descritor)->ult = NULL;

}

