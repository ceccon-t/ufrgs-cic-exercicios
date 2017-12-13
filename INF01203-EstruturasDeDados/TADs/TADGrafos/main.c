#include<stdio.h>
#include<stdlib.h>
#include "filaEncadeada.h"
#include "grafo.h"

void testa_colore();

int main() {

    TipoDFila * acessiveis;
    TipoDFila * prioridade;
    TipoDFila * adjs;
    TipoFila * item;
    int i;





    //testa_colore();

    //return 0;

    testa_dijkstra();

    return 0;


    GRAFO grafo = inicializa_grafo(8);

    adiciona_arco(grafo, 0, 1, 0, 1);
    adiciona_arco(grafo, 0, 2, 0, 1);
    adiciona_arco(grafo, 1, 3, 0, 1);
    adiciona_arco(grafo, 2, 3, 0, 1);
    adiciona_arco(grafo, 2, 4, 0, 1);
    adiciona_arco(grafo, 3, 4, 0, 1);
    adiciona_arco(grafo, 3, 5, 0, 1);
    adiciona_arco(grafo, 3, 7, 0, 1);
    adiciona_arco(grafo, 5, 4, 0, 1);
    adiciona_arco(grafo, 6, 1, 0, 1);
    adiciona_arco(grafo, 7, 6, 0, 1);



    printf("\n--- Matriz de adjacencia ---\n");
    printa_matriz_arcos(grafo);


    // TODO: Para grafos direcionados, o que deve contar são as arcos que CHEGAM nele, os que SAEM, ou ambos?
    printf("\n\n=== TESTANDO GRAU ===\n");

    for (i = 0; i < grafo.numVertices; i++) {
        printf("Grau do vertice %d: %d\n", i, grau_vertice(grafo, i));
    }



    printf("\n\n=== TESTANDO LISTAS DE ADJACENCIA ===\n");


    adjs = fila_adjacentes(grafo, 0); printf("\n-------\n");
    printaFila(adjs);

    set_cor_vertice(grafo, 1, 7);
    set_cor_vertice(grafo, 2, 1);

    printf("\nCores do vertices adjacentes: \n");
    item = adjs->prim;
    while (item != NULL) {
        printf("Cor do vertice %d: %d\n", item->dado, get_cor_vertice(grafo, item->dado));
        item = item->elo;
    }

    printaFila(adjs);

    printf("\n-- Testando cor presente em adj --\n");
    printf("Cor 0 presente em adjacentes: %d\n", cor_em_adjacentes(grafo, adjs, 0));
    printf("Cor 1 presente em adjacentes: %d\n", cor_em_adjacentes(grafo, adjs, 1));
    printf("Cor 3 presente em adjacentes: %d\n", cor_em_adjacentes(grafo, adjs, 3));
    printf("Cor 7 presente em adjacentes: %d\n", cor_em_adjacentes(grafo, adjs, 7));
    printf("Cor 8 presente em adjacentes: %d\n", cor_em_adjacentes(grafo, adjs, 8));

    adjs = fila_adjacentes(grafo, 1); printf("\n-------\n");
    printaFila(adjs);
    adjs = fila_adjacentes(grafo, 2); printf("\n-------\n");
    printaFila(adjs);
    adjs = fila_adjacentes(grafo, 3); printf("\n-------\n");
    printaFila(adjs);



    return 0;



    printf("\n--- Depth First Search, comecando em 1 ---\n");
    depth_first_search(grafo, 0);
    printf("\n--- Depth First Search, comecando em 3 ---\n");
    depth_first_search(grafo, 2);
    printf("\n--- Depth First Search, comecando em 5 ---\n");
    depth_first_search(grafo, 4);


    printf("\n\n=====\n\n");

    printf("\n--- Breadth First Search, comecando em 1 ---\n");
    breadth_first_search(grafo, 0);

    printf("\n\n--- Breadth First Search, comecando em 3 ---\n");
    breadth_first_search(grafo, 2);

    printf("\n\n--- Breadth First Search, comecando em 5 ---\n");
    breadth_first_search(grafo, 4);


    printf("\n\n=====\n\n");

    printf("\n--- Acessiveis atraves de 1: ---\n");
    acessiveis = acessiveis_bfs(grafo, 0);
    printaFila(acessiveis);
    printf("\n5 eh acessivel atraves de 1: %d", acessivel(grafo, 0, 4));

    printf("\n--- Acessiveis atraves de 3: ---\n");
    acessiveis = acessiveis_bfs(grafo, 2);
    printaFila(acessiveis);
    printf("\n1 eh acessivel atraves de 3: %d", acessivel(grafo, 2, 0));
    printf("\n5 eh acessivel atraves de 3: %d", acessivel(grafo, 2, 4));

    printf("\n--- Acessiveis atraves de 5: ---\n");
    acessiveis = acessiveis_bfs(grafo, 4);
    printaFila(acessiveis);
    printf("\n1 eh acessivel atraves de 5: %d", acessivel(grafo, 4, 0));


    printf("\n\n ==== TESTANDO FILA COM PRIORIDADE ==== \n\n");
    prioridade = inicializa();
    insereComPrioridade(&prioridade, 5, CRESCENTE);
    insereComPrioridade(&prioridade, 3, CRESCENTE);
    insereComPrioridade(&prioridade, 1, CRESCENTE);
    insereComPrioridade(&prioridade, 2, CRESCENTE);
    insereComPrioridade(&prioridade, 7, CRESCENTE);
    insereComPrioridade(&prioridade, 6, CRESCENTE);
    insereComPrioridade(&prioridade, 8, CRESCENTE);
    insereComPrioridade(&prioridade, 9, CRESCENTE);

    printaFila(prioridade);

    destroi(&prioridade);

    printf("\n\n ==== TESTANDO FILA COM PRIORIDADE DECRESCENTE ==== \n\n");
    prioridade = inicializa();
    insereComPrioridade(&prioridade, 5, DECRESCENTE);
    insereComPrioridade(&prioridade, 3, DECRESCENTE);
    insereComPrioridade(&prioridade, 1, DECRESCENTE);
    insereComPrioridade(&prioridade, 2, DECRESCENTE);
    insereComPrioridade(&prioridade, 7, DECRESCENTE);
    insereComPrioridade(&prioridade, 6, DECRESCENTE);
    insereComPrioridade(&prioridade, 8, DECRESCENTE);
    insereComPrioridade(&prioridade, 9, DECRESCENTE);

    printaFila(prioridade);


    printf("\n--- FIM ---\n");
    return 0;


}

void testa_colore() {

    int i;

    GRAFO grafo = inicializa_grafo(6);

    adiciona_arco(grafo, 0, 1, 1, 1);
    adiciona_arco(grafo, 0, 5, 1, 1);
    adiciona_arco(grafo, 1, 2, 1, 1);
    adiciona_arco(grafo, 1, 3, 1, 1);
    adiciona_arco(grafo, 2, 3, 1, 1);
    adiciona_arco(grafo, 2, 4, 1, 1);
    adiciona_arco(grafo, 3, 4, 1, 1);
    adiciona_arco(grafo, 3, 5, 1, 1);
    adiciona_arco(grafo, 4, 5, 1, 1);

    printa_matriz_arcos(grafo);

    printf("\n\n==== COLORE BFS ====\n");
    printa_cores(grafo);

    colore_grafo(grafo, BFS);

    printa_cores(grafo);


    printf("\n\n==== COLORE DFS ====\n");
    for (i = 0; i < grafo.numVertices; i++) {
        grafo.vertices[i].cor = -1;
    }
    printa_cores(grafo);

    colore_grafo(grafo, DFS);

    printa_cores(grafo);




    printf("\n\n--- FIM TESTA COLORE ---\n");
    return 0;
}

void testa_dijkstra() {

    GRAFO grafo = inicializa_grafo(6);
    int * arr_distancias;
    int i;

    adiciona_arco(grafo, 0, 1, 1, 6);
    adiciona_arco(grafo, 0, 2, 1, 1);
    adiciona_arco(grafo, 0, 4, 1, 9);
    adiciona_arco(grafo, 0, 5, 1, 6);
    adiciona_arco(grafo, 1, 3, 1, 3);
    adiciona_arco(grafo, 1, 4, 1, 5);
    adiciona_arco(grafo, 2, 3, 1, 8);
    adiciona_arco(grafo, 2, 4, 1, 7);
    adiciona_arco(grafo, 2, 5, 1, 4);
    adiciona_arco(grafo, 3, 4, 1, 4);
    adiciona_arco(grafo, 4, 5, 1, 8);

    printf("\nMatriz do grafo sendo trabalhado:\n");
    printa_matriz_arcos(grafo);

    printf("\nGerando um array com todas as distancias:\n");
    arr_distancias = dijkstra_array_distancia(grafo, 5);

    for (i = 0; i < grafo.numVertices; i++) {
        printf("%d\n", arr_distancias[i]);
    }


    printf("\nRetorno de uma distancia especifica:\n");
    printf("Distancia de %d a %d: %d\n", 5, 0, distancia(grafo, 5, 0));
    printf("Distancia de %d a %d: %d\n", 0, 5, distancia(grafo, 0, 5));
    printf("Distancia de %d a %d: %d\n", 5, 1, distancia(grafo, 5, 1));
    printf("Distancia de %d a %d: %d\n", 5, 3, distancia(grafo, 5, 3));
    printf("Distancia de %d a %d: %d\n", 0, 4, distancia(grafo, 0, 4));
    printf("Distancia de %d a %d: %d\n", 1, 2, distancia(grafo, 1, 2));



    printf("\n\n--- FIM TESTA DIJKSTRA ---\n");
    return 0;
}

