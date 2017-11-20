/* FILMES - Lista simplesmente encadeada */
#include<string.h>

#define NULL (void *) 0


/* TIPOS DE DADOS */
typedef struct s_InfoNo {
    char titulo[20];
    char distr[20];
    char diretor[20];
} TipoInfoNo;

typedef struct s_PtNo {
    TipoInfoNo info;
    struct s_PtNo * prox;
} TipoPtNo;


/* OPERACOES */

TipoPtNo * inicializa();

TipoPtNo * insereInicio(TipoPtNo *lista);

TipoPtNo * insereFim(TipoPtNo *lista);

TipoPtNo * remover(TipoPtNo *lista, char titulo[]);

TipoPtNo * consulta(TipoPtNo *lista, char titulo[]);

void printaElemento(TipoInfoNo elemento);

void listar(TipoPtNo * lista);

TipoPtNo * destroi(TipoPtNo * lista);


/*
inicializa(): cria uma lista vazia
insere(): insere um elemento em uma posição da lista
remove(): remove um elemento na lista
consulta(): consulta um elemento da lista
lista(): exibe todos os elementos da lista
destroi(): destrói a lista
*/
