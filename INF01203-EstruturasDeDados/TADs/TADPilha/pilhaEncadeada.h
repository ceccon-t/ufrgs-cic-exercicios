typedef int TipoInfo;

typedef struct TPtPilha {
    TipoInfo dado;
    struct TPtPilha *elo;
} TipoPilha;

TipoPilha * inicializa();
void printaElemento(TipoInfo dado);
void printaPilha(TipoPilha * pilha);
int vazia(TipoPilha * pilha);
TipoPilha * push(TipoPilha * pilha, TipoInfo dado);
int pop(TipoPilha ** pilha, TipoInfo * dado);
TipoInfo consulta(TipoPilha * pilha);
TipoPilha * destroi(TipoPilha * pilha);
