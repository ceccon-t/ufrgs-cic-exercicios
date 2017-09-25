/* LISTA SIMPLESMENTE ENCADEADA - INTEIROS */

// DEFINICAO DE DADOS

typedef struct s_lsei {
    int num;
    struct s_lsei * prox;
} TipoPTLseI;

// OPERACOES

TipoPTLseI * inicializa();

TipoPTLseI * insere(TipoPTLseI * lista, int num);

int contem(TipoPTLseI * lista, int num);

void printaElemento(TipoPTLseI * elemento);

void listar(TipoPTLseI * lista);

TipoPTLseI * destroi(TipoPTLseI * lista);

// Ex 1 Crie uma função que recebe um ponteiro para uma lista encadeada e retorna o número de elementos que ela possui.
int numElementos(TipoPTLseI * lista);

// Ex 2 Crie uma função que recebe um ponteiro para uma lista encadeada de números inteiros e retorna o maior valor contido na lista.
int maiorNum(TipoPTLseI * lista);

// Ex 3 Faça uma função que percorre uma lista encadeada e remove os elementos repetidos.
TipoPTLseI * removeRepetidos(TipoPTLseI *lista);

// Ex 4 Faça uma função que percorre uma lista encadeada de números inteiros e remove os elementos ímpares.
TipoPTLseI * removeImpares(TipoPTLseI *lista);

// Ex 5 Faça uma função que recebe uma lista encadeada de números inteiros e devolve duas listas, uma contendo os valores pares e outra contendo os valores ímpares.
void separaParesImpares(TipoPTLseI * lista, TipoPTLseI ** pares, TipoPTLseI ** impares);

// Ex 6 Faça uma função que recebe duas listas encadeadas e retorna 1 caso elas sejam iguais e 0 caso contrário.
int iguais(TipoPTLseI *lista1, TipoPTLseI *lista2);

// Ex 7 Faça uma função que recebe um ponteiro para uma lista e dois valores. A função deve substituir todas as ocorrência do primeiro valor pelo segundo valor.
void substituiValores(TipoPTLseI *lista, int antigo, int novo);

//Ex 8) Faça uma função para inverter os elementos de uma lista encadeada sem usar arrays ou outras estruturas auxiliares,
//      apenas ponteiros ( questão usada em entrevista de emprego em empresas como o Google ).
TipoPTLseI * inverte(TipoPTLseI *lista);


/*
Exercícios Listas Simplesmente Encadeadas
1) Crie uma função que recebe um ponteiro para uma lista encadeada e retorna o
número de elementos que ela possui.
2) Crie uma função que recebe um ponteiro para uma lista encadeada de números
inteiros e retorna o maior valor contido na lista.
3) Faça uma função que percorre uma lista encadeada e remove os elementos repetidos.
4) Faça uma função que percorre uma lista encadeada de números inteiros e remove os
elementos ímpares.
5) Faça uma função que recebe uma lista encadeada de números inteiros e devolve duas
listas, uma contendo os valores pares e outra contendo os valores ímpares.
6) Faça uma função que recebe duas listas encadeadas e retorna 1 caso elas sejam iguais
e 0 caso contrário.
7) Faça uma função que recebe um ponteiro para uma lista e dois valores. A função deve
substituir todas as ocorrência do primeiro valor pelo segundo valor.
8) Faça uma função para inverter os elementos de uma lista encadeada sem usar arrays
ou outras estruturas auxiliares, apenas ponteiros ( questão usada em entrevista de emprego
em empresas como o Google ).
*/
