/* OPERACOES */
#include "produto.h"

#ifndef NULL
    #define NULL (void *) 0
#endif // NULL

PtNo * inicializa() {
    return NULL;
}

void printaElemento(InfoNo elemento) {
    printf("--\nELEMENTO: \n-\n");
    printf("Codigo: %d\n", elemento.codigo);
    printf("Nome: %s\n", elemento.nome);
    printf("Preco: %.2f\n", elemento.preco);
    printf("-\n--");
}


void listar(PtNo * lista) {

    printf("\n--- LISTAR: ---\n");

    if (lista) {
        while(lista) {
            printaElemento(lista->info);
            lista = lista->prox;
        }
    } else {
        printf("\nLista vazia.\n");
    }

    printf("\n---------------\n");

}

void listarInverso(PtNo * lista) {

    printf("\n--- LISTAR: ---\n");

    if (lista) {
        while(lista->prox) {
            lista = lista->prox;
        }
        while(lista) {
            printaElemento(lista->info);
            lista = lista->ant;
        }
    } else {
        printf("\nLista vazia.\n");
    }

    printf("\n---------------\n");

}

InfoNo leProduto() {
    InfoNo produto;

    printf("Codigo: ");
    scanf("%d", &produto.codigo);
    printf("Nome: ");
    scanf(" %s", produto.nome);
    printf("Preco: ");
    scanf("%f", &produto.preco);

    return produto;

}

PtNo * insereInicio(PtNo * lista, InfoNo info) {
    PtNo * novo = malloc(sizeof(PtNo));

    novo->info = info;
    novo->ant = NULL;
    novo->prox = lista;
    if (lista) {
        lista->ant = novo;
    }
    return novo;
}

PtNo * insereFim(PtNo * lista, InfoNo info) {
    PtNo * novo = malloc(sizeof(PtNo)), *aux;

    novo->info = info;
    novo->prox = NULL;

    if (lista) {
        aux = lista;
        while(aux->prox) {
            aux = aux->prox;
        }
        aux->prox = novo;
        novo->ant = aux;
    } else {
        novo->ant = NULL;
        lista = novo;
    }

    return lista;
}

PtNo * insereAntesDe(PtNo * lista, InfoNo info, int codigo) {
    PtNo * novo = malloc(sizeof(PtNo)), * aux;

    novo->info = info;

    if (!lista || (lista->info.codigo == codigo)) { // Novo vai ser o primeiro da lista
        novo->ant = NULL;
        novo->prox = lista;
        if (lista) {
            lista->ant = novo;
        }
        lista = novo;
    } else {
        aux = lista;

        while (aux->prox && (aux->info.codigo != codigo)) {
            aux = aux->prox;
        }

        if(aux->info.codigo == codigo) { // Codigo foi encontrado
            novo->ant = aux->ant;
            novo->prox = aux;
            novo->ant->prox = novo;
            aux->ant = novo;
        } else { // Codigo nao foi encontrado, inserir no final da lista
            novo->prox = NULL;
            novo->ant = aux;
            aux->prox = novo;
        }

    }

    return lista;
}

PtNo * insereDepoisDe(PtNo * lista, InfoNo info, int codigo) {
    PtNo * novo = malloc(sizeof(PtNo)), * aux;

    novo->info = info;

    if (!lista) {
        novo->ant = NULL;
        novo->prox = NULL;
        lista = novo;
    } else {
        aux = lista;
        while(aux->prox && (aux->info.codigo != codigo)) {
            aux = aux->prox;
        }
        novo->ant = aux;
        novo->prox = aux->prox;
        aux->prox = novo;
        if (novo->prox) { // Caso nao esteja sendo inserido no final da lista
            novo->prox->ant = novo;
        }
    }

    return lista;
}

PtNo * removerPrimeiro(PtNo * lista) {
    PtNo * removido;

    if (lista) {
        removido = lista;
        lista = lista->prox;
        lista->ant = NULL;
        free(removido);
    }

    return lista;
}

PtNo * removerUltimo(PtNo * lista) {
    PtNo * removido;

    if(lista) {
        removido = lista;
        while(removido->prox) {
            removido = removido->prox;
        }
        if (removido->ant) { // Ultimo nao eh o primeiro
            removido->ant->prox = NULL;
            free(removido);
        } else { // Ultimo eh o primeiro
            lista = NULL;
            free(removido);
        }
    }

    return lista;
}

PtNo * removerPosicao(PtNo * lista, int pos) {
    return NULL;
}

PtNo * removerCodigo(PtNo * lista, int codigo) {
    return NULL;
}

PtNo * trocarOrdem(PtNo * lista, int codigo1, int codigo2) {
    return NULL;
}

PtNo * destroi(PtNo * lista) {
    PtNo * aux;

    while (lista) {
        aux = lista;
        lista = lista->prox;
        free(aux);
    }

    return NULL;
}


// Para QuestionarioRevisaoP1
InfoNo encontraMeio(PtNo * lista) {
    PtNo * aux = lista;
    //if (lista->prox == NULL || lista->prox->prox == NULL) { // Casos triviais
    //    return lista->info;
    //} else {
    if (lista->prox != NULL && lista->prox->prox != NULL) { // Pula os casos triviais em que len(lista) < 3

        while (aux->prox != NULL) { // Nao especificado se deve usar lista circular ou nao, partindo do pressuposto que nao
            aux = aux->prox; // Leva um dos ponteiros ate o final da lista, desnecessario no caso de lista circular
        }

        while ( (lista != aux) && (lista->prox != aux) ) {
            lista = lista->prox;
            aux = aux->ant;
        }

        //return lista->info;
    }

    return lista->info;
}


/*
inicializar
listar
listar inverso
inserir antes/depois de determinado no
remover o primeiro, o ultimo e o k-esimo no
trocar ordem de 2 nos
*/

