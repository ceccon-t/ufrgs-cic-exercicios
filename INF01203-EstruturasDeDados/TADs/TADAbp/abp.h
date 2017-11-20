// DADOS
typedef struct s_abp {
    int chave;
    char info;
    struct s_abp * esq;
    struct s_abp * dir;
} ABP;

enum { PRE_ESQUERDA, CENTRAL_ESQUERDA, POS_ESQUERDA, PRE_DIREITA, CENTRAL_DIREITA, POS_DIREITA};



// FUNCOES
ABP * inicializa_abp();
ABP * insere_abp(ABP * raiz, int chave, char info);
void lista_abp(ABP * raiz, int caminhamento);
ABP * destroi_abp(ABP * raiz);
