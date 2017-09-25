#include<stdio.h>
#include "lse.h"

int main() {
    TipoPTLseI *lista, *pares, *impares;
    int i;

    printf("\nINICIALIZANDO LISTA\n");
    lista = inicializa();
    listar(lista);
    printf("\n====\n");

    printf("\nLista contem 1: %d\n", contem(lista, 1));

    printf("\nPREENCHENDO LISTA COM FOR\n");
    for(i = 0; i <= 10; i++) {
        lista = insere(lista, i);
    }

    listar(lista);
    printf("\n====\n");

    printf("\nNumero de elementos: %d\n", numElementos(lista));
    printf("\n====\n");

    printf("\nMaior numero da lista: %d\n", maiorNum(lista));
    printf("\n====\n");

    printf("\nLista contem 1: %d\n", contem(lista, 1));
    printf("\nLista contem 15: %d\n", contem(lista, 15));
    printf("\n====\n");

    printf("\nREMOVENDO REPETIDOS\n");
    lista = removeRepetidos(lista);
    listar(lista);
    printf("\n====\n");

    //pares = inicializa();
    //impares = inicializa();
    printf("\nSEPARANDO EM PARES E IMPARES\n");
    separaParesImpares(lista, &pares, &impares);
    printf("\nLista pares:\n");
    listar(pares);
    printf("\nLista impares:\n");
    listar(impares);


    printf("\nCOMPARACAO DE IGUALDADE\n");
    printf("\nLista eh igual a si propria: %d\n", iguais(lista, lista));
    printf("\nLista eh igual a lista vazia: %d\n", iguais(lista, inicializa()));
    printf("\n====\n");

    printf("\nTROCANDO VALORES\n");
    printf("\nTrocando ocorrencias de 5 por 42: ");
    substituiValores(lista, 5, 42);
    listar(lista);
    printf("\n====\n");

    printf("\nMaior numero da lista: %d\n", maiorNum(lista));
    printf("\n====\n");

    printf("\nINVERTENDO LISTA\n");
    lista = inverte(lista);
    listar(lista);


    printf("\nDESTRUINDO LISTA\n");
    lista = destroi(lista);
    listar(lista);
    printf("\n====\n");


    printf("\nPREENCHENDO LISTA MANUALMENTE\n");
    lista = inicializa();
    lista = insere(lista, 7);
    lista = insere(lista, 1);
    lista = insere(lista, 6);
    lista = insere(lista, 8);
    lista = insere(lista, 8);
    lista = insere(lista, 9);
    lista = insere(lista, 3);
    lista = insere(lista, 7);
    listar(lista);

    printf("\nTROCANDO VALORES\n");
    printf("\nTrocando ocorrencias de 7 por 81: ");
    substituiValores(lista, 7, 81);
    listar(lista);
    printf("\n====\n");

    printf("\nREMOVENDO REPETIDOS\n");
    lista = removeRepetidos(lista);
    listar(lista);

    printf("\nREMOVENDO IMPARES\n");
    lista = removeImpares(lista);
    listar(lista);

    printf("\nNumero de elementos: %d\n", numElementos(lista));
    printf("\n====\n");

    printf("\n--- FIM ---\n");
    return 0;
}
