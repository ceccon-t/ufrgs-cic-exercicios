#include "filme.h"


/* Operacoes */

TipoPtNo * inicializa() {
    //return (void *) 0;
    return NULL;
}

TipoPtNo * insereInicio(TipoPtNo *lista) {
    TipoPtNo *novo = malloc(sizeof(TipoPtNo));

    printf("\n-- Inserir novo elemento no inicio --\n");

    printf("Titulo: ");
    scanf("%s", &novo->info.titulo);
    printf("Diretor: ");
    scanf("%s", &novo->info.diretor);
    printf("Distribuicao: ");
    scanf("%s", &novo->info.distr);

    novo->prox = lista;

    return novo;

}

TipoPtNo * insereFim(TipoPtNo *lista) {
    TipoPtNo *novo = malloc(sizeof(TipoPtNo)), *aux = lista;

    printf("\n-- Inserir novo elemento no fim --\n");

    printf("Titulo: ");
    scanf("%s", &novo->info.titulo);
    printf("Diretor: ");
    scanf("%s", &novo->info.diretor);
    printf("Distribuicao: ");
    scanf("%s", &novo->info.distr);

    if (lista == NULL) {
        novo->prox = lista;
        return novo;
    } else {
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        aux->prox = novo;
        return lista;
    }

}

TipoPtNo * remover(TipoPtNo *lista, char titulo[]) {
    TipoPtNo *ant, *atual;

    if (lista == NULL) { // Lista vazia, nao ha o que remover
        return lista;
    } else if (strcmp(lista->info.titulo, titulo) == 0) { // Remover primeiro elemento da lista
        atual = lista->prox;
        free(lista);
        return atual;
    } else { // Procurar elemento para remover
        ant = lista;
        atual = lista->prox;
        while (atual != NULL) {
            if (strcmp(atual->info.titulo, titulo) == 0) {
                ant->prox = atual->prox;
                free(atual);
                return lista;
            } else {
                ant = atual;
                atual = atual->prox;
            }
        }
        return lista; // Elemento nao encontrado
    }
}

TipoPtNo * consulta(TipoPtNo *lista, char titulo[]) {
    TipoPtNo *elemento = lista;

    while((elemento != NULL) && (strcmp(elemento->info.titulo, titulo) != 0)) {
        elemento = elemento->prox;
    }

    return elemento;
}

void printaElemento(TipoInfoNo elemento) {
    printf("Titulo: %s\n", elemento.titulo);
    printf("Diretor: %s\n", elemento.diretor);
    printf("Distribuicao: %s\n\n", elemento.distr);
}


void listar(TipoPtNo * lista) {
    int cont = 0;

    printf("\n-- Listando elementos da lista: --\n");

    while (lista != NULL) {
        cont++;
        printf("Elemento %d:\n", cont);
        /*
        printf("Titulo: %s\n", lista->info.titulo);
        printf("Diretor: %s\n", lista->info.diretor);
        printf("Distribuicao: %s\n\n", lista->info.distr);
        */
        printaElemento(lista->info);

        lista = lista->prox;
    }

    printf("\nFim da lista.\n\n");

}


TipoPtNo * destroi(TipoPtNo * lista) {
    TipoPtNo * aux = lista, *aux2;

    while (aux != NULL) {
        aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }

    free(lista);

    return NULL;
}
