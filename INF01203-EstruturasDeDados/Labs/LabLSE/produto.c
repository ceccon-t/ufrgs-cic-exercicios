#include<string.h>
#include "produto.h"


/* Operacoes */

TipoPtProduto * inicializa() {
    return NULL;
}

TipoProduto geraProduto() {
    TipoProduto prod;

    printf("Codigo: ");
    scanf("%d", &prod.codigo);
    printf("Nome: ");
    scanf(" %s", &prod.nome);
    printf("Preco: ");
    scanf("%f",prod.preco);

    return prod;
}

TipoPtProduto * insereProduto(TipoPtProduto *lista, TipoProduto prod) {
    TipoPtProduto *novo = malloc(sizeof(TipoPtProduto));
    TipoPtProduto *atual = lista;
    TipoPtProduto *anterior = lista;

    novo->produto = prod;

    if (lista == NULL) { // Lista vazia, inserir no inicio e retornar novo inicio
        novo->prox = NULL;
        return novo;
    } else if(prod.codigo < lista->produto.codigo) { // Codigo menor que o primeiro elemento, inserir no inicio e retornar novo inicio
        novo->prox = lista;
        return novo;
    } else { // Inserir no meio (ou fim da lista)
        anterior = lista;
        atual = lista->prox;
        while (atual && (prod.codigo > atual->produto.codigo)) {
            anterior = atual;
            atual = atual->prox;
        }
        novo->prox = atual;
        anterior->prox = novo;
    }

    return lista;

}

void printaElemento(TipoProduto elemento) {
    printf("Codigo: %d\n", elemento.codigo);
    printf("Nome: %s\n", elemento.nome);
    printf("Preco: %.2f\n\n", elemento.preco);
}


void listar(TipoPtProduto * lista) {
    int cont = 0;

    printf("\n-- Listando elementos da lista: --\n");

    while (lista != NULL) {
        cont++;
        printf("Elemento %d:\n\n", cont);
        printaElemento(lista->produto);

        lista = lista->prox;

        printf("\n--\n");
    }

    printf("\nFim da lista.\n\n");

}



TipoPtProduto * destroi(TipoPtProduto * lista) {
    TipoPtProduto * aux = lista, *aux2;

    while (aux != NULL) {
        aux2 = aux->prox;
        free(aux);
        aux = aux2;
    }

    free(lista);

    return NULL;
}



