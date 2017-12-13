/*   ===== TAD FILA ENCADEADA =====    */

// DEFINICAO DE DADOS

typedef int TipoInfo;

typedef struct s_Fila {
    TipoInfo dado;
    struct s_Fila * elo;
} TipoFila;

typedef struct s_Descritor {
    TipoFila * prim;
    TipoFila * ult;
} TipoDFila;

enum { CRESCENTE, DECRESCENTE };


// OPERACOES

TipoDFila * inicializa();
void printaElemento(TipoInfo dado);
void printaFila(TipoDFila * descritor);
int vazia(TipoDFila * descritor);
TipoInfo consulta(TipoDFila * descritor);
int contem(TipoDFila * descritor, TipoInfo desejado);
int insere(TipoDFila ** descritor, TipoInfo dado);
int insereComPrioridade(TipoDFila ** descritor, TipoInfo dado, int ordem);
int remover(TipoDFila ** descritor, TipoInfo * dado);
void destroi(TipoDFila ** descritor);
