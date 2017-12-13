#ifndef TipoDFila
    #include "filaEncadeada.h"
#endif // TipoDFila
#ifndef INT_MAX
    #include <limits.h>
#endif // INT_MAX

#include "grafo.h"

GRAFO inicializa_grafo(int numVertices) {
    GRAFO novo_grafo;
    int i;

    novo_grafo.numVertices = numVertices;

    novo_grafo.arcos = malloc(sizeof(int) * (numVertices * numVertices)); // Matriz
    for (i = 0; i < (numVertices * numVertices); i++) {
        novo_grafo.arcos[i] = 0;
    }

    novo_grafo.vertices = malloc(sizeof(VERTICE) * numVertices);

    for (i = 0; i < numVertices; i++) {
        novo_grafo.vertices[i].chave = i;
        novo_grafo.vertices[i].info = 0;
        novo_grafo.vertices[i].cor = -1;
    }

    return novo_grafo;
}

void printa_matriz_arcos(GRAFO grafo) {
    int n = grafo.numVertices, i, j;

    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            printf("%d ", grafo.arcos[(i * n) + j]);
        }
        printf("\n");
    }
}

int adiciona_arco(GRAFO grafo, int origem, int destino, int reciproco, int valor) {
    int n = grafo.numVertices;

    if (origem >= n || destino >= n) return -1;

    grafo.arcos[ (origem * n) + destino ] = valor;
    if (reciproco) {
        grafo.arcos[ (destino * n) + origem ] = valor;
    }

    return 1;
}

int eh_adjacente(GRAFO grafo, int vertice1, int vertice2) {
    return grafo.arcos[ (vertice1 * grafo.numVertices) + vertice2 ] != 0;
}

int valor_arco(GRAFO grafo, int origem, int destino) {
    return grafo.arcos[ (origem * grafo.numVertices) + destino ];
}

void depth_first_search(GRAFO grafo, int inicio) {
    int n = grafo.numVertices, i;
    int * visitados = malloc(sizeof(int) * n);

    for (i = 0; i < n; i++) {
        visitados[i] = 0;
    }

    dfs_interno(grafo, inicio, visitados);


}

void dfs_interno(GRAFO grafo, int atual, int * visitados) {
    int i;

    printf("%d\n", atual+1);
    visitados[atual] = 1;

    for (i = 0; i < grafo.numVertices; i++) {
        if ( eh_adjacente(grafo, atual, i) && !visitados[ i ] ) {
            visitados[i] = 1;
            dfs_interno( grafo,  i , visitados);
        }
    }
}

TipoDFila * acessiveis_dfs(GRAFO grafo, int inicio) {
    int n = grafo.numVertices, i;
    int * visitados = malloc(sizeof(int) * n);
    TipoDFila * acessiveis = inicializa();

    for (i = 0; i < n; i++) {
        visitados[i] = 0;
    }

    dfs_acessiveis_interno(grafo, inicio, visitados, &acessiveis);

    return acessiveis;
}

void dfs_acessiveis_interno(GRAFO grafo, int atual, int * visitados, TipoDFila ** acessiveis) {
    int i;

    insere(acessiveis, atual);
    visitados[atual] = 1;

    for (i = 0; i < grafo.numVertices; i++) {
        if ( eh_adjacente(grafo, atual, i) && !visitados[i] ) {
            visitados[i] = 1;
            dfs_acessiveis_interno(grafo, i, visitados, acessiveis);
        }
    }
}


void breadth_first_search(GRAFO grafo, int inicio) {
    TipoDFila * fila_vertices = inicializa();
    int n = grafo.numVertices, atual, i;
    int * visitados = malloc(sizeof(int) * n);

    for (i = 0; i < n; i++) {
        visitados[i] = 0;
    }

    insere(&fila_vertices, inicio);
    visitados[inicio] = 1;

    while (!vazia(fila_vertices)) {
        remover(&fila_vertices, &atual);
        printf("%d\n", atual+1);
        for (i = 0; i < n; i++) {
            if ( eh_adjacente(grafo, atual, i) && !visitados[i] ) {
                insere(&fila_vertices, i);
                visitados[i] = 1;
            }
        }
    }

}


TipoDFila * acessiveis_bfs(GRAFO grafo, int inicio) {
    TipoDFila * fila_visitar = inicializa();
    TipoDFila * acessiveis = inicializa();
    int n = grafo.numVertices, atual, i;

    int * visitados = malloc(sizeof(int) * n);

    for (i = 0; i < n; i++) {
        visitados[i] = 0;
    }

    insere(&fila_visitar, inicio);
    visitados[inicio] = 1;

    while (!vazia(fila_visitar)) {
        remover(&fila_visitar, &atual);
        insere(&acessiveis, atual);
        for (i = 0; i < n; i++) {
            if ( eh_adjacente(grafo, atual, i) && !visitados[i] ) {
                insere(&fila_visitar, i);
                visitados[i] = 1;
            }
        }
    }

    return acessiveis;
}

TipoDFila * fila_adjacentes(GRAFO grafo, int vertice) {
    TipoDFila * adj = inicializa();
    int inicio = vertice * grafo.numVertices;
    int fim = inicio + grafo.numVertices;
    int i;

    for (i = inicio; i < fim; i++) {
        //insere(&adj, grafo.arcos[i]);
        if (grafo.arcos[i] != 0) {
            insere(&adj, i - inicio);
        }
    }

    return adj;
}

int set_cor_vertice(GRAFO grafo, int vertice, int cor) {
    grafo.vertices[vertice].cor = cor;
    return 1;
}

int get_cor_vertice(GRAFO grafo, int vertice) {
    return grafo.vertices[vertice].cor;
}

// TODO: Para grafos direcionados, o que deve contar são as arcos que CHEGAM nele, os que SAEM, ou ambos?
int grau_vertice(GRAFO grafo, int vertice) {
    int grau = 0, i;

    for (i = 0; i < grafo.numVertices; i++) {
        // Para arcos que SAEM do vertice:
        //if ( grafo.arcos[ (vertice * grafo.numVertices) + i ] != 0 ) grau++;

        // Para arcos que CHEGAM no vertice:
        if ( grafo.arcos[ (i * grafo.numVertices) + vertice] != 0 ) grau++;
    }

    return grau;
}

int cor_em_adjacentes(GRAFO grafo, TipoDFila * vertices_adjacentes, int cor) {
    TipoFila * atual = vertices_adjacentes->prim;

    while (atual) {
        if ( get_cor_vertice(grafo, atual->dado) == cor) {
            return 1;
        }
        atual = atual->elo;
    }

    return 0;
}



int acessivel(GRAFO grafo, int origem, int destino) {
    TipoDFila * todos_acessiveis = acessiveis_bfs(grafo, origem);
    return contem(todos_acessiveis, destino);
}

void printa_cores(GRAFO grafo) {
    int i;

    printf("\n\n- Printa cores -\n");
    for(i = 0; i < grafo.numVertices; i++) {
        printf("Vertice %d, cor: %d\n", i+1, get_cor_vertice(grafo, i));
    }
}

void colore_vertice(GRAFO grafo, int vertice) {
    int cor = 1;
    TipoDFila * adjs = fila_adjacentes(grafo, vertice);

    while ( cor_em_adjacentes(grafo, adjs, cor) ) {
        cor++;
    }

    set_cor_vertice(grafo, vertice, cor);

}


void colore_grafo(GRAFO grafo, int caminho) {
    TipoDFila * vertices;

    if (caminho == DFS) {
        vertices = acessiveis_dfs(grafo, 0);
    } else if (caminho == BFS) {
        vertices = acessiveis_bfs(grafo, 0);
    } else {
        printf("\nERRO em [colore_grafos] - Caminho nao reconhecido");
        return;
    }

    TipoFila * atual = vertices->prim;


    while (atual) {
        colore_vertice(grafo, atual->dado);
        atual = atual->elo;
    }
}

void full_dijkstra(GRAFO grafo, int * antecessores, int * distancias) {
    int n = grafo.numVertices, i, vertice_inicial, atual, distancia_atual, menor_distancia, vertice_menor_dist, dist;
    int v;
    int * nuvem = malloc(sizeof(int) * n);
    TipoDFila * adjs;
    TipoFila * adj_atual;

    for (i = 0; i < n; i++) {
        nuvem[i] = 0;
        if (distancias[i] == 0) vertice_inicial = i;
    }

    atual = vertice_inicial;

    while (atual != -1) {
        nuvem[atual] = 1;
        distancia_atual = distancias[atual];
        adjs = fila_adjacentes(grafo, atual);

        // Processando distancias dos vertices adjacentes a esse
        adj_atual = adjs->prim;
        while (adj_atual) {
            v = adj_atual->dado;
            dist = distancia_atual + valor_arco(grafo, atual, v);
            if (dist < distancias[v]) {
                distancias[v] = dist;
                antecessores[v] = atual;
            }
            adj_atual = adj_atual->elo;
        }


        // Escolhendo proximo vertice
        vertice_menor_dist = -1;
        menor_distancia = INT_MAX;
        for (i = 0; i < n; i++) {
            if (!nuvem[i] && distancias[i] < menor_distancia) {
                menor_distancia = distancias[i];
                vertice_menor_dist = i;
            }
        }

        atual = vertice_menor_dist;

    }

}


int * dijkstra_array_distancia(GRAFO grafo, int vertice_inicial) {
    int n = grafo.numVertices, i;
    int * distancias = malloc(sizeof(int) * n);
    int * antecessores = malloc(sizeof(int) * n);

    for (i = 0; i < n; i++) {
        distancias[i] = INT_MAX;
    }

    distancias[vertice_inicial] = 0;

    for (i = 0; i < n; i++) {
        antecessores[i] = -1;
    }

    full_dijkstra(grafo, antecessores, distancias);


    return distancias;
}

int distancia(GRAFO grafo, int origem, int destino) {
    int n = grafo.numVertices, i;
    int * distancias = malloc(sizeof(int) * n);
    int * antecessores = malloc(sizeof(int) * n);

    for (i = 0; i < n; i++) {
        distancias[i] = INT_MAX;
    }

    distancias[origem] = 0;

    for (i = 0; i < n; i++) {
        antecessores[i] = -1;
    }

    full_dijkstra(grafo, antecessores, distancias);

    return distancias[destino];
}




