/* PRODUTOS - Lista simplesmente encadeada */

/* TIPOS DE DADOS */
typedef struct s_Prod {
    int codigo;
    char nome[20];
    float preco;
} TipoProduto;

typedef struct s_PtProd {
    TipoProduto produto;
    struct s_PtProd * prox;
} TipoPtProduto;


/* OPERACOES */

TipoPtProduto * inicializa();

TipoProduto geraProduto();

TipoPtProduto * insereProduto(TipoPtProduto *lista, TipoProduto prod);

void printaElemento(TipoProduto elemento);

void listar(TipoPtProduto * lista);

TipoPtProduto * destroi(TipoPtProduto * lista);

