/* LISTA DUPLAMENTE ENCADEADA */

/* DADOS */
typedef struct TipoInfoNo {
    int codigo;
    char nome[20];
    float preco;
} InfoNo;

typedef struct TipoPtNo {
    InfoNo info;
    struct TipoPtNo * ant;
    struct TipoPtNo * prox;
} PtNo;


/* OPERACOES */

PtNo * inicializa();
void printaElemento(InfoNo elemento);
void listar(PtNo * lista);
void listarInverso(PtNo * lista);
InfoNo leProduto();
PtNo * insereInicio(PtNo * lista, InfoNo info);
PtNo * insereFim(PtNo * lista, InfoNo info);
PtNo * insereAntesDe(PtNo * lista, InfoNo info, int codigo);
PtNo * insereDepoisDe(PtNo * lista, InfoNo info, int codigo);
PtNo * removerPrimeiro(PtNo * lista);
PtNo * removerUltimo(PtNo * lista);
PtNo * removerPosicao(PtNo * lista, int pos);
PtNo * removerCodigo(PtNo * lista, int codigo);
PtNo * trocarOrdem(PtNo * lista, int codigo1, int codigo2);
PtNo * destroi(PtNo * lista);

// Para QuestionarioRevisaoP1
InfoNo encontraMeio(PtNo * lista);

/*
inicializar
listar
listar inverso
inserir antes/depois de determinado no
remover o primeiro, o ultimo e o k-esimo no
trocar ordem de 2 nos
*/
