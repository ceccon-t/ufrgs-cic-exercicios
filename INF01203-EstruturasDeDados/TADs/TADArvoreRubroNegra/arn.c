#include "arn.h"
#ifndef NULL
    #define NULL (void *) 0
#endif // NULL


// FUNCOES
ARN * inicializa_arn () {
    return NULL;
}

ARN * busca_raiz(ARN * arvore) {
    if (arvore) {
        while (!eh_raiz(arvore)) {
            arvore = arvore->pai;
        }
        return arvore;
    } else {
        return NULL;
    }
}

ARN * insere_abp(ARN * raiz, int chave) {  // Apenas para servir como comparacao entre ABP normal e Rubro-Negra
    ARN * novo;

    if (!raiz) {
        novo = malloc(sizeof(ARN));
        novo->chave = chave;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->cor = VERMELHO;
        return novo;
    } else {
        if (chave < raiz->chave) {
            raiz->esq = insere_abp(raiz->esq, chave);
        } else {
            raiz->dir = insere_abp(raiz->dir, chave);
        }
        return raiz;
    }

}


ARN * insere_arn(ARN * raiz, int chave) {
    ARN * novo;

    novo = malloc(sizeof(ARN));
    novo->chave = chave;
    novo->esq = NULL;
    novo->dir = NULL;
    novo->cor = VERMELHO;
    novo->pai = NULL;

    raiz = insere_nodo_arn(raiz, novo);

    raiz = corrige_arn(novo);  // Corrige possiveis violacoes das regras de Rubro-Negra ocasionadas pela insercao do nodo

    return raiz;
}


ARN * insere_nodo_arn(ARN * raiz, ARN * novo) {

    if (!raiz) {
        return novo;
    } else {

        if (novo->chave < raiz->chave) { // Inserindo a esquerda

            raiz->esq = insere_nodo_arn(raiz->esq, novo);

            raiz->esq->pai = raiz;


        } else { // Inserindo a direita

            raiz->dir = insere_nodo_arn(raiz->dir, novo);

            raiz->dir->pai = raiz;

        }
        return raiz;
    }

}

void corrige_arn(ARN * nodo) {
    ARN * raiz;
    ARN * atual = nodo;
    ARN * tio_do_nodo;

    while (cor_nodo(atual->pai) == VERMELHO ) {  // Se for Caso 1, tudo ok e nao entra no loop
        tio_do_nodo = tio(atual);
        if (cor_nodo(tio_do_nodo) == VERMELHO) {  // Caso 2.1 dos slides
            tio_do_nodo->cor = PRETO;
            atual->pai->cor = PRETO;
            atual->pai->pai->cor = VERMELHO;
            atual = atual->pai->pai;
        } else {  // Caso 2.2
            if (quiralidade(atual->pai) == ESQUERDO) { // Rotacao (simples ou dupla) a direita
                if (quiralidade(atual) != quiralidade(atual->pai)) { // Rotacao dupla, Caso 2.2C dos slides
                    rotacao_simples_esquerda(atual->pai);           // Note que o primeiro passo desse caso recai
                    atual = atual->esq;                             // quase diretamente no caso 2.2A.
                }
                rotacao_simples_direita(atual->pai->pai);  // Rotacao simles, caso 2.2A dos slides
                atual->pai->cor = PRETO;
                atual->pai->dir->cor = VERMELHO;
                //atual = atual->pai;
                break; // Violacao foi corrigida e loop pode ser encerrado.
            } else {  // Rotacao (simples ou dupla) a esquerda
                if (quiralidade(atual) != quiralidade(atual->pai)) { // Rotacao dupla, caso 2.2D dos slides
                    rotacao_simples_direita(atual->pai);
                    atual = atual->dir;
                }
                rotacao_simples_esquerda(atual->pai->pai);  // Rotacao simples, caso 2.2B dos slides
                atual->pai->cor = PRETO;
                atual->pai->esq->cor = VERMELHO;
                break; // Violacao foi corrigida e loop pode ser encerrado.
            }
        }
    }

    raiz = busca_raiz(nodo);

    raiz->cor = PRETO;

    return raiz;

}


void printa_info_arn(ARN * nodo, int mostraNiveis, int nivel) {
    int i;
    if (nodo) {
        if (mostraNiveis) {
            for (i = 0; i < nivel; i++) {
                printf("=");
            }
        }
        printf("%d, cor: %s\n", nodo->chave, (nodo->cor == VERMELHO) ? "Vermelho" : "Preto" );
    } /* else {
        printf("NULL\n");
    } */
}

void lista_arn(ARN * raiz, int caminhamento, int mostraNiveis, int nivel) {


    switch(caminhamento) {

        case PRE_ESQUERDA:
            printa_info_arn(raiz, mostraNiveis, nivel);
            if (raiz) {
                lista_arn(raiz->esq, PRE_ESQUERDA, mostraNiveis, nivel+1);
                lista_arn(raiz->dir, PRE_ESQUERDA, mostraNiveis, nivel+1);
            }
            break;

        case CENTRAL_ESQUERDA:
            if (raiz)
                lista_arn(raiz->esq, CENTRAL_ESQUERDA, mostraNiveis, nivel+1);
            printa_info_arn(raiz, mostraNiveis, nivel);
            if (raiz)
                lista_arn(raiz->dir, CENTRAL_ESQUERDA, mostraNiveis, nivel+1);
            break;

        case POS_ESQUERDA:
            if (raiz) {
                lista_arn(raiz->esq, POS_ESQUERDA, mostraNiveis, nivel+1);
                lista_arn(raiz->dir, POS_ESQUERDA, mostraNiveis, nivel+1);
            }
            printa_info_arn(raiz, mostraNiveis, nivel);
            break;

        case PRE_DIREITA:
            printa_info_arn(raiz, mostraNiveis, nivel);
            if (raiz) {
                lista_arn(raiz->dir, PRE_DIREITA, mostraNiveis, nivel+1);
                lista_arn(raiz->esq, PRE_DIREITA, mostraNiveis, nivel+1);
            }
            break;

        case CENTRAL_DIREITA:
            if (raiz)
                lista_arn(raiz->dir, CENTRAL_DIREITA, mostraNiveis, nivel+1);
            printa_info_arn(raiz, mostraNiveis, nivel);
            if (raiz)
                lista_arn(raiz->esq, CENTRAL_DIREITA, mostraNiveis, nivel+1);
            break;

        case POS_DIREITA:
            if (raiz) {
                lista_arn(raiz->dir, POS_DIREITA, mostraNiveis, nivel+1);
                lista_arn(raiz->esq, POS_DIREITA, mostraNiveis, nivel+1);
            }
            printa_info_arn(raiz, mostraNiveis, nivel);
            break;

    }

}

ARN * destroi_arn(ARN * raiz) {

    if (raiz) {
        destroi_arn(raiz->esq);
        destroi_arn(raiz->dir);
        free(raiz);
    }

    return NULL;

}

int altura(ARN * raiz) {
    if (raiz) {
        return 1 + maior(altura(raiz->esq), altura(raiz->dir));
    } else {
        return 0;
    }
}

int cor_nodo(ARN * nodo) {
    if (nodo) {
        return nodo->cor;
    } else {
        return PRETO;
    }
}

int quiralidade(ARN * nodo) {
    if (nodo) {
        if (nodo->pai) {
            return (nodo->pai->esq == nodo) ? ESQUERDO : DIREITO ;
        } else {
            return RAIZ;
        }
    } else {
        printf("\nERRO --QUIRALIDADE-- encontrou um nodo nulo.\n");
        return ERRO_QUI;
    }
}

int eh_raiz(ARN * nodo) {
    return nodo->pai == NULL;
}


// Para Insercao
ARN * tio(ARN * nodo) {
    if (!eh_raiz(nodo) && !eh_raiz(nodo->pai)) {
        return (quiralidade(nodo->pai) == ESQUERDO) ? nodo->pai->pai->dir : nodo->pai->pai->esq ;
    } else {
        printf("\nERRO NAO ENCONTRADO TIO\n");
        return NULL;
    }
}


// Rotacoes
ARN * rotacao_simples_direita(ARN * raiz) {
    ARN * nova_raiz = raiz->esq; // Separa os nos que vao ser rotados

    nova_raiz->pai = raiz->pai;

    if (raiz->pai) {
        if (quiralidade(raiz) == ESQUERDO) {
            raiz->pai->esq = nova_raiz;
        } else {
            raiz->pai->dir = nova_raiz;
        }
    }


    // Faz a rotacao logica
    raiz->esq = nova_raiz->dir;
    if (nova_raiz->dir) nova_raiz->dir->pai = raiz;

    nova_raiz->dir = raiz;
    raiz->pai = nova_raiz;

    // Retorna a nova raiz
    raiz = nova_raiz;

    return raiz;
}

ARN * rotacao_simples_esquerda(ARN * raiz) {
    ARN * nova_raiz = raiz->dir;

    nova_raiz->pai = raiz->pai;

    if (raiz->pai) {
        if (quiralidade(raiz) == ESQUERDO) {
            raiz->pai->esq = nova_raiz;
        } else {
            raiz->pai->dir = nova_raiz;
        }
    }

    raiz->dir = nova_raiz->esq;
    if (nova_raiz->esq) nova_raiz->esq->pai = raiz;

    nova_raiz->esq = raiz;
    raiz->pai = nova_raiz;

    raiz = nova_raiz;

    return raiz;

}


//  Extras
int totalNodos(ARN * raiz) {
    if (raiz) {
        return totalNodos(raiz->esq) + totalNodos(raiz->dir) + 1;
    } else {
        return 0;
    }
}

int maior(int a, int b) {
    return (a > b) ? a : b;
}

