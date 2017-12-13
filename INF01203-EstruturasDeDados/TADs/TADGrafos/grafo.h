

typedef int INFO_GRAFO;

typedef struct s_vert {
    int chave;
    INFO_GRAFO info;
    int cor;
} VERTICE;

typedef struct s_grafo {
    int numVertices;
    int * arcos;  // Matriz de adjacencia valorada
    VERTICE * vertices;
} GRAFO;

enum { DFS, BFS};


GRAFO inicializa_grafo(int numVertices);
void printa_matriz_arcos(GRAFO grafo);
int adiciona_arco(GRAFO grafo, int origem, int destino, int reciproco, int valor);
int eh_adjacente(GRAFO grafo, int vertice1, int vertice2);
int valor_arco(GRAFO grafo, int origem, int destino);
void depth_first_search(GRAFO grafo, int inicio);
void dfs_interno(GRAFO grafo, int atual, int * visitados);
TipoDFila * acessiveis_dfs(GRAFO grafo, int inicio);
void dfs_acessiveis_interno(GRAFO grafo, int atual, int * visitados, TipoDFila ** acessiveis);
void breadth_first_search(GRAFO grafo, int inicio);
TipoDFila * acessiveis_bfs(GRAFO grafo, int inicio);
TipoDFila * fila_adjacentes(GRAFO grafo, int vertice);
int set_cor_vertice(GRAFO grafo, int vertice, int cor);
int get_cor_vertice(GRAFO grafo, int vertice);
int grau_vertice(GRAFO grafo, int vertice); // TODO: Para grafos direcionados, o que deve contar são as arcos que CHEGAM nele, os que SAEM, ou ambos?
int cor_em_adjacentes(GRAFO grafo, TipoDFila * vertices_adjacentes, int cor);
int acessivel(GRAFO grafo, int origem, int destino);
void printa_cores(GRAFO grafo);
void colore_vertice(GRAFO grafo, int vertice);
void colore_grafo(GRAFO grafo, int caminho);
void full_dijkstra(GRAFO grafo, int * antecessores, int * distancias);
int * dijkstra_array_distancia(GRAFO grafo, int vertice_inicial);
int distancia(GRAFO grafo, int origem, int destino);
