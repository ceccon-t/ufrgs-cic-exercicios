// DADOS
typedef struct s_abp {
    int chave;
    struct s_abp * esq;
    struct s_abp * dir;
} ABP;

enum { PRE_ESQUERDA, CENTRAL_ESQUERDA, POS_ESQUERDA, PRE_DIREITA, CENTRAL_DIREITA, POS_DIREITA };



// FUNCOES
ABP * inicializa_abp();
ABP * insere_abp(ABP * raiz, int chave);
void printa_info_abp(ABP * nodo, int mostraNiveis, int nivel);
void lista_abp(ABP * raiz, int caminhamento, int mostraNiveis, int nivel);
ABP * destroi_abp(ABP * raiz);

// Lab
int totalNodos(ABP * raiz);

// Revisao P2
int total_folhas(ABP * raiz);
