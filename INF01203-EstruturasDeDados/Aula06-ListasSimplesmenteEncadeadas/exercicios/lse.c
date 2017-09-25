#include "lse.h"
#define NULL (void *) 0

TipoPTLseI * inicializa() {
    return NULL;
}

TipoPTLseI * insere(TipoPTLseI *lista, int num) {
    TipoPTLseI * novo, *aux;
    if (!lista) {
        novo = malloc(sizeof(TipoPTLseI));
        novo->num = num;
        novo->prox = NULL;
        lista = novo;
    } else {
        aux = lista;
        while(aux->prox) {
            aux = aux->prox;
        }
        novo = malloc(sizeof(TipoPTLseI));
        novo->num = num;
        novo->prox = NULL;
        aux->prox = novo;
    }
    return lista;
}

int contem(TipoPTLseI * lista, int num) {

    if (!lista) {
        return 0;
    } else {
        while (lista) {
            if (lista->num == num) {
                return 1;
            }
            lista = lista->prox;
        }
        return 0;
    }

}

void printaElemento(TipoPTLseI * elemento) {
    printf("\nElemento: %d\n", elemento->num);
}

void listar(TipoPTLseI * lista) {
    if (!lista) {
        printf("\nLISTA VAZIA.\n");
    } else {
        printf("\nLISTANDO:\n");
        while (lista) {
            printaElemento(lista);
            lista = lista->prox;
        }
        printf("\nFIM LISTA\n");
    }
}

TipoPTLseI * destroi(TipoPTLseI * lista) {
    TipoPTLseI *aux;
    if (!lista) {
        return lista;
    } else {
        while(lista) {
            aux = lista->prox;
            free(lista);
            lista = aux;
        }
        return NULL;
    }
}

// Ex 1 Crie uma função que recebe um ponteiro para uma lista encadeada e retorna o número de elementos que ela possui.
int numElementos(TipoPTLseI * lista) {
    int cont = 0;
    while (lista) {
        cont++;
        lista = lista->prox;
    }
    return cont;
}

// Ex 2 Crie uma função que recebe um ponteiro para uma lista encadeada de números inteiros e retorna o maior valor contido na lista.
int maiorNum(TipoPTLseI * lista) {
    int maior;
    if (!lista) {
        maior = -1;
    } else {
        maior = lista->num;
        while(lista) {
            if (lista->num > maior) {
                maior = lista->num;
            }
            lista = lista->prox;
        }
    }

    return maior;
}

// Ex 3 Faça uma função que percorre uma lista encadeada e remove os elementos repetidos.
TipoPTLseI * removeRepetidos(TipoPTLseI *lista) {
    TipoPTLseI * presentes, *aux, *ant;

    if (lista) {
        presentes = inicializa();
        aux = lista;

        while(aux) {
            if (contem(presentes, aux->num)) {
                ant->prox = aux->prox;
                free(aux);
                aux = ant->prox;
            } else {
                presentes = insere(presentes, aux->num);
                ant = aux;
                aux = aux->prox;
            }
        }

    }
    destroi(presentes);

    return lista;

}

// Ex 4 Faça uma função que percorre uma lista encadeada de números inteiros e remove os elementos ímpares.
TipoPTLseI * removeImpares(TipoPTLseI *lista) {
    TipoPTLseI *aux, *ant;

    if (lista) {
        while (lista && lista->num % 2) { // Remove todos os impares no comeco da lista primeiro para retornar ponteiro correto como inicio da lista
            aux = lista->prox;
            free(lista);
            lista = aux;
        }

        aux = lista;

        while(aux) {
            if(aux->num % 2) {
                ant->prox = aux->prox;
                free(aux);
                aux = ant->prox;
            } else {
                ant = aux;
                aux = aux->prox;
            }
        }

    }

    return lista;
}

// Ex 5 Faça uma função que recebe uma lista encadeada de números inteiros e devolve duas listas, uma contendo os valores pares e outra contendo os valores ímpares.
void separaParesImpares(TipoPTLseI * lista, TipoPTLseI ** pares, TipoPTLseI ** impares) {
    TipoPTLseI *t_pares, *t_impares;

    t_pares = inicializa();
    t_impares = inicializa();

    while (lista) {
            //printf("\nElemento da lista: %d\n", lista->num);

        if ((lista->num % 2) != 0) {
            t_impares = insere(t_impares, lista->num);
            //listar(t_impares);
        } else {
            t_pares = insere(t_pares, lista->num);
            //listar(t_pares);
        }

        lista = lista->prox;
    }

    *pares = t_pares;
    *impares = t_impares;

}

//Ex 6 Faça uma função que recebe duas listas encadeadas e retorna 1 caso elas sejam iguais e 0 caso contrário.
int iguais(TipoPTLseI *lista1, TipoPTLseI *lista2) {
    while (lista1) {
        if (!lista2 || (lista1->num != lista2->num)) {
            return 0;
        }
        lista1 = lista1->prox;
        lista2 = lista2->prox;
    }

    if (lista2 == NULL) { // Lista 2 eh maior que lista 1
        return 1;
    } else {
        return 0;
    }
}

// Ex 7 Faça uma função que recebe um ponteiro para uma lista e dois valores. A função deve substituir todas as ocorrência do primeiro valor pelo segundo valor.
void substituiValores(TipoPTLseI *lista, int antigo, int novo) {
    while (lista) {
        if (lista->num == antigo) {
            lista->num = novo;
        }
        lista = lista->prox;
    }
}

//Ex 8) Faça uma função para inverter os elementos de uma lista encadeada sem usar arrays ou outras estruturas auxiliares,
//      apenas ponteiros ( questão usada em entrevista de emprego em empresas como o Google ).
TipoPTLseI * inverte(TipoPTLseI *lista) {
    TipoPTLseI *ant, *seguinte;

    if (lista && lista->prox) { // Se a lista esta vazia ou nao ha proximo (lista de 1 elemento), nao ha o que fazer
        ant = lista;
        lista = lista->prox;
        ant->prox = NULL; // Primeiro elemento se torna o ultimo
        while (lista) {
            seguinte = lista->prox;
            lista->prox = ant; // Passo que inverte a ordem de associacao
            ant = lista;
            lista = seguinte;
        }
        lista = ant;
    }

    return lista;
}






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

