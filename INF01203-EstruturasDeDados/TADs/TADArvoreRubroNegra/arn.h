// DADOS
typedef struct s_arn {
    int chave;
    struct s_arn * esq;
    struct s_arn * dir;
    struct s_arn * pai;
    int cor;
} ARN;

enum { PRE_ESQUERDA, CENTRAL_ESQUERDA, POS_ESQUERDA, PRE_DIREITA, CENTRAL_DIREITA, POS_DIREITA };
enum { ERRO_COR, VERMELHO, PRETO };
enum { ERRO_QUI, RAIZ, ESQUERDO, DIREITO };



// FUNCOES
ARN * inicializa_arn();
ARN * insere_abp(ARN * raiz, int chave);
ARN * insere_arn(ARN * raiz, int chave);
ARN * insere_nodo_arn(ARN * raiz, ARN * novo);
void printa_info_arn(ARN * nodo, int mostraNiveis, int nivel);
void lista_arn(ARN * raiz, int caminhamento, int mostraNiveis, int nivel);
ARN * destroi_arn(ARN * raiz);
int altura(ARN * raiz);
int cor_nodo(ARN * nodo);
int quiralidade(ARN * nodo);
int eh_raiz(ARN * nodo);

// Para Insercao
ARN * tio(ARN * nodo);
// Rotacoes
ARN * rotacao_simples_direita(ARN * raiz);
ARN * rotacao_simples_esquerda(ARN * raiz);

// Extras
int totalNodos(ARN * raiz);
int maior(int a, int b);
