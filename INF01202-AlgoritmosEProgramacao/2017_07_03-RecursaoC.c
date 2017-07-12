#include<stdio.h>
#include<conio2.h>
#include<windows.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>

#define X_POS 0
#define Y_POS 1

#define MAX_SNAKE 10

#define ASCII_CIMA 72
#define ASCII_BAIXO 80
#define ASCII_DIREITA 77
#define ASCII_ESQUERDA 75

#define PTS_BASE_COMIDA 2
#define PTS_BASE_SLOWER 1
#define PTS_BASE_FASTER 3
#define PTS_BASE_SKIP 40

#define LINHAS_CENARIO 24
#define COLUNAS_CENARIO 80

#define NUM_SCORES 10


// dia 12/06
typedef struct coordenada {
    int x;
    int y;
} COORDENADA;

// dia 12/06
typedef struct tunel {
    COORDENADA pos;
    int id;
    char direcao;
    int id_saida;
} TUNEL;

// dia 12/06
typedef struct score {
    int pontuacao;
    char nome[4];
} SCORE;

// dia 14/06
typedef struct cobra {
    COORDENADA corpo[MAX_SNAKE];
    char direcao;
    int tamanho;
} COBRA;

// dia 19/06
typedef struct config {
    int speed;
    int maxlen;
    int maxitem;
} CONFIG;

// carrega_score: funcao do dia 03/07
int carrega_score(SCORE *scores);

// ordena_score: funcao do dia 03/07
void ordena_score(SCORE *scores, int inicio, int fim);

// carrega_mapa: funcao do dia 28/06
int carrega_mapa(char *fname, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]);

// salva_mapa: funcao do dia 28/06
int salva_mapa(char *fname, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]);

// salva_score: funcao do dia 26/06
int salva_score(SCORE *scores);

// carrega_score: funcao do dia 26/06
int carrega_score_old(SCORE *scores);

// salva_tunel: funcao do dia 21/06
void salva_tunel(TUNEL *tuneis, int tamanho, char *fname);

// carrega_tunel: funcao do dia 21/06
int carrega_tunel(TUNEL *tuneis, char *fname);

// salva_config: funcao do dia 19/06
void salva_config(CONFIG c);

// carrega_config: funcao do dia 19/06
int carrega_config(CONFIG *c);

// busca_tunel: funcao do dia 14/06
int busca_tunel(TUNEL *tuneis, COORDENADA coord, int num_tuneis);

// entra_tunel: funcao do dia 14/06
int entra_tunel(TUNEL *tuneis, COORDENADA *corpo, char *direcao, int num_tuneis);

// desenha_tunel: funcao do dia 12/06, ALTERADA para dia 19/06
void desenha_tunel(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL *tuneis, int num_tuneis);

// insere_score: funcao do dia 12/06
void insere_score(SCORE *scores, SCORE novo_score, int num_scores);

// desenha_snake: funcao do dia 29/05
void desenha_snake(int x_cabeca, int y_cabeca, int x_cauda, int y_cauda);

// desenha_cenario: funcao do dia 29/05, alterada dia 05/06
void desenha_cenario(char cenario[25][80]);

// desenha_interface: funcao do dia 31/05
void desenha_interface(int velocidade, int cenario, int pontuacao, int tamanho);

// colidiu: funcao do dia 31/05
void colidiu(int *p_pontuacao, int *p_tamanho, int *p_velocidade, int *p_sair_do_jogo, char item);

// movimenta_snake: funcao do dia 05/06
void movimenta_snake(char cenario[25][80], int snake[MAX_SNAKE][2], int proxima_coord[2], int *p_tamanho, int cresce);

// calcula_pontuacao: funcao do dia 07/06
int calcula_pontuacao(int velocidade, int tamanho, char caractere, int pontuacao_atual);

// escolhe_item: funcao do dia 07/06
char escolhe_item();

// gera_item: funcao do dia 07/06
void gera_item(char cenario[25][80]);


int main() {
    SCORE scores[10];

    if(!carrega_score(scores)) {
        display_scores(scores, 10);
    } else {
        printf("Erro ao carregar scores.\n");
    }

    getch();

    clrscr();
    printf("Ordenando scores: \n");
    getch();

    ordena_score(scores, 0, 9);
    display_scores(scores, 10);

    fflush(stdin);
    getch();
    return 0;
}

// carrega_score: funcao do dia 03/07
/*
    Entrada: Um ponteiro para um array de score .
    Comportamento: A funcao deve carregar o arquivo de texto score.txt
    fornecido no moodle e armazena-lo no array de entrada. O arquivo esta no
    formato CSV, ou seja, cada linha e um score e seus campos estao separados por
    virgulas.A solucao pode ser implementada com fscanf com os parametros
    definidos, ou atraves de STRTOK,ATOI/ATOF.
*/
int carrega_score(SCORE *scores) {
    FILE *arq;
    SCORE buf;
    int i = 0;

    if (arq = fopen("scores.txt", "r")) {

        while (!feof(arq) && i < NUM_SCORES) {
            if (fscanf(arq, "%d,%s", &buf.pontuacao, &buf.nome) != NULL) {
                scores[i].pontuacao = buf.pontuacao;
                strcpy(scores[i].nome, buf.nome);
                i++;
            }
        }

        fclose(arq);

    } else {
        for (i = 0; i < NUM_SCORES; i++) {
            strcpy(scores[i].nome, "AAA");
            scores[i].pontuacao = 0;
        }
        return 1; // Erro ao abrir o arquivo, tudo zerado
    }

    return 0; // Tudo ok
}

// separa_pivo: funcao AUXILIAR do dia 03/07
int separa_pivo(SCORE * scores, int p, int r) {
    SCORE pivo = scores[p], t;
    int i = p + 1;
    int j = r;

    while (i <= j) {
        if (scores[i].pontuacao >= pivo.pontuacao) {
            i++;
        } else if (scores[j].pontuacao < pivo.pontuacao) {
            j--;
        } else {

            t.pontuacao = scores[i].pontuacao;
            strcpy(t.nome, scores[i].nome);

            scores[i].pontuacao = scores[j].pontuacao;
            strcpy(scores[i].nome, scores[j].nome);

            scores[j].pontuacao = t.pontuacao;
            strcpy(scores[j].nome, t.nome);

            //t = scores[i];
            //scores[i] = scores[j];
            //scores[j] = t;

            i++;
            j--;
        }
    }


    t.pontuacao = scores[p].pontuacao;
    strcpy(t.nome, scores[p].nome);

    scores[p].pontuacao = scores[j].pontuacao;
    strcpy(scores[p].nome, scores[j].nome);

    scores[j].pontuacao = t.pontuacao;
    strcpy(scores[j].nome, t.nome);

    //t = scores[p];
    //scores[p] = scores[j];
    //scores[j] = t;

    return j;
}

// ordena_score: funcao do dia 03/07
/*
    Entrada: Um ponteiro para um array de score .
    Comportamento: A funcao deve ordenar os scores em ordem decrescente de
    pontuacao . O ordenamento deve ser feito atraves de quicksort. A implementacao
    deve utilizar recursao.
*/
void ordena_score(SCORE * scores, int inicio, int fim) {
    int j;
    if (inicio < fim) {

        j = separa_pivo(scores, inicio, fim);

        ordena_score(scores, inicio, j-1);

        ordena_score(scores, j+1, fim);

    }
}


// testa_salvacarregamapa_main: funcao do dia 28/06 para testar as estruturas e funcionalidades desenvolvidas nesse dia
int testa_salvacarregamapa_main() {
    char cenario[LINHAS_CENARIO][COLUNAS_CENARIO];
    char fname[80] = "map3.txt";

    if (!carrega_mapa(fname, cenario)) {
        desenha_cenario(cenario);
    } else {
        printf("Erro ao abrir arquivo para carregar mapa.");
    }

    //printf("%c", cenario[0][78]);

    getch();
    clrscr();

    if (!salva_mapa("novo_mapa.txt", cenario)) {
        printf("Novo arquivo salvo com sucesso.");
    } else {
        printf("Erro ao salvar novo arquivo;");
    }

    fflush(stdin);
    getch();
    return 0;
}

// carrega_mapa: funcao do dia 28/06
/*
    Entrada: Uma string indicando o caminho de um arquivo de texto, um
    ponteiro para um array de strings representando um mapa do jogo.
    Comportamento: Carrega os caracteres contidos no arquivo de texto e salva
    na matriz apontada na entrada. Use os arquivos de mapa contidos na definicao
    do trabalho final.
*/
int carrega_mapa(char *fname, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]){
    FILE *arq;
    int i, j;
    char buf[81];

    if ((arq = fopen(fname, "r")) != NULL) {
        for (i = 0; i < LINHAS_CENARIO; i++) {
            fgets(buf, 81, arq);
            //printf("%s", buf);
            for(j = 0; j < COLUNAS_CENARIO; j++) {
                cenario[i][j] = buf[j];
            }
        }
        fclose(arq);
        return 0;
    } else {
        return 1;
    }
}

// salva_mapa: funcao do dia 28/06
/*
    Entrada: Uma string indicando o caminho de um arquivo de texto, um
    ponteiro para um array de strings representando um mapa do jogo.
    Comportamento: A funcao deve criar um arquivo de texto e salvar o mapa
    como uma matriz de caracteres, onde 1 representa um obstaculo e 0 representa
    um espaço vazio.
*/
int salva_mapa(char *fname, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]){
    FILE *arq;
    int i, j;

    if ((arq = fopen(fname, "w")) != NULL) {
        for (i = 0; i < LINHAS_CENARIO; i++) {
            for (j = 0; j < COLUNAS_CENARIO; j++) {
                putc(cenario[i][j], arq);
            }
            //putc('\n', arq);
        }
        fclose(arq);
        return 0;
    } else {
        return 1;
    }
}


// testa_salvacarregascore_main: funcao do dia 26/06 para testar as estruturas e funcionalidades desenvolvidas nesse dia
int testa_salvacarregascore_main() {
    SCORE scores[NUM_SCORES] = {
//         {13, "RJD"},
         {14513, "RJD"},
         {13421, "ASS"},
         {8161, "EDU"},
         {4515, "BLA"},
//         {4312, "ZZZ"},
         {4312, "LAB"},
         {4222, "BLA"},
         {4000, "AAA"},
         {3000, "BBB"},
         {2000, "CCC"},
         {1000, "DDD"}
    };
    int op = 1;


    do {

        display_scores(scores, NUM_SCORES);

        printf("\n=====\n1 - Salvar scores em arquivo de texto.\n");
        printf("2 - Carregar vetor do arquivo.\n");
        printf("3 - Sair\n");
        printf("Operacao: ");
        scanf("%d", &op);

        switch(op) {
            case 1:
                if (!salva_score(scores)) {
                    printf("\nArquivo salvo com sucesso.\n");
                } else {
                    printf("\nErro ao salvar o arquivo.\n");
                }
                break;
            case 2:
                if (!carrega_score(scores)) {
                    clrscr();
                    printf("Arquivo carregado com sucesso. Novo array de scores:\n");
                    display_scores(scores, NUM_SCORES);
                } else {
                    clrscr();
                    printf("\nNao foi possivel carregar arquivo, preenchendo com os valores zerados:\n");
                    display_scores(scores, NUM_SCORES);
                }
                break;
            default:
                break;
        }

        fflush(stdin);
        getch();
        clrscr();
    } while (op != 3);

    return 0;
}

// salva_score: funcao do dia 26/06
/*
    Entrada: Um array de score .
    Comportamento: Cria um arquivo de texto com o nome score.txt no diretorio
    do executavel e salva os scores, um por linha, no formato exemplificado:
    14513 RJD
    13421 ASS
    8161 EDU
    Caso o arquivo ja exista, ele deve ser sobreescrito.
*/
int salva_score(SCORE *scores) {
    FILE *arq;
    int i;

    if (arq = fopen("score.txt", "w")) {

        for (i = 0; i < NUM_SCORES; i++) {
            if (!(fprintf(arq, "%d %s\n", scores[i].pontuacao, scores[i].nome))) {
                fclose(arq);
                return 1; // Erro ao escrever para o arquivo
            }
        }

        fclose(arq);
    } else {
        return 1; // Erro ao abrir arquivo
    }

    return 0; // Tudo certo
}

// carrega_score_old: funcao do dia 26/06
/*
    Entrada: Um ponteiro para um array de score .
    Comportamento: A funcao deve carregar o arquivo de texto score.txt no
    formato exemplificado na primeira funcao e salvar os scores na lista de entrada.
    Caso o arquivo nao exista ou seja invalido, preencha todos os scores da lista com
    0 AAA. Considere que o número de score s é 10.
*/
int carrega_score_old(SCORE *scores) {
    FILE *arq;
    SCORE buf;
    int i = 0;

    if (arq = fopen("score.txt", "r")) {

        while (!feof(arq) && i < NUM_SCORES) {
            if (fscanf(arq, "%d %s", &buf.pontuacao, &buf.nome) != NULL) {
                scores[i].pontuacao = buf.pontuacao;
                strcpy(scores[i].nome, buf.nome);
                i++;
            }
        }

        fclose(arq);

    } else {
        for (i = 0; i < NUM_SCORES; i++) {
            strcpy(scores[i].nome, "AAA");
            scores[i].pontuacao = 0;
        }
        return 1; // Erro ao abrir o arquivo, tudo zerado
    }

    return 0; // Tudo ok
}

// testa_salvacarregatunel_main: funcao do dia 21/06 para testar as estruturas e funcionalidades desenvolvidas nesse dia
int testa_salvacarregatunel_main() {
    int op, tamanho = 4;
    TUNEL tuneis[4] = { {{2,3} , 0, 'E', 2},
                        {{10,10} , 1, 'C', 3},
                        {{60,6} , 2, 'B', 1},
                        {{40,17} , 3, 'D', 0}};
//    TUNEL tuneis[4] = { {{45,3} , 0, 'E', 1},
//                        {{0,10} , 1, 'a', 1},
//                        {{30,6} , 2, 'A', 1},
//                        {{40,40} , 3, 'v', 1}};

    clrscr();
    exibe_tunel(tuneis, tamanho);

    printf("1 - Salvar tuneis, 2 - Carregar tuneis do arquivo: ");
    scanf("%d", &op);

    switch(op) {
        case 1:
            salva_tunel(tuneis, tamanho, "tuneis-2017_06_21.bin");
            printf("Tuneis salvos no arquivo.\n");
            break;
        case 2:
            tamanho = carrega_tunel(tuneis, "tuneis-2017_06_21.bin");
            clrscr();
//            printf("Total de tuneis carregados: %d", tamanho);
//            getch();
//            clrscr();
            printf("Tuneis carregados do arquivo:\n");
            exibe_tunel(tuneis, tamanho);
            break;
        default:
            printf("Codigo invalido.\n");
            break;
    }


    getch();

    return 0;
}

// salva_tunel: funcao do dia 21/06
/*
    Entrada: Um array de tunel , um int indicando o tamanho do array, uma string
    especificando um caminho de arquivo.
    Comportamento: Cria um arquivo binario no caminho especificado e salva a
    lista de tunel no mesmo.
*/
void salva_tunel(TUNEL *tuneis, int tamanho, char *fname){
    int i;
    FILE *arq;

    arq = fopen(fname, "wb");

    for (i = 0; i < tamanho; i++) {
        fwrite(&tuneis[i], sizeof(tuneis[i]), 1, arq);
    }

    close(arq);
}

// carrega_tunel: funcao do dia 21/06
/*
    Entrada: Um ponteiro para um array de tunel , uma string especificando um
    caminho de arquivo.
    Comportamento: A funcao deve carregar o arquivo criado pela primeira
    funcao e salvar o array lido no array apontado na entrada.
    Saida: Um int indicando a quantidade de tunel s lidos do arquivo.
*/
int carrega_tunel(TUNEL *tuneis, char *fname){
    int tamanho = 0, tam_buff;
    TUNEL tun_buff;
    FILE *arq;

    arq = fopen(fname, "rb");

    while (!feof(arq)) {
        tam_buff = fread(&tun_buff, sizeof(TUNEL), 1, arq);

        if (tam_buff == 1) {
            tuneis[tamanho] = tun_buff;
            tamanho += tam_buff;
        }
    }

    close(arq);

    return tamanho;

}

// exibe_tunel: funcao AUXILIAR 21/06
void exibe_tunel(TUNEL *tuneis, int tamanho) {
    int i;
    for (i = 0; i < tamanho; i++) {
        printf("\nTUNEL %d\n", i);
        printf("Pos X: %d\t Pos Y: %d\n", tuneis[i].pos.x, tuneis[i].pos.y);
        printf("ID: %d\n", tuneis[i].id);
        printf("Direcao: %c\n", tuneis[i].direcao);
        printf("ID Saida: %d\n", tuneis[i].id_saida);
        printf("==========\n");
    }
}


// testa_salvacarregaconfig_main: funcao do dia 19/06 para testar as estruturas e funcionalidades desenvolvidas nesse dia
int testa_salvacarregaconfig_main() {
   CONFIG configuracoes;
   int op;
   int result_carrega;

   do {
        clrscr();
        printf("Entre 1 para preencher a config com dados, 2 para salvar a config, 3 para carregar a config do arquivo, 0 para sair: ");
        scanf("%d", &op);

        switch(op) {
            case 1:
                printf("Speed: ");
                scanf("%d", &configuracoes.speed);
                printf("\nMaxlen: ");
                scanf("%d", &configuracoes.maxlen);
                printf("\nMaxitem: ");
                scanf("%d", &configuracoes.maxitem);

                printf("\n\nConfig preenchida. Dados atuais:\n");
                printf("Speed: %d", configuracoes.speed);
                printf("\nMaxlen: %d", configuracoes.maxlen);
                printf("\nMaxitem: %d", configuracoes.maxitem);

                getch();
                break;
            case 2:
                salva_config(configuracoes);
                printf("\nConfiguracao salva.");
                getch();
                break;
            case 3:
                if (carrega_config(&configuracoes)) {
                    printf("\nArquivo carregado com sucesso. Dados atuais:\n");
                } else {
                    printf("\nArquivo nao pode ser carregado, preenchendo com valores minimos. Dados atuais:\n");
                }
                printf("Speed: %d", configuracoes.speed);
                printf("\nMaxlen: %d", configuracoes.maxlen);
                printf("\nMaxitem: %d", configuracoes.maxitem);
                getch();
                break;
            default:
                break;
        }

   } while (op != 0);

   getch();

   return 0;
}

// salva_config: funcao do dia 19/06
/*
    Entrada: Uma config.
    Comportamento: Cria um arquivo binario e salva a configuracao no mesmo.
*/
void salva_config(CONFIG c) {
    FILE *arq;

    arq = fopen("config_2017-06-19.bin", "wb");

    fwrite(&c, sizeof(CONFIG), 1, arq);

    fclose(arq);

}

// carrega_config: funcao do dia 19/06
/*
    Entrada: Um ponteiro para uma config .
    Comportamento: A funcao deve carregar o arquivo criado pela primeira
    funcao e salvar a estrutura na config apontada pela entrada. Caso o arquivo nao
    possa ser carregado ou seja invalido, preencha a config com os valores minimos.
*/
int carrega_config(CONFIG *c) {
    FILE *arq;

    if (arq = fopen("config_2017-06-19.bin", "rb")) {
        fread(c, sizeof(CONFIG), 1, arq);
        return 1;
    } else {
        c->speed = 1;
        c->maxlen = 10;
        c->maxitem = 1;
        return 0;
    }

}

// testa_buscaentratunel_main: funcao do dia 14/06 para testar as estruturas e funcionalidades desenvolvidas nesse dia
int testa_buscaentratunel_main () {
    TUNEL tuneis[4], t1 = { {2,3} , 0, 'E', 2},
                     t2 = { {10,10} , 1, 'C', 3},
                     t3 = { {60,6} , 2, 'B', 1},
                     t4 = { {40,17} , 3, 'D', 0};
    COORDENADA c[5] = { {2,3},
                        {10,10},
                        {60,6},
                        {40,17},
                        {30,11} };
    COBRA snake = {
        {0},
        'D',
        5
    };

    int i, teste_index_1, teste_index_2, teste_index_3, teste_index_4, teste_index_5;
    // Matriz para representacao do cenario
    char cenario[3][25][80] = {{
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"},
    //                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"}},
                                {
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"},
    //                            {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"}},
                                {
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"},
    //                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000001111111111110000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000111111111111100000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"}}};



    tuneis[0] = t1;
    tuneis[1] = t2;
    tuneis[2] = t3;
    tuneis[3] = t4;

    teste_index_1 = busca_tunel(tuneis, c[0], 4);
    printf("TESTE 1 - Esperado: 0, encontrado: %d\n", teste_index_1);
    teste_index_2 = busca_tunel(tuneis, c[1], 4);
    printf("TESTE 2 - Esperado: 1, encontrado: %d\n", teste_index_2);
    teste_index_3 = busca_tunel(tuneis, c[2], 4);
    printf("TESTE 3 - Esperado: 2, encontrado: %d\n", teste_index_3);
    teste_index_4 = busca_tunel(tuneis, c[3], 4);
    printf("TESTE 4 - Esperado: 3, encontrado: %d\n", teste_index_4);
    teste_index_5 = busca_tunel(tuneis, c[4], 4);
    printf("TESTE 5 - Esperado: -1, encontrado: %d\n", teste_index_5);

    getch();

    clrscr();
    printf("=== TESTES ENTRA_TUNEL ===\n\n-----\n");

    // Teste 1
    snake.corpo[0].x = 2;
    snake.corpo[0].y = 3;
    snake.direcao = 'E';
    printf("TESTE 1\n");
    if (entra_tunel(tuneis, snake.corpo, &snake.direcao, 4)){
        printf("PosX - Esperado: 60, encontrado: %d\n", snake.corpo[0].x);
        printf("PosY - Esperado: 6, encontrado: %d\n", snake.corpo[0].y);
        printf("Direcao - Esperado: B, encontrado: %c\n", snake.direcao);
        printf("-----\n");
    } else {
        printf("ENTRA_TUNEL retornou 0 no teste 1\n-----\n");
    }


    // Teste 2
    snake.corpo[0].x = 10;
    snake.corpo[0].y = 10;
    snake.direcao = 'C';
    printf("TESTE 2\n");
    if (entra_tunel(tuneis, snake.corpo, &snake.direcao, 4)){
        printf("PosX - Esperado: 40, encontrado: %d\n", snake.corpo[0].x);
        printf("PosY - Esperado: 17, encontrado: %d\n", snake.corpo[0].y);
        printf("Direcao - Esperado: D, encontrado: %c\n", snake.direcao);
        printf("-----\n");
    } else {
        printf("ENTRA_TUNEL retornou 0 no teste 2\n-----\n");
    }

    // Teste 3
    snake.corpo[0].x = 10;
    snake.corpo[0].y = 10;
    snake.direcao = 'D';
    printf("TESTE 3\n");
    if (entra_tunel(tuneis, snake.corpo, &snake.direcao, 4)){
        printf("ENTRA_TUNEL retornou 1 no teste 3 mesmo entrando pela direcao errada\n-----\n");
    } else {
        printf("ENTRA_TUNEL retornou 0 no teste 3 ao entrar pela direcao errada\n-----\n");
    }



    getch();

    return 0;
}

// busca_tunel: funcao do dia 14/06
/*
    Entrada: Um vetor de tunel , uma coordenada .
    Saida: O index do tunel correspondente a coordenada de entrada.
*/
int busca_tunel(TUNEL *tuneis, COORDENADA coord, int num_tuneis) {
    int i, i_encontrado = -1;

    for (i = 0; i < num_tuneis; i++) {
        if ((tuneis[i].pos.x == coord.x) && (tuneis[i].pos.y == coord.y)) {
            i_encontrado = i;
        }
    }

    return i_encontrado;
}

// entra_tunel: funcao do dia 14/06
/*
    Entrada: Um vetor de tunel , um vetor de coordenada representando a cobra, um ponteiro para a direcao
    atual da cobra.
    Comportamento: A funcao deve:
    -Buscar o tunel correspondente a coordenada.
    -Verificar se a cobra esta entrando no tunel pela direcao correta.
    Opcional: Mover a cabeca da cobra para o tunel correspondente e alterar a sua
    direcao.
*/
int entra_tunel(TUNEL *tuneis, COORDENADA *corpo, char *direcao, int num_tuneis) {
    int i, novo_x, novo_y;
    char nova_direcao;

    i = busca_tunel(tuneis, corpo[0], num_tuneis);

    if (*direcao != tuneis[i].direcao) {
        return 0; // Cobra entrou pela direcao errada, morreu
    }

    novo_x = tuneis[tuneis[i].id_saida].pos.x; //printf("NovoX:%d\n", novo_x);
    novo_y = tuneis[tuneis[i].id_saida].pos.y; //printf("NovoY:%d\n", novo_y);
    nova_direcao = tuneis[tuneis[i].id_saida].direcao; //printf("NovaD:%c\n", nova_direcao);

    corpo[0].x = novo_x;
    corpo[0].y = novo_y;
    *direcao = nova_direcao;

    return 1; // Sucesso

}

// testa_tunelescore_main: funcao do dia 12/06 para testar as estruturas e funcionalidades desenvolvidas nesse dia
int testa_tunelescore_main () {
    TUNEL tuneis[4], t1 = { {2,3} , 1, 'E', 3},
                     t2 = { {10,10} , 2, 'C', 4},
                     t3 = { {60,6} , 3, 'B', 2},
                     t4 = { {40,17} , 4, 'D', 1};

    SCORE scores[4], s1 = {300, "AAA"},
                     s2 = {200, "BBB"},
                     s3 = {150, "CCC"},
                     s4 = {100, "DDD"},
                     ns = {250, "NEW"};
    int i;
    // Matriz para representacao do cenario
    char cenario[3][25][80] = {{
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"},
    //                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"}},
                                {
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"},
    //                            {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"}},
                                {
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"},
    //                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000001111111111110000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000111111111111100000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"}}};



    tuneis[0] = t1;
    tuneis[1] = t2;
    tuneis[2] = t3;
    tuneis[3] = t4;

    // desenha_tunel coloca os tuneis no array cenario, nao na tela
    // portanto chamar desenha_cenario apenas DEPOIS de chamar desenha_tunel
    desenha_cenario(cenario[0]);
    desenha_tunel(cenario[0], tuneis, 4);


    getch();

    clrscr(); // Teste tuneis realizado, partir para teste scores


    scores[0] = s1;
    scores[1] = s2;
    scores[2] = s3;
    scores[3] = s4;

    display_scores(scores, 4); // Mostra array original, antes de reordenar

    getch();

    insere_score(scores, ns, 4); // Reordena com novo score

    display_scores(scores, 4); // Mostra array reordenado

    getch();

    return 0;
}

//desenha_tunel: funcao do dia 12/06, ALTERADA para dia 19/06
/*
    Entrada: Um array de strings representando o mapa, um vetor de tunel e um
    int indicando o numero de tuneis.
    Comportamento: Para cada um dos tuneis, a funcao verifica sua posicao e
    direcao, e insere na posicao correspondente do mapa um caracter indicando um
    tunel na direcao apropriada.
*/
void desenha_tunel(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL *tuneis, int num_tuneis){
    int i;
    char direcao;

    for (i = 0; i < num_tuneis; i++) {
        // Determina caracter de acordo com a direcao de entrada do tunel
        switch(tuneis[i].direcao) {
            case 'B':
                direcao = '\x19';
                break;
            case 'C':
                direcao = '\x18';
                break;
            case 'E':
                direcao = '\x1b';
                break;
            case 'D':
                direcao = '\x1a';
                break;
            default:
                direcao = '0';
                break;
        }
        //cenario[tuneis[i].pos.y][tuneis[i].pos.x] = direcao; // Coloca tunel NO ARRAY CENARIO, nao na tela
        cenario[tuneis[i].pos.y][tuneis[i].pos.x] = 'T'; // Coloca tunel NO ARRAY CENARIO, nao na tela
        putchxy((tuneis[i].pos.x)+1, (tuneis[i].pos.y)+2, direcao); // Coloca tunel na tela
    }
}

// insere_score: funcao do dia 12/06
/*
    Entrada: Um vetor de score , um novo score e o tamanho do vetor.
    Comportamento: O vetor deve estar ordenado em ordem decrescente, o novo
    score deve ser inserido na posicao apropriada e o menor score descartado.
    Imprima a lista na tela.
*/
void insere_score(SCORE *scores, SCORE novo_score, int num_scores){
    int i, j; //, index_colocar = -1;

    // Buscando posicao para inserir
    i = 0;
    while ((scores[i].pontuacao > novo_score.pontuacao) && (i < num_scores)) {
        i++;
    }

    // Se entrar na lista, insere na posicao correta
    if (i < num_scores) {
        for (j = num_scores - 1; j > i ; j-- ) {
            strcpy(scores[j].nome, scores[j-1].nome);
            scores[j].pontuacao = scores[j-1].pontuacao;
        }
        strcpy(scores[i].nome, novo_score.nome);
        scores[i].pontuacao = novo_score.pontuacao;
    }

}

// display_scores: funcao auxiliar feita para o dia 12/06
/*
   Apenas facilita a visualizacao do array de scores, para uso durante teste de reordenacao
*/
void display_scores(SCORE *scores, int num_scores) {
    int i;

    printf("========\nSCORES:\n\n");

    for (i = 0; i < num_scores; i++) {
        printf("%s\t%d\n", scores[i].nome, scores[i].pontuacao);
    }

    printf("========\n");

}

// main: funcao principal, eventualmente redirecionada para testes, tendo seu nome alterado
int jogo_main() {
    // snake: Vetor para representar as posicoes atualmente ocupadas pela cobra
    // Sendo que: snake[0] = cabeca da cobra, snake[tamanho] = cauda da cobra
    // E: snake[0][X_POS] = coordenada x da cabeca da cobra, snake[0][Y_POS] = coordenada y
    int snake[MAX_SNAKE][2] = {0};
    // proximo_movimento: Vetor que contem o proximo movimento da cobra, alterado quando uma tecla direcional
    // eh pressionada
    int proximo_movimento[2] = {1,0};
    int proxima_coord[2] = {0};
    int num_cenario;
    int encerrar = 0, pause = 0;
    int op; // para leitura do teclado
    int i;
    int aux_x, aux_y;
    int tamanho = 7; // tamanho atual da cobra
    int velocidade = 1;
    int pontuacao = 0;
    // Matriz para representacao do cenario
    char cenario[3][25][80] = {{
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"},
    //                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10C00000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"}},
                                {
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"},
    //                            {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000100000000000000000000000000000000000001"},
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"}},
                                {
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"},
    //                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000001111111111110000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000111111111111100000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000010000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                                {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"}}};

    char item_no_proximo_movimento; // para verificar se houve uma colisao

    srand(time(0)); // Para calculos com rand

    // Posicao inicial da cabeca da cobra setada arbitrariamente
    snake[0][X_POS] = 20;
    snake[0][Y_POS] = 10;

    printf("Escolha o cenario: ");
    scanf("%d", &num_cenario);

    // Inicializando a tela do jogo
    desenha_interface(velocidade, num_cenario, pontuacao, tamanho);
    desenha_cenario(cenario[num_cenario-1]);

    // Processamento do jogo. Fica em loop ateh que o usuario aperte Esc ou a cobra bata num obstaculo
    while (!encerrar) {
        if (kbhit()) { // Se alguma tecla foi pressionada
            op = getch(); // Pega o codigo da tecla pressionada

            if (op == 224 /*-32*/) { // Tecla do teclado extendido. ex: setas direcionais
                // Processa alteracao na direcao do movimento, setando no vetor proximo_movimento os valores relevantes
                switch(getch()) {
                case ASCII_CIMA:
                    if (proximo_movimento[Y_POS] != 1) { // Se nao estiver indo para baixo
                        proximo_movimento[X_POS] = 0;
                        proximo_movimento[Y_POS] = -1;
                    }

                    break;
                case ASCII_BAIXO:
                    if (proximo_movimento[Y_POS] != -1) { // Se nao estiver indo para cima
                        proximo_movimento[X_POS] = 0;
                        proximo_movimento[Y_POS] = 1;
                    }
                    break;
                case ASCII_DIREITA:
                    if (proximo_movimento[X_POS] != -1) { // Se nao estiver indo para esquerda
                        proximo_movimento[X_POS] = 1;
                        proximo_movimento[Y_POS] = 0;
                    }
                    break;
                case ASCII_ESQUERDA:
                    if (proximo_movimento[X_POS] != 1) { // Se nao estiver indo para direita
                        proximo_movimento[X_POS] = -1;
                        proximo_movimento[Y_POS] = 0;
                    }
                    break;
                default:
                    break;
                }

            } else if (op == 32) { // Tecla de espaco pausa o jogo
                if (pause) {
                    pause = 0;
                } else {
                    pause = 1;
                }
            } else if (op == 27) { // Tecla Esc sai do jogo
                encerrar = 1;
            } else if (op == 'w') { // Teclas 'WASD' refletem o funcionamento das setas direcionais
                if (proximo_movimento[Y_POS] != 1) {
                    proximo_movimento[Y_POS] = -1;
                    proximo_movimento[X_POS] = 0;
                }
            } else if (op == 's') {
                if (proximo_movimento[Y_POS] != -1) {
                    proximo_movimento[Y_POS] = 1;
                    proximo_movimento[X_POS] = 0;
                }
            } else if (op == 'd') {
                if (proximo_movimento[X_POS] != -1) {
                    proximo_movimento[Y_POS] = 0;
                    proximo_movimento[X_POS] = 1;
                }
            } else if (op == 'a') {
                if (proximo_movimento[X_POS] != 1) {
                    proximo_movimento[Y_POS] = 0;
                    proximo_movimento[X_POS] = -1;
                }
            } else if (op == 'g') { // Para debug, tecla 'g' faz a cobra crescer
                if (tamanho < MAX_SNAKE - 1) {
                    tamanho += 1;
                }
                desenha_interface(velocidade, num_cenario, pontuacao, tamanho);
            } else if (op == 't') { // Para debug, tecla 't' aumenta a pontuacao
                pontuacao += 1;
                desenha_interface(velocidade, num_cenario, pontuacao, tamanho);
            } else if (op == 'n') { // Para debug, tecla 'n' testa geracao de novos itens
                //putchxy(3, 23, escolhe_item());
                gera_item(cenario[num_cenario-1]);
            }
        }
        if (!pause) { // Se estiver pausado, nao faz nada. Caso contrario, processa proximo instante do jogo

            // Determina a proxima posicao da cabeca da cobra (proximo movimento)
            // atraves da simples soma da posicao atual da cabeca com os valores de proximo_movimento
            proxima_coord[X_POS] = snake[0][X_POS] + proximo_movimento[X_POS];
            proxima_coord[Y_POS] = snake[0][Y_POS] + proximo_movimento[Y_POS];

            // Pega o caractere na posicao da cabeca da cobra na matriz do cenario
            item_no_proximo_movimento = cenario[num_cenario-1][proxima_coord[Y_POS]-2][proxima_coord[X_POS]-1];

            // Se a nova posicao da cabeca nao estiver vazia, processa uma colisao
            // se estiver vazia, apenas movimenta a cobra
            if (item_no_proximo_movimento != '0') {
                colidiu(&pontuacao, &velocidade, &tamanho, &encerrar, item_no_proximo_movimento);
                if (item_no_proximo_movimento == 'C') { // Comida, cobra cresce
                    movimenta_snake(cenario[num_cenario - 1], snake, proxima_coord, &tamanho, 1);
                } else if (item_no_proximo_movimento == 'S' ||
                           item_no_proximo_movimento == 'F') {
                    movimenta_snake(cenario[num_cenario - 1], snake, proxima_coord, &tamanho, 0);
                }
                desenha_interface(velocidade, num_cenario, pontuacao, tamanho); // Altera interface apenas se necessario
            } else {
                movimenta_snake(cenario[num_cenario - 1], snake, proxima_coord, &tamanho, 0);
            }

        }
        //gotoxy(1,1);

        // Controla a velocidade do jogo
        Sleep(100);

    }


    // Jogo encerrado, seta o cursor para o fim da tela, evitando que sobrescreva o cenario
    gotoxy(1,27);

    //getch();

    return 0;
}

// desenha_snake: funcao do dia 29/05
/*
    Dada uma posicao X e Y, desenha a cabeca da cobra na
    posicao. E dada outra posicao X e Y, apaga a cauda da cobra nessa
    posicao.
*/
void desenha_snake(int x_cabeca, int y_cabeca, int x_cauda, int y_cauda) {
    putchxy(x_cabeca, y_cabeca, 'X');
    putchxy(x_cauda, y_cauda, ' ');
}

// desenha_cenario: funcao do dia 29/05
/*
    Entrada: Uma matriz de strings que representa o mapa composta por numeros
    que indicam o objeto presente na celula correspondente.
    Comportamento: desenha o mapa na tela (a partir da linha 2), convertendo os
    caracteres para a representacao escolhida.
*/
void desenha_cenario(char cenario[25][80]) {
    int i, j;

    for (i = 0; i < 25; i++) {
        for (j = 0; j < 80; j++) {
            if (cenario[i][j] == '1') { // Obstaculo
                putchxy(j+1, i+2, '|');
            } else if (cenario[i][j] == '0') { // Vazio
                putchxy(j+1, i+2, ' ');
            } else if (cenario[i][j] == 'T') { // Por enquanto nao fazer nada com tuneis, talvez mude no futuro
                putchxy(j+1, i+2, 'T');
            } else { // Se nao for obstaculo nem vazio, desenha o caractere que estiver na matriz
                putchxy(j+1, i+2, cenario[i][j]);
            }
        }
    }
    gotoxy(1,1); // Volta o cursor para o início da tela
}

// desenha_interface: funcao do dia 31/05
/*
    Desenha na primeira linha(acima do cenario atual), a
    pontuacao, o tamanho, a velocidade e o numero do cenario atual.
*/
void desenha_interface(int velocidade, int cenario, int pontuacao, int tamanho) {
    char status[80];
    int i;

    // Gera a string da interface com os valores passados
    sprintf(status, "Pontuacao: %d\t\tVelocidade: %d\t\tTamanho: %d\tCenario: %d", pontuacao, velocidade, tamanho, cenario);

    textbackground(15);
    textcolor(0);
    // Preenche toda a linha com a cor de fundo
    for (i = 1; i < 81; i++) {
        putchxy(i, 1, ' ');
    }
    // Escreve a string da interface na tela
    cputsxy(1,1,status);

    // Retorna a cor de fundo padrao do terminal
    textbackground(0);
    textcolor(15);

}

// colidiu: funcao do dia 31/05
/*
    Entrada: Quatro ponteiros para inteiro e um caracter. Os quatro ponteiros sao:
             Pontuacao, Tamanho, Velocidade, SairDoJogo
    Comportamento: Verifica o caracter lido de acordo com sua
    representacao no jogo(1 para obstaculo, defina os outros caracteres para
    cada item a ser coletado), e altera o conteudo da variavel correspondente,
    por exemplo, se for um item, altera a pontuacao e tamanho, se for item
    especial, altera velocidade, se for obstaculo, altera a variavel SairDoJogo.
*/
void colidiu(int *p_pontuacao, int *p_velocidade, int *p_tamanho, int *p_encerrar, char item) {
    switch(item) { // Processa a colisao de acordo com o que havia naquela posicao
        case '1': // Obstaculo
        case 'B': // Corpo (body) da cobra
            *p_encerrar = 1; // Game Over
            break;
        case 'C': // Comida
            //*p_pontuacao += 2 * (*p_tamanho / 5) * *p_velocidade; // Aumenta pontuacao
            *p_pontuacao = calcula_pontuacao(*p_velocidade, *p_tamanho, item, *p_pontuacao); // Aumenta pontuacao
            // TRECHO REMOVIDO POIS: a nova funcao movimenta_snake deve tratar essa operacao, de acordo com
            // o exercico do dia 05/06
//            if (*p_tamanho < MAX_SNAKE - 1) {
//                *p_tamanho += 1;
//            }
            break;
        case 'F':
            *p_pontuacao = calcula_pontuacao(*p_velocidade, *p_tamanho, item, *p_pontuacao); // Aumenta pontuacao
            break;
        case 'S':
            *p_pontuacao = calcula_pontuacao(*p_velocidade, *p_tamanho, item, *p_pontuacao); // Aumenta pontuacao
            break;
        case 'V':
            *p_pontuacao = calcula_pontuacao(*p_velocidade, *p_tamanho, item, *p_pontuacao); // Aumenta pontuacao
            *p_encerrar = 1;
            break;
        default:
            break;
    }
}

// movimenta_snake: funcao do dia 05/06
/*
    Entrada: Uma matriz de strings representando o mapa, uma matriz 2xN onde
    cada coluna representa a coordenada de um segmento da cobra, um vetor de duas
    posicoes indicando a proxima coordenada da cabeca da cobra, um int indicando o
    tamanho atual da cobra, e uma booleana indicando se a cobra cresce.
    Comportamento: Atualiza a matriz de posicao da cobra movendo todas as
    colunas um index para a direita e adicionando uma posicao nova na primeira
    coluna correspondendo a nova posicao da cabeca. Caso a cobra nao cresca, a
    posicao da cauda deve ser zerada na matriz do mapa, descarte a posicao do ultimo
    segmento da cobra. Caso a cobra cresca, incremente o contador do tamanho da
    cobra
*/
void movimenta_snake(char cenario[25][80], int snake[MAX_SNAKE][2], int proxima_coord[2], int *p_tamanho, int cresce) {
    int i;

    // Aumenta o tamanho caso cobra deva crescer e ainda nao esteja no tamanho maximo
    if (cresce && (*p_tamanho < MAX_SNAKE - 1)) {
        *p_tamanho += 1;
    }

    // Atualiza o array com as posicoes da cobra, movendo tudo uma posicao para a direita
    for (i = *p_tamanho; i > 0; i--) {
        snake[i][X_POS] = snake[i-1][X_POS];
        snake[i][Y_POS] = snake[i-1][Y_POS];
    }
    // Seta a proxima posicao da cabeca da cobra com os valores computados na main e passados para essa funcao
    snake[0][X_POS] = proxima_coord[X_POS];
    snake[0][Y_POS] = proxima_coord[Y_POS];

    // Atualiza posicao da cobra dentro do array cenario
    cenario[snake[0][Y_POS]-2][snake[0][X_POS]-1] = 'B';
    if (!cresce) { // Se crescer, nao remove a ultima posicao da cobra no array cenario - se crescer remove
        cenario[snake[*p_tamanho][Y_POS]-2][snake[*p_tamanho][X_POS]-1] = '0';
    }

    // Desenha a cobra na tela com as ultimas atualizacoes
    desenha_snake(snake[0][X_POS], snake[0][Y_POS], snake[*p_tamanho][X_POS], snake[*p_tamanho][Y_POS]);
}


// calcula_pontuacao: funcao do dia 07/06
/*
    Entrada: Velocidade, tamanho da cobra, valor item coletado, pontuacao atual.
    Defina os valores base dos itens como constantes.
    Saida: Retorna a pontuacao atualizada. Calcule a pontuacao de acordo com a
    definicao do trabalho final.
*/
int calcula_pontuacao(int velocidade, int tamanho, char caractere, int pontuacao_atual) {
    int pts_base, pontuacao_nova;
    switch(caractere) {
        case 'C':
            pts_base = PTS_BASE_COMIDA;
            break;
        case 'F':
            pts_base = PTS_BASE_FASTER;
            break;
        case 'S':
            pts_base = PTS_BASE_SLOWER;
            break;
        case 'V':
            pts_base = PTS_BASE_SKIP;
            break;
    }

    pontuacao_nova = pontuacao_atual + (pts_base * (tamanho / 5) * velocidade);

    return pontuacao_nova;
}

// escolhe_item: funcao do dia 07/06
/*
    Escolhe um item aleatoriamente e retorna um caracter correspondente.
    O item deve ser escolhido de acordo com as probabilidades descritas na definicao
    do trabalho final.
*/
char escolhe_item() {
    // val: Valor aleatorio de 0 a 99, a faixa onde ele cair determina o objeto a ser retornado
    // probabilidades deteminadas: Comida 67%, Faster 20%, Slower 10%, Skip 3%
    int val = (int) (rand() / (double) RAND_MAX * 100);
    char objeto;

    // Verifica o range em que val caiu e retorna um objeto de acordo com a probabilidade
    if (val < 3) {
        objeto = 'V';
    } else if (val < 13) {
        objeto = 'S';
    } else if (val < 33) {
        objeto = 'F';
    } else {
        objeto = 'C';
    }

    return objeto;
}

// gera_item: funcao do dia 07/06
/*
    Entrada: Uma matriz de strings representando o mapa
    Comportamento: Escolhe uma posicao do mapa aleatoriamente, verifica se
    esta vazia e insere um item escolhido por escolhe_item nesta posicao, caso a
    posicao nao esteja vazia, escolha uma nova posicao.
*/
void gera_item(char cenario[25][80]){
    int novo_x, novo_y;
    char novo_item = escolhe_item();

    do {
        // novo_y entre 1 e 23, pois primeira linha = obstaculos sempre
        novo_y = ((int) (rand() / (double) RAND_MAX * 22)) + 1;
        // novo_x entre 1 e 78, pois primeira e ultima coluna = obstaculos sempre
        novo_x = ((int) (rand() / (double) RAND_MAX * 78)) + 1;
    } while(cenario[novo_y][novo_x] != '0');

    cenario[novo_y][novo_x] = novo_item;
    putchxy(novo_x+1, novo_y+2, novo_item); // compensando indexacao do terminal e interface
}
