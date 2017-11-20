// DADOS
typedef struct s_avl {
    int chave;
    int fb;
    struct s_avl * esq;
    struct s_avl * dir;
} AVL;

enum { PRE_ESQUERDA, CENTRAL_ESQUERDA, POS_ESQUERDA, PRE_DIREITA, CENTRAL_DIREITA, POS_DIREITA };



// FUNCOES
AVL * inicializa_avl();
AVL * insere_abp(AVL * raiz, int chave);
AVL * insere_avl(AVL * raiz, int chave, int *ok);
void printa_info_avl(AVL * nodo, int mostraNiveis, int nivel);
void lista_avl(AVL * raiz, int caminhamento, int mostraNiveis, int nivel);
AVL * destroi_avl(AVL * raiz);
// --- Para AVL ---
int altura(AVL * raiz);
int fator_arvore(AVL * raiz);
// Rotacoes
AVL * rotacao_simples_direita(AVL * raiz);
AVL * rotacao_simples_esquerda(AVL * raiz);
AVL * rotacao_dupla_direita(AVL * raiz);
AVL * rotacao_dupla_esquerda(AVL * raiz);
// Balanceamentos
AVL * balancear_esquerda(AVL * raiz, int * ok);
AVL * balancear_direita(AVL * raiz, int * ok);

// Lab ABP
int totalNodos(AVL * raiz);

// AUX
int maior(int a, int b);
