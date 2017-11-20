#include<stdio.h>
#include "produto.h"


int main() {
    TipoProduto prod;
    TipoPtProduto * lista;

    lista = inicializa();

    // PRODUTO 1
    prod.codigo = 3;
    strcpy(prod.nome, "teclado");
    prod.preco = 120;
    lista = insereProduto(lista, prod);

    // PRODUTO 2
    prod.codigo = 1;
    strcpy(prod.nome, "mouse");
    prod.preco = 90;
    lista = insereProduto(lista, prod);


    // PRODUTO 3
    prod.codigo = 4;
    strcpy(prod.nome, "pen drive");
    prod.preco = 50;
    lista = insereProduto(lista, prod);


    // PRODUTO 4
    prod.codigo = 2;
    strcpy(prod.nome, "HD externo");
    prod.preco = 300;
    lista = insereProduto(lista, prod);


    listar(lista);

    printf("\n-- FIM --\n");
    return 0;
}
