/* DEQUE (FILA DUPLA) */

/* CONSTANTES */
#define INICIO 1
#define FIM 2

/* DADOS */
typedef int TipoInfo;

typedef struct s_deque {
    TipoInfo info;
    struct s_deque * ant;
    struct s_deque * prox;
} TipoDeque;

typedef struct s_dDeque {
    TipoDeque * prim;
    TipoDeque * ult;
} TipoDescDeque;


/* OPERACOES */

TipoDescDeque * inicializa();
void printaElemento(TipoInfo elemento);
void listar(TipoDescDeque * descritor);
void listarInverso(TipoDescDeque * descritor);
int insereInicio(TipoDescDeque ** descritor, TipoInfo info);
int insereFim(TipoDescDeque ** descritor, TipoInfo info);
int insere(TipoDescDeque ** descritor, TipoInfo info, int lado);
TipoInfo consulta(TipoDescDeque * descritor, int lado);
TipoInfo removerPrimeiro(TipoDescDeque ** descritor);
TipoInfo removerUltimo(TipoDescDeque ** descritor);
TipoInfo remover(TipoDeque ** descritor, int lado);
void destroi(TipoDescDeque ** descritor);

