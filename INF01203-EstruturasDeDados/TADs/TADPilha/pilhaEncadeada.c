#include "pilhaEncadeada.h"
#ifndef NULL
    #define NULL (void *) 0
#endif // NULL

TipoPilha * inicializa() {
    return NULL;
}

void printaElemento(TipoInfo dado) {
    printf("\n-- Print Elemento: --\n");
    printf("%d\n", dado);
    printf("----\n");
}

void printaPilha(TipoPilha * pilha) {

    if (vazia(pilha)) {
        printf("\n---- PILHA VAZIA ----\n");
    } else {
        while(pilha) {
            printaElemento(pilha->dado);
            pilha = pilha->elo;
        }
    }

}

int vazia(TipoPilha * pilha) {
    return pilha == NULL;
}

TipoPilha * push(TipoPilha * pilha, TipoInfo dado) {
    TipoPilha * novo = malloc(sizeof(TipoPilha));
    novo->dado = dado;
    novo->elo = pilha;
    return novo;
}

int pop(TipoPilha ** pilha, TipoInfo * dado) {
    TipoPilha * aux;
    TipoInfo topo = consulta(*pilha);
    if (topo > -1) {
        *dado = topo;
        aux = *pilha;
        *pilha = (*pilha)->elo;
        free(aux);
        return 1;
    } else {
        return 0;
    }
}

TipoInfo consulta(TipoPilha * pilha) {
    if (!vazia(pilha)) {
        return pilha->dado;
    } else {
        return -1; // Sinal de erro
    }
}

TipoPilha * destroi(TipoPilha * pilha) {
    TipoPilha * aux;
    while (pilha != NULL) {
        aux = pilha;
        pilha = pilha->elo;
        free(aux);
    }
    return NULL;
}
