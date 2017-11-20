/* TAD LISTA LINEAR */

/* TIPO DE DADO */
typedef struct T_Produto {
    int cod;
    char nome[40];
    float preco;
} TProduto;

int inicio,fim;


/* OPERACOES */

/* Inicializa uma lista */
void inicializa(TProduto t[], int *inicio, int *fim);

/* Insere elemento em uma determinada posicao de uma lista */
void insere(TProduto t[], int *inicio, int *fim, int posicao);

/* Remove o elemento em uma determinada posicao de uma lista */
int remover(TProduto t[], int *inicio, int *fim, int posicao);

/* Consula o elemento em uma determinada posicao de uma lista */
int consulta(TProduto t[], int inicio, int fim, int posicao);

/* Destroi */
void destroi(int *inicio, int *fim);
