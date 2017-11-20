#include "avl.h"
#ifndef NULL
    #define NULL (void *) 0
#endif // NULL


// FUNCOES
AVL * inicializa_avl () {
    return NULL;
}

AVL * insere_abp(AVL * raiz, int chave) {  // Apenas para servir como comparacao para a AVL
    AVL * novo;

    if (!raiz) {
        novo = malloc(sizeof(AVL));
        novo->chave = chave;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->fb = 0;
        return novo;
    } else {
        if (chave < raiz->chave) {
            raiz->esq = insere_abp(raiz->esq, chave);
        } else {
            raiz->dir = insere_abp(raiz->dir, chave);
        }
        raiz->fb = altura(raiz->esq) - altura(raiz->dir);
        return raiz;
    }

}

AVL * insere_avl(AVL * raiz, int chave, int *ok) {
    AVL * novo;

    if (!raiz) {
        novo = malloc(sizeof(AVL));
        novo->chave = chave;
        novo->esq = NULL;
        novo->dir = NULL;
        novo->fb = 0;
        *ok = 1;
        return novo;
    } else {

        if (chave < raiz->chave) { // Inserindo a esquerda

            raiz->esq = insere_avl(raiz->esq, chave, ok);
            if (*ok) {
                switch(raiz->fb) {
                    case -1:
                        raiz->fb = 0;
                        *ok = 0;
                        break;
                    case 0:
                        raiz->fb = 1;
                        break;
                    case 1: // fb iria para +2, necessario balancear
                        raiz = balancear_esquerda(raiz, ok);
                        break;
                }
            }

        } else { // Inserindo a direita

            raiz->dir = insere_avl(raiz->dir, chave, ok);
            if (*ok) {
                switch(raiz->fb) {
                    case 1:
                        raiz->fb = 0;
                        *ok = 0;
                        break;
                    case 0:
                        raiz->fb = -1;
                        break;
                    case -1: // fb iria para -2, necessario balancear
                        raiz = balancear_direita(raiz, ok);
                        break;
                }
            }

        }
        //raiz->fb = altura(raiz->esq) - altura(raiz->dir);
        return raiz;
    }

}


void printa_info_avl(AVL * nodo, int mostraNiveis, int nivel) {
    int i;
    if (nodo) {
        if (mostraNiveis) {
            for (i = 0; i < nivel; i++) {
                printf("=");
            }
        }
        printf("%d, fator: %d\n", nodo->chave, nodo->fb);
    } /* else {
        printf("NULL\n");
    } */
}

void lista_avl(AVL * raiz, int caminhamento, int mostraNiveis, int nivel) {


    switch(caminhamento) {

        case PRE_ESQUERDA:
            printa_info_avl(raiz, mostraNiveis, nivel);
            if (raiz) {
                lista_avl(raiz->esq, PRE_ESQUERDA, mostraNiveis, nivel+1);
                lista_avl(raiz->dir, PRE_ESQUERDA, mostraNiveis, nivel+1);
            }
            break;

        case CENTRAL_ESQUERDA:
            if (raiz)
                lista_avl(raiz->esq, CENTRAL_ESQUERDA, mostraNiveis, nivel+1);
            printa_info_avl(raiz, mostraNiveis, nivel);
            if (raiz)
                lista_avl(raiz->dir, CENTRAL_ESQUERDA, mostraNiveis, nivel+1);
            break;

        case POS_ESQUERDA:
            if (raiz) {
                lista_avl(raiz->esq, POS_ESQUERDA, mostraNiveis, nivel+1);
                lista_avl(raiz->dir, POS_ESQUERDA, mostraNiveis, nivel+1);
            }
            printa_info_avl(raiz, mostraNiveis, nivel);
            break;

        case PRE_DIREITA:
            printa_info_avl(raiz, mostraNiveis, nivel);
            if (raiz) {
                lista_avl(raiz->dir, PRE_DIREITA, mostraNiveis, nivel+1);
                lista_avl(raiz->esq, PRE_DIREITA, mostraNiveis, nivel+1);
            }
            break;

        case CENTRAL_DIREITA:
            if (raiz)
                lista_avl(raiz->dir, CENTRAL_DIREITA, mostraNiveis, nivel+1);
            printa_info_avl(raiz, mostraNiveis, nivel);
            if (raiz)
                lista_avl(raiz->esq, CENTRAL_DIREITA, mostraNiveis, nivel+1);
            break;

        case POS_DIREITA:
            if (raiz) {
                lista_avl(raiz->dir, POS_DIREITA, mostraNiveis, nivel+1);
                lista_avl(raiz->esq, POS_DIREITA, mostraNiveis, nivel+1);
            }
            printa_info_avl(raiz, mostraNiveis, nivel);
            break;

    }

}

AVL * destroi_avl(AVL * raiz) {

    if (raiz) {
        destroi_avl(raiz->esq);
        destroi_avl(raiz->dir);
        free(raiz);
    }

    return NULL;

}

// --- Para AVL ---
int altura(AVL * raiz) {
    if (raiz) {
        return 1 + maior(altura(raiz->esq), altura(raiz->dir));
    } else {
        return 0;
    }
}

int fator_arvore(AVL * raiz) {
    if (raiz) {
        return maior(raiz->fb, maior( fator_arvore(raiz->esq) , fator_arvore(raiz->dir) ));
    } else {
        return 0;
    }
}

// Rotacoes
AVL * rotacao_simples_direita(AVL * raiz) {
    AVL * nova_raiz = raiz->esq; // Separa os nos que vao ser rotados

    // Faz a rotacao logica
    raiz->esq = nova_raiz->dir;
    nova_raiz->dir = raiz;

    // Atualiza fatores de balanceamento
    // TODO: Nos slides simplesmente seta raiz(antiga)->fb como 0, verificar porque funciona e talvez mudar aqui. DONE
    nova_raiz->fb = altura(nova_raiz->esq) - altura(nova_raiz->dir);
    raiz->fb = altura(raiz->esq) - altura(raiz->dir);
    //raiz->fb = 0;

    // Retorna a nova raiz
    raiz = nova_raiz;

    return raiz;
}

AVL * rotacao_simples_esquerda(AVL * raiz) {
    AVL * nova_raiz = raiz->dir;

    raiz->dir = nova_raiz->esq;
    nova_raiz->esq = raiz;

    // Atualiza fatores de balanceamento
    // TODO: Nos slides simplesmente seta raiz(antiga)->fb como 0, verificar porque funciona e talvez mudar aqui. DONE
    //nova_raiz->fb = altura(nova_raiz->esq) - altura(nova_raiz->dir);
    //raiz->fb = altura(raiz->esq) - altura(raiz->dir);
    raiz->fb = 0;

    raiz = nova_raiz;

    return raiz;

}

AVL * rotacao_dupla_direita(AVL * raiz) {
    // Uma rotacao dupla pode ser vista como a composicao de duas rotacoes simples consecutivas
    // sendo a primeira no sentido inverso ao da dupla e a segunda no mesmo sentido da dupla
    // Especificamente: Rotacao Dupla A Direita == Rot. Simp. A Esquerda (do filho esquerdo) + Rot. Simp. A Direita (da raiz)

    // Adaptando a logica dos slides
    int fb_nova_raiz = raiz->esq->dir->fb;
    //

    raiz->esq = rotacao_simples_esquerda(raiz->esq);
    raiz = rotacao_simples_direita(raiz);

    // Adaptando a logica dos slides
    if (fb_nova_raiz == 1) raiz->dir->fb = -1;
    else raiz->dir->fb = 0;

    if (fb_nova_raiz == -1) raiz->esq->fb = 1;
    else raiz->esq->fb = 0;
    //

    return raiz;
}

AVL * rotacao_dupla_esquerda(AVL * raiz) {
    // Uma rotacao dupla pode ser vista como a composicao de duas rotacoes simples consecutivas
    // sendo a primeira no sentido inverso ao da dupla e a segunda no mesmo sentido da dupla
    // Especificamente: Rotacao Dupla A Esquerda == Rot. Simp. A Direita (do filho direito) + Rot. Simp. A Esquerda (da raiz)

    // Adaptando a logica dos slides
    int fb_nova_raiz = raiz->dir->esq->fb;
    //

    raiz->dir = rotacao_simples_direita(raiz->dir);
    raiz = rotacao_simples_esquerda(raiz);

    // Adaptando a logica dos slides
    if (fb_nova_raiz == -1) raiz->esq->fb = 1;
    else raiz->esq->fb = 0;

    if (fb_nova_raiz == 1) raiz->dir->fb = -1;
    else raiz->dir->fb = 0;
    //

    return raiz;
}

// Balanceamentos
AVL * balancear_esquerda(AVL * raiz, int * ok) { // "Caso1" nos slides
    // Raiz estah "left-heavy" (fb == +2), deve-se balancear esse lado

    if (raiz->esq->fb == 1) { // Sinal fb do filho a balancear == sinal fb raiz
        raiz = rotacao_simples_direita(raiz);
    } else { // Sinais de fb diferentes
        raiz = rotacao_dupla_direita(raiz);
    }

    raiz->fb = 0;
    *ok = 0;
    return raiz;

}

AVL * balancear_direita(AVL * raiz, int * ok) { // "Caso2" nos slides
    // Raiz estah "right-heavy" (fb == -2), deve-se balancear esse lado

    if (raiz->dir->fb == -1) { // Sinal fb do filho a balancear == sinal fb raiz
        raiz = rotacao_simples_esquerda(raiz);
    } else { // Sinais de fb diferentes
        raiz = rotacao_dupla_esquerda(raiz);
    }

    raiz->fb = 0;
    *ok = 0;
    return raiz;

}



//  LAB
int totalNodos(AVL * raiz) {
    if (raiz) {
        return totalNodos(raiz->esq) + totalNodos(raiz->dir) + 1;
    } else {
        return 0;
    }
}

// AUX
int maior(int a, int b) {
    return (abs(a) > abs(b)) ? abs(a) : abs(b);
}

