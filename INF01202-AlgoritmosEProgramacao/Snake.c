/*
    ================ SNAKE ======================
    Desenvolvido por Tiago Ceccon e Manuel Micas.
    2017-01 INF01202-ALGPROG
*/

#include<stdio.h>
#include<conio2.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>

#define FILENAME_HIGH_SCORES "scores.txt"
#define FILENAME_CONFIG "config.bin"
#define FILENAME_TUNEIS "tuneis.bin"

#define MAX_X_TELA 80
#define MAX_Y_TELA 25

#define LINHA_INICIO_MENU 15
#define LINHA_INICIO_HIGH_SCORES 12
#define COLUNA_INICIO_HIGH_SCORES 30
#define COLUNA_INICIO_MENU_OPCOES 35

#define LINHA_INICIO_FIMCENARIO 11
#define LINHA_FIM_FIMCENARIO 20
#define COLUNA_INICIO_FIMCENARIO 25
#define COLUNA_FIM_FIMCENARIO 65

#define LINHA_MSG_FIMCENARIO 12
#define COLUNA_MSG_FIMCENARIO 36
#define LINHA_PONTUACAO_FIMCENARIO 14
#define COLUNA_PONTUACAO_FIMCENARIO 30
#define LINHA_SAIR_FIMCENARIO 18
#define COLUNA_SAIR_FIMCENARIO 33

#define LINHA_INICIO_ENTRAHIGHSCORE 20
#define LINHA_FIM_ENTRAHIGHSCORE 24
#define COLUNA_INICIO_ENTRAHIGHSCORE 25
#define COLUNA_FIM_ENTRAHIGHSCORE 65

#define LINHA_NOME_HIGHSCORE 22
#define COLUNA_NOME_HIGHSCORE 38

#define MAX_STRINGS_MENU 20
#define MAXSIZE_STRINGS_MENU 20
#define MAXSIZE_MSGS_FIMCENARIO 50

#define NUM_OPCOES 5

#define NOVO_JOGO 0
#define HIGH_SCORES 1
#define OPCOES 2
#define CREDITOS 3
#define SAIR 4

#define MENU_CONFIG_VELOCIDADEINICIAL 0
#define MENU_CONFIG_MAXTAMANHO 1
#define MENU_CONFIG_MAXITENS 2
#define MENU_CONFIG_VOLTAR 3

#define UM_SEGUNDO_EM_MS 1000

#define X_POS 0
#define Y_POS 1
#define MAX_SNAKE 80
#define INI_X_SNAKE 20
#define INI_Y_SNAKE 12
#define INI_TAM_SNAKE 5
#define OFFSET_X 1
#define OFFSET_Y 2

#define TECLADO_ESTENDIDO 224

#define ASCII_CIMA 72
#define ASCII_BAIXO 80
#define ASCII_DIREITA 77
#define ASCII_ESQUERDA 75

#define ASCII_ENTER 13

#define ASCII_SPACEBAR 32
#define ASCII_ESC 27

#define BACK_CENARIO 6
#define BACK_SNAKE 2

#define I_OPTS_VELOCIDADE 0
#define I_OPTS_MAXTAMANHO 1
#define I_OPTS_MAXITENS 2
#define I_OPTS_NUMCENARIO 3
#define I_OPTS_SCORE 4

#define NUM_OPCOES_CONFIG 4

#define MIN_VELOCIDADEINICIAL 1
#define MAX_VELOCIDADEINICIAL 10
#define MIN_MAXTAMANHO 10
#define MAX_MAXTAMANHO 100
#define MIN_MAXITENS 1
#define MAX_MAXITENS 10

#define VELOCIDADEINICIAL_PADRAO 5
#define MAXTAMANHO_PADRAO 20
#define MAXITENS_PADRAO 5

#define PTS_BASE_COMIDA 2
#define PTS_BASE_SLOWER 1
#define PTS_BASE_FASTER 3
#define PTS_BASE_SKIP 40

#define BONUS_COMPLETA_CENARIO 1000

#define NUM_CENARIOS 3
#define LINHAS_CENARIO 24
#define COLUNAS_CENARIO 80

#define MAX_TUNEIS 5

#define MAX_NOME 3
#define NUM_HIGH_SCORES 10
#define MAXSIZE_STRING_HIGHSCORES 15

#define GAME_OVER 1
#define CENARIO_COMPLETO 2
#define USER_EXIT 3

typedef struct coordenada {
    int x;
    int y;
} COORDENADA;

typedef struct snake {
    COORDENADA corpo[MAX_SNAKE];
    char direcao;
    int tamanho;
} SNAKE;

typedef struct tunel {
    COORDENADA pos;
    int id;
    char direcao;
    int id_saida;
    int cenario;
} TUNEL;

typedef struct score {
    char nome[MAX_NOME + 1];
    int pontuacao;
} SCORE;

typedef struct config {
    int velocidade_inicial;
    int maxtamanho;
    int maxitens;
} CONFIG;


void limpa_linha(int linha, int x_ini, int x_fim, int cor);
void limpa_retangulo(int y_ini, int y_fim, int x_ini, int x_fim, int cor);
void salva_config(CONFIG opcoes);
int carrega_config(CONFIG *opcoes);
void cria_arquivo_tuneis();
int carrega_score(SCORE *scores);
void display_high_scores();
void ordena_score(SCORE *scores);
void insere_score(SCORE *scores, SCORE novo_score);
int salva_scores(SCORE *scores);
void display_menu(char items_menu[NUM_OPCOES][MAXSIZE_STRINGS_MENU], int selecionado);
void atualiza_menu(char items_menu[NUM_OPCOES][MAXSIZE_STRINGS_MENU], int selecionado, int old_selecionado);
void controla_menu(int *score, int *num_cenario, CONFIG *opcoes);
void display_menu_opcoes(char items_menu[NUM_OPCOES_CONFIG][MAXSIZE_STRINGS_MENU], int selecionado, CONFIG *opcoes);
void atualiza_menu_opcoes(char items_menu[NUM_OPCOES_CONFIG][MAXSIZE_STRINGS_MENU], int selecionado, int old_selecionado, CONFIG *opcoes);
void controla_menu_opcoes(CONFIG *opcoes);
void display_creditos();
void limpa_tela_menu();
void ini_display_menu();
void inicializa_snake(SNAKE *p_snake, int tamanho, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]);
void desenha_snake(int x_cabeca, int y_cabeca, int x_cauda, int y_cauda);
void desenha_cenario(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]);
void popula_cenario(char addr_cenario[LINHAS_CENARIO][COLUNAS_CENARIO], int numero_cenario);
void inicializa_cenario(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], int numero_cenario, TUNEL tuneis[MAX_TUNEIS], int *num_tuneis);
int inicializa_tuneis(TUNEL tuneis[MAX_TUNEIS], int numero_cenario);
void posiciona_tuneis_no_cenario(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL tuneis[MAX_TUNEIS], int num_tuneis);
void desenha_tuneis(TUNEL tuneis[MAX_TUNEIS], int num_tuneis);
void desenha_interface(int pontuacao, int velocidade, int tamanho, int cenario_atual);
void processa_input(SNAKE *p_snake, int *p_pause, int *p_encerrar, int *p_inicializar, /* tirar */ char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]);
int calcula_pontos(int velocidade, int tamanho, char item);
void processa_proximo_movimento(COORDENADA proxima_coord, int *p_pontuacao, int *p_velocidade, SNAKE *snake, int max_tamanho, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL *tuneis, int num_tuneis, int *p_encerrar, int num_cenario);
void processa_colisao(int *p_pontuacao, int *p_velocidade, int *p_tamanho, int *p_encerrar, char item, int max_tamanho, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL *tuneis, int num_tuneis, SNAKE *snake, COORDENADA *proxima_coord);
COORDENADA proxima_coordenada(COORDENADA coord_atual, char direcao);
void movimenta_snake(SNAKE *p_snake, COORDENADA prox_coord);
char escolhe_item();
void gera_novo_item(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]);
void fim_cenario(int result, int pontuacao, int num_cenario);
void processa_score_final(int pontuacao);
char pega_letra(int x);
void pega_nome(char *nome);
int roda_jogo(int *score, int *num_cenario, CONFIG *opcoes);


// main
/*
    Entrada do programa, inicializa configuracoes e chama o menu, que controla as funcionalidades do jogo
*/
int main() {
    CONFIG opcoes;
    int score = 0, num_cenario = 1; // Pontuacao do jogador e cenario atual precisam ser mantidos atraves das partidas

    // Inicializa a estrutura com as configuracoes do jogo
    carrega_config(&opcoes);

    // Seed para numeros aleatorios
    srand(time(0));

    // Inicializa o menu que controla o jogo
    controla_menu(&score, &num_cenario, &opcoes);

    // Jogo encerrado, volta as cores para o padrao do terminal
    textbackground(BLACK);
    clrscr();
    textcolor(WHITE);

    return 0;
}

// limpa_linha
/*
    Funcao auxiliar que preenche uma linha na tela com a cor de fundo passada
*/
void limpa_linha(int linha, int x_ini, int x_fim, int cor) {
    int i;

    textbackground(cor);
    for ( i=x_ini ; i < x_fim ; i++) {
        putchxy(i, linha, ' ');
    }

}

// limpa_retangulo
/*
    Funcao auxiliar que preenche um retangulo na tela com a cor de fundo passada
*/

void limpa_retangulo(int y_ini, int y_fim, int x_ini, int x_fim, int cor) {
    int i;

    for (i = y_ini; i < y_fim; i++) {
        limpa_linha(i, x_ini, x_fim, cor);
    }

}

// display_menu
/*
    Inicializa o menu na tela
*/
void display_menu(char items_menu[NUM_OPCOES][MAXSIZE_STRINGS_MENU], int selecionado) {
    int i;

    textbackground(BROWN);
    clrscr();
    ini_display_menu();
    for (i = 0; i < NUM_OPCOES; i++) {
        if (i == selecionado) {
            textbackground(BLACK);
            textcolor(LIGHTGREEN);
        }
        cputsxy(( MAX_X_TELA - strlen(items_menu[i]))/2, LINHA_INICIO_MENU + i, items_menu[i]);
        if (i == selecionado) {
            textbackground(BROWN);
            textcolor(BLACK);
        }
    }
}

// atualiza_menu
/*
    Redesenha na tela apenas o item do menu selecionado e o recem de-selecionado
*/
void atualiza_menu(char items_menu[NUM_OPCOES][MAXSIZE_STRINGS_MENU], int selecionado, int old_selecionado) {
    int i;


    for (i = 0; i < NUM_OPCOES; i++) {

        if (i == old_selecionado) { // Restaura visualizacao do previamente selecionado para o padrao
            textbackground(BROWN);
            textcolor(BLACK);
            cputsxy(( MAX_X_TELA - strlen(items_menu[i]))/2, LINHA_INICIO_MENU + i, items_menu[i]);
        }

        if (i == selecionado) { // Mostra o item selecionado com cor de fundo e texto diferentes
            textbackground(BLACK);
            textcolor(LIGHTGREEN);
            cputsxy(( MAX_X_TELA - strlen(items_menu[i]))/2, LINHA_INICIO_MENU + i, items_menu[i]);
        }
    }
    textbackground(BROWN);
    textcolor(BLACK);
}

// controla_menu
/*
    Logica principal do menu principal, controla as funcionalidades do jogo
*/
void controla_menu(int *score, int *num_cenario, CONFIG *opcoes) {
    char items_menu[NUM_OPCOES][MAXSIZE_STRINGS_MENU] = {"   NOVO JOGO  ", "  HIGH SCORES ", "    OPCOES    ", "   CREDITOS   ", "     SAIR     "};
    int encerrar = 0, selecionado = 0, op, result, old_selecionado;
    display_menu(items_menu, selecionado);

    while (!encerrar) {
        if (kbhit()) {
            op = getch();

            if (op == TECLADO_ESTENDIDO) {
                switch(getch()) {
                    case ASCII_CIMA:
                        old_selecionado = selecionado;
                        selecionado--;
                        if (selecionado < 0) selecionado = NUM_OPCOES - 1;
                        selecionado = selecionado % NUM_OPCOES;
                        atualiza_menu(items_menu, selecionado, old_selecionado);
                        break;
                    case ASCII_BAIXO:
                        old_selecionado = selecionado;
                        selecionado++;
                        selecionado = selecionado % NUM_OPCOES;
                        atualiza_menu(items_menu, selecionado, old_selecionado);
                        break;
                    default:
                        break;
                }
            } else if (op == ASCII_ENTER) {
                switch (selecionado) {
                    case NOVO_JOGO:
                        *score = 0; // Novo jogo, score zerado
                        result = 0;
                        do {
                            result = roda_jogo(score, num_cenario, opcoes);
                        } while (result == CENARIO_COMPLETO && *num_cenario != 4);
                        processa_score_final(*score); // Fim de jogo, verifica se entrou no top ten
                        *num_cenario = 1; // Proximo novo jogo inicializa no primeiro cenario
                        break;
                    case HIGH_SCORES:
                        display_high_scores();
                        break;
                    case OPCOES:
                        controla_menu_opcoes(opcoes);
                        break;
                    case CREDITOS:
                        display_creditos();
                        break;
                    case SAIR:
                        encerrar = 1;
                        break;
                }
                display_menu(items_menu, selecionado); // Voltando de uma tela diferente, necessario reinicializar o menu na tela
            } else if (op == ASCII_ESC) {
                encerrar = 1;
            }

        }

    }

}

// converte_index_menu_para_valor_config
/*
    Funcao auxiliar para display_menu_opcoes, recebe o index de uma opcao no array do menu
    e converte para o valor da opcao nas configuracoes (apenas para display)
*/
int converte_index_menu_para_valor_config(int index, CONFIG opcoes) {
    switch(index) {
        case MENU_CONFIG_VELOCIDADEINICIAL:
            return opcoes.velocidade_inicial;
            break;
        case MENU_CONFIG_MAXTAMANHO:
            return opcoes.maxtamanho;
            break;
        case MENU_CONFIG_MAXITENS:
            return opcoes.maxitens;
            break;
        default:
            return 0;
            break;
    }
}

// display_menu_opcoes
/*
    Inicializa o menu de opcoes na tela
*/
void display_menu_opcoes(char items_menu[NUM_OPCOES_CONFIG][MAXSIZE_STRINGS_MENU], int selecionado, CONFIG *opcoes) {
    char str_opcao[MAXSIZE_STRINGS_MENU + 3]; // 3 espacos extra para valor das opcoes
    int i;

    textbackground(BROWN);
    clrscr();
    ini_display_menu();
    for (i = 0; i < NUM_OPCOES_CONFIG; i++) {
        if (i == selecionado) { // Display especifico para item selecionado
            textbackground(BLACK);
            textcolor(LIGHTGREEN);
        }

        if (i != MENU_CONFIG_VOLTAR) {
            sprintf(str_opcao, "%s%3d", items_menu[i], converte_index_menu_para_valor_config(i, *opcoes));
        } else {
            strcpy(str_opcao, items_menu[i]);
        }

        cputsxy(COLUNA_INICIO_MENU_OPCOES, LINHA_INICIO_MENU + i, str_opcao);

        if (i == selecionado) { // Retorna display para o estado normal
            textbackground(BROWN);
            textcolor(BLACK);
        }
    }

}

// atualiza_menu_opcoes
/*
    Redesenha na tela apenas o item do menu selecionado e o recem de-selecionado, para o menu de opcoes
*/
void atualiza_menu_opcoes(char items_menu[NUM_OPCOES_CONFIG][MAXSIZE_STRINGS_MENU], int selecionado, int old_selecionado, CONFIG *opcoes) {
    char str_opcao[MAXSIZE_STRINGS_MENU + 3]; // 3 espacos extra para valor das opcoes
    int i;

    for (i = 0; i < NUM_OPCOES_CONFIG; i++) {

        if (i == old_selecionado) { // Atualiza na tela o que estava previamente selecionado
            textbackground(BROWN);
            textcolor(BLACK);

            if (i != MENU_CONFIG_VOLTAR) {
                sprintf(str_opcao, "%s%3d", items_menu[i], converte_index_menu_para_valor_config(i, *opcoes));
            } else {
                strcpy(str_opcao, items_menu[i]);
            }

            cputsxy(COLUNA_INICIO_MENU_OPCOES, LINHA_INICIO_MENU + i, str_opcao);
        }

        if (i == selecionado) { // Atualiza na tela o atualmente selecionado
            textbackground(BLACK);
            textcolor(LIGHTGREEN);
            if (i != MENU_CONFIG_VOLTAR) {
                sprintf(str_opcao, "%s%3d", items_menu[i], converte_index_menu_para_valor_config(i, *opcoes));
            } else {
                strcpy(str_opcao, items_menu[i]);
            }

            cputsxy(COLUNA_INICIO_MENU_OPCOES, LINHA_INICIO_MENU + i, str_opcao);
        }

        textbackground(BROWN); // Volta para o display padrao
        textcolor(BLACK);

    }

}

// controla_menu
/*
    Logica principal do menu de opcoes, controla as configuracoes do jogo
*/
void controla_menu_opcoes(CONFIG *opcoes) {
    char items_menu[NUM_OPCOES_CONFIG][MAXSIZE_STRINGS_MENU] = {"VELOCIDADE\t", "MAX TAMANHO\t", "MAX ITENS\t", "VOLTAR"};
    int voltar = 0, selecionado = 0, old_selecionado, alterou_config = 0, op;
    display_menu_opcoes(items_menu, selecionado, opcoes);

    while (!voltar) {
        if (kbhit()) {
            op = getch();

            if (op == TECLADO_ESTENDIDO) {
                old_selecionado = selecionado;
                switch(getch()) {
                    case ASCII_CIMA:
                        selecionado--;
                        if (selecionado < 0) selecionado = NUM_OPCOES_CONFIG - 1 ;
                        selecionado = selecionado % NUM_OPCOES_CONFIG;
                        break;
                    case ASCII_BAIXO:
                        selecionado++;
                        selecionado = selecionado % NUM_OPCOES_CONFIG;
                        break;
                    case ASCII_DIREITA:
                        switch(selecionado) {
                            case 0: // Velocidade Inicial
                                if (opcoes->velocidade_inicial < MAX_VELOCIDADEINICIAL) {
                                    opcoes->velocidade_inicial += 1;
                                    alterou_config = 1;
                                }
                                break;
                            case 1: // MaxTamanho
                                if (opcoes->maxtamanho < MAX_MAXTAMANHO) {
                                    opcoes->maxtamanho += 1;
                                    alterou_config = 1;
                                }
                                break;
                            case 2: // MaxItens
                                if (opcoes->maxitens < MAX_MAXITENS) {
                                    opcoes->maxitens += 1;
                                    alterou_config = 1;
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case ASCII_ESQUERDA:
                        switch(selecionado) {
                            case 0: // Velocidade Inicial
                                if (opcoes->velocidade_inicial > MIN_VELOCIDADEINICIAL) {
                                    opcoes->velocidade_inicial -= 1;
                                    alterou_config = 1;
                                }
                                break;
                            case 1: // MaxTamanho
                                if (opcoes->maxtamanho > MIN_MAXTAMANHO) {
                                    opcoes->maxtamanho -= 1;
                                    alterou_config = 1;
                                }
                                break;
                            case 2: // MaxItens
                                if (opcoes->maxitens > MIN_MAXITENS) {
                                    opcoes->maxitens -= 1;
                                    alterou_config = 1;
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
                atualiza_menu_opcoes(items_menu, selecionado, old_selecionado, opcoes);
            } else if (op == ASCII_ENTER) {
                switch (selecionado) {
                    case MENU_CONFIG_VOLTAR:
                        voltar = 1;
                        break;
                    default:
                        break;
                }
            } else if (op == ASCII_ESC) {
                voltar = 1;
            }

            if (alterou_config) {
                salva_config(*opcoes);
            }

            alterou_config = 0; // reseta para nao ficar salvando sempre.

        }
    }
}

// display_creditos
/*
    Mostra a tela de creditos
*/
void display_creditos() {
    int i, linhas;
    char creditos[][MAX_X_TELA] = {"Desenvolvido por Tiago Ceccon e Manuel Micas.",
                           "Para a cadeira de Algoritmos E Programacao (INF01202)",
                           "do curso de Ciencia da Computacao da UFRGS.",
                           "2017-01"};


    limpa_tela_menu();

    linhas = sizeof(creditos)/sizeof(creditos[0]);
    for (i = 0; i < linhas; i++) {
        cputsxy((MAX_X_TELA - strlen(creditos[i]))/2, LINHA_INICIO_MENU + i, creditos[i]); // Coloca linha (mais ou menos) centralizada na tela
    }

    textbackground(BLACK);
    textcolor(LIGHTGREEN);
    cputsxy(COLUNA_INICIO_MENU_OPCOES, LINHA_INICIO_MENU+i+2, "  VOLTAR  ");
    textbackground(BROWN);
    textcolor(BLACK);
    gotoxy(42, LINHA_INICIO_MENU+i+2); // x=42 apenas para o cursos ficar abaixo da letra R do "VOLTAR"

    while(getch() != ASCII_ENTER);
}

// display_high_scores
/*
    Mostra a tela com o ranking das dez melhores pontuacoes
*/
void display_high_scores() {
    SCORE scores[NUM_HIGH_SCORES];
    int i = 0;
    char str_score[MAXSIZE_STRING_HIGHSCORES];

    carrega_score(scores);
    ordena_score(scores);

    for(i = 0; i < NUM_HIGH_SCORES; i++) {
        switch(i) {
            case 0:
                textbackground(LIGHTGREEN);
                textcolor(WHITE);
                break;
            case 1:
                textbackground(CYAN);
                break;
            case 2:
                textbackground(GREEN);
                break;
            default:
                textbackground(BROWN);
                textcolor(BLACK);
                break;
        }
        sprintf(str_score, " %s\t%7d ", scores[i].nome, scores[i].pontuacao);
        cputsxy(COLUNA_INICIO_HIGH_SCORES, LINHA_INICIO_HIGH_SCORES+i, str_score);
    }

    textbackground(BLACK);
    textcolor(LIGHTGREEN);
    cputsxy(COLUNA_INICIO_HIGH_SCORES + 4, LINHA_INICIO_HIGH_SCORES+i+1, "  VOLTAR  "); // +4 para ficar visualmente um pouco mais centralizado
    textbackground(BROWN);
    textcolor(BLACK);
    gotoxy(41, LINHA_INICIO_HIGH_SCORES+i+1); // x=41 para o cursos ficar embaixo da letra R

    while(getch() != ASCII_ENTER);
}

// limpa_tela_menu
/*
    Funcao auxiliar para limpar a area do menu na tela
*/
void limpa_tela_menu() {
    limpa_retangulo(LINHA_INICIO_MENU, MAX_Y_TELA, 2, MAX_X_TELA, BROWN); // x_ini = 2 para nao apagar a moldura da tela na primeira coluna
}

// ini_display_menu
/*
    Inicializa a parte estatica do menu na tela
*/
void ini_display_menu() {
    int i, j;

    // Nome do jogo na parte superior do menu
    char tela[][MAX_X_TELA] = {
                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"10000000000000000000011111001111011001111100110011001111100000000000000000000001"},
                            {"10000000000000000000011000001111011001101100110110001100000000000000000000000001"},
                            {"10000000000000000000011111001101011001111100111100001111100000000000000000000001"},
                            {"10000000000000000000000011001101111001101100110110001100000000000000000000000001"},
                            {"10000000000000000000011111001101111001101100110011001111100000000000000000000001"},
                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"}};

    // Desenha moldura
    textbackground(GREEN);
    limpa_linha(1, 1, MAX_X_TELA+1, GREEN); // Primeira linha da tela, prompt inicia contagem em 1
    limpa_linha(MAX_Y_TELA, 1, MAX_X_TELA+1, GREEN); // Ultima linha da tela, prompt inicia contagem em 1
    for (i = 1; i < MAX_Y_TELA+1; i++) { // Preenche primeira e ultima coluna da tela
        putchxy(1, i, ' ');
        putchxy(MAX_X_TELA, i, ' ');
    }
    gotoxy(1,1);

    // Desenha titulo
    textbackground(BROWN);
    for (i = 1; i <= (MAX_Y_TELA-LINHA_INICIO_MENU); i++) {
        for (j = 0; j < MAX_X_TELA; j++) {
            if (tela[i][j] == '1') {
                textbackground(GREEN);
                putchxy(j+OFFSET_X, i+OFFSET_Y, ' ');
            } else {
                textbackground(BROWN);
                putchxy(j+OFFSET_X, i+OFFSET_Y, ' ');
            }
        }
    }
    textbackground(BROWN);
    gotoxy(1,1); // Volta o cursor para o início da tela
}

// carrega_config
/*
    Carrega configuracoes do arquivo binario e preenche a struct passada por referencia
    Caso haja erro ao abrir arquivo, seta um conjunto padrao de configuracoes
*/
int carrega_config(CONFIG *opcoes) {
    FILE *arq;

    if (arq = fopen(FILENAME_CONFIG, "rb")) {
        fread(opcoes, sizeof(CONFIG), 1, arq);
        return 1;
    } else {
        opcoes->velocidade_inicial = VELOCIDADEINICIAL_PADRAO;
        opcoes->maxtamanho = MAXTAMANHO_PADRAO;
        opcoes->maxitens = MAXITENS_PADRAO;
        return 0;
    }

}

// salva_config
/*
    Salva configuracao em arquivo binario
*/
void salva_config(CONFIG opcoes) {
    FILE *arq;

    arq = fopen(FILENAME_CONFIG, "wb");

    fwrite(&opcoes, sizeof(CONFIG), 1, arq);

    fclose(arq);

}

// carrega_score
/*
    Preenche um array com as 10 maiores pontuacoes salvas no arquivo
    ou, caso o arquivo nao seja encontrado, inicializa tudo com 0
*/
int carrega_score(SCORE *scores) {
    FILE *arq;
    SCORE buf;
    int i = 0;

    if (arq = fopen(FILENAME_HIGH_SCORES, "r")) {

        while (!feof(arq) && i < NUM_HIGH_SCORES) {
            if (fscanf(arq, "%d,%s", &buf.pontuacao, &buf.nome) != NULL) {
                scores[i].pontuacao = buf.pontuacao;
                strcpy(scores[i].nome, buf.nome);
                i++;
            }
        }

        fclose(arq);

    } else {
        for (i = 0; i < NUM_HIGH_SCORES; i++) {
            strcpy(scores[i].nome, "AAA");
            scores[i].pontuacao = 0;
        }
        return 1; // Erro ao abrir o arquivo, tudo zerado
    }

    return 0; // Tudo ok
}

// ordena_scores
/*
    Garante que um array de scores esteja ordenado em ordem decrescente,
    caso o array fornecido nao esteja, chama a funcao que aplica selection sort
*/
void ordena_score(SCORE *scores) {
    int i = 0, ordenado = 1;

    while(i < NUM_HIGH_SCORES - 1 && ordenado) {
        if (scores[i].pontuacao < scores[i+1].pontuacao) {
            ordenado = 0;
        }
        i++;
    }

    if (!ordenado) {
        selection_sort_score(scores, 0, NUM_HIGH_SCORES-1);
        salva_scores(scores);
    }

}

// separa_pivo_score: funcao AUXILIAR para o selection sort
int separa_pivo_score(SCORE * scores, int p, int r) {
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

    return j;
}

// selection_sort_score
/*
    Ordena um array de scores
*/
void selection_sort_score(SCORE * scores, int inicio, int fim) {
    int j;
    if (inicio < fim) {

        j = separa_pivo_score(scores, inicio, fim);

        selection_sort_score(scores, inicio, j-1);

        selection_sort_score(scores, j+1, fim);

    }
}

// insere_score
/*
    Dado um array de scores ordenado e um novo score, o insere no array
*/
void insere_score(SCORE *scores, SCORE novo_score){
    int i, j; //, index_colocar = -1;

    // Buscando posicao para inserir
    i = 0;
    while ((scores[i].pontuacao > novo_score.pontuacao) && (i < NUM_HIGH_SCORES)) {
        i++;
    }

    // Se entrar na lista, insere na posicao correta
    if (i < NUM_HIGH_SCORES) {
        for (j = NUM_HIGH_SCORES - 1; j > i ; j-- ) {
            strcpy(scores[j].nome, scores[j-1].nome);
            scores[j].pontuacao = scores[j-1].pontuacao;
        }
        strcpy(scores[i].nome, novo_score.nome);
        scores[i].pontuacao = novo_score.pontuacao;
    }

}

// salva_scores
/*
    Grava um array de scores no arquivo, no formato "pontuacao,nome"
*/
int salva_scores(SCORE *scores) {
    FILE *arq;
    int i;

    if (arq = fopen(FILENAME_HIGH_SCORES, "w")) {

        for (i = 0; i < NUM_HIGH_SCORES; i++) {
            if (!(fprintf(arq, "%d,%s\n", scores[i].pontuacao, scores[i].nome))) {
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

// display_scores: funcao auxiliar para DEBUG
/*
   Mostra um array de scores na tela com formatacao arbitraria para debug
*/
void display_scores(SCORE *scores, int num_scores) {
    int i;

    printf("========\nSCORES:\n\n");

    for (i = 0; i < num_scores; i++) {
        printf("%s\t%d\n", scores[i].nome, scores[i].pontuacao);
    }

    printf("========\n");

}

// inicizaliza_snake
/*
    Inicializa a estrutura da cobra e faz o desenho inicial na tela.
*/
void inicializa_snake(SNAKE *p_snake, int tamanho, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]) {
    int i;

    p_snake->tamanho = tamanho;

    p_snake->direcao = 'd';


    textbackground(BACK_SNAKE);
    for (i = 0; i < tamanho; i++) {
        p_snake->corpo[i].x = INI_X_SNAKE - i;
        p_snake->corpo[i].y = INI_Y_SNAKE;
        cenario[p_snake->corpo[i].y - 2][p_snake->corpo[i].x - 1] = 'B';
        putchxy(p_snake->corpo[i].x, p_snake->corpo[i].y, ' ');
    }

}

// desenha_snake
/*
    Atualiza representacao da cobra na tela, desenhando a cabeca e apagando a cauda
*/
void desenha_snake(int x_cabeca, int y_cabeca, int x_cauda, int y_cauda) {
    textbackground(BACK_SNAKE);
    putchxy(x_cabeca, y_cabeca, ' ');
    textbackground(BACK_CENARIO);
    putchxy(x_cauda, y_cauda, ' ');
    textbackground(BACK_CENARIO);
}

// desenha_cenario
/*
    Inicializa o cenario na tela
*/
void desenha_cenario(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]) {
    int i, j;

    textbackground(BROWN);
    textcolor(BLACK);
    for (i = 0; i < LINHAS_CENARIO; i++) {
        for (j = 0; j < COLUNAS_CENARIO; j++) {
            if (cenario[i][j] == '1') {
                putchxy(j+1, i+2, '|');
            } else {
                putchxy(j+1, i+2, ' ');
            }
        }
    }
    textbackground(BLACK);
    gotoxy(1,1); // Volta o cursor para o início da tela
}

// popula_cenario
/*
    Preenche a matriz do cenario com a leitura do arquivo de texto
    Caso nao encontre o arquivo, usa cenarios padroes arbitrarios
*/
void popula_cenario(char addr_cenario[LINHAS_CENARIO][COLUNAS_CENARIO], int numero_cenario) {
    int i, j;
    FILE *arq_mapa;
    char nome_arq[9];
    char buf[COLUNAS_CENARIO + 1];
    char cenario[NUM_CENARIOS][LINHAS_CENARIO][COLUNAS_CENARIO] = {{
                            {"1111111111111111111111111111111111111111111111111111111111111111111111111111111"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1111111111111111111111111111111111111111111111111111111111111111111111111111111"}},
                            {
                            {"1111111111111111111111111111111111111111111111111111111111111111111111111111111"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000010000000000000000000000000000000000001"},
                            {"1111111111111111111111111111111111111111111111111111111111111111111111111111111"}},
                            {
                            {"1111111111111111111111111111111111111111111111111111111111111111111111111111111"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000111111111111000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000001000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000001000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000001000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000001000000000000000000001"},
                            {"1000000000000000000000000011111111111110000000000000000001000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000001000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1000000000000000000000000000000000000000000000000000000000000000000000000000001"},
                            {"1111111111111111111111111111111111111111111111111111111111111111111111111111111"}}};

    sprintf(nome_arq, "map%d.txt", numero_cenario);
    if ((arq_mapa = fopen(nome_arq, "r")) != NULL) {

        for (i = 0; i < LINHAS_CENARIO; i++) {
            fgets(buf, COLUNAS_CENARIO + 1, arq_mapa);
            for (j = 0; j < COLUNAS_CENARIO; j++) {
                addr_cenario[i][j] = buf[j];
            }

        }
        fclose(arq_mapa);

    } else {

        for (i = 0; i < LINHAS_CENARIO; i++) {
            for (j = 0; j < COLUNAS_CENARIO; j++) {
                addr_cenario[i][j] = cenario[numero_cenario-1][i][j];
            }
        }

    }
}

// inicializa_cenario
/*
    Popula array do cenario, faz a inicializacao dele na tela e trata tuneis.
*/
void inicializa_cenario(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], int numero_cenario, TUNEL tuneis[MAX_TUNEIS], int *num_tuneis) {

    // Cenario
    popula_cenario(cenario, numero_cenario);
    desenha_cenario(cenario);

    // Tuneis
    *num_tuneis = inicializa_tuneis(tuneis, numero_cenario);
    posiciona_tuneis_no_cenario(cenario, tuneis, *num_tuneis);
    desenha_tuneis(tuneis, *num_tuneis);

}

// inicializa_tuneis
/*
    Inicializa o array de tuneis
*/
int inicializa_tuneis(TUNEL tuneis[MAX_TUNEIS], int numero_cenario){
    int tamanho = 0, tam_buff;
    TUNEL tun_buff;
    FILE *arq_tuneis;

    arq_tuneis = fopen(FILENAME_TUNEIS, "rb");

    while (!feof(arq_tuneis)) {
        tam_buff = fread(&tun_buff, sizeof(TUNEL), 1, arq_tuneis);

        if (tam_buff == 1 && tun_buff.cenario == numero_cenario) {
            tuneis[tamanho] = tun_buff;
            tamanho += tam_buff;
        }
    }

    fclose(arq_tuneis);

    return tamanho;

}

// posiciona_tuneis_no_cenario
/*
    Coloca os tuneis na matriz do cenario para a logica do jogo
*/
void posiciona_tuneis_no_cenario(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL tuneis[MAX_TUNEIS], int num_tuneis) {
    int i;

    for (i = 0; i < num_tuneis; i++) {
        cenario[tuneis[i].pos.y][tuneis[i].pos.x] = 'T';
    }
}


// desenha_tuneis
/*
    Desenha os tuneis na tela
*/
void desenha_tuneis(TUNEL tuneis[MAX_TUNEIS], int num_tuneis) {
    int i;
    char direcao;

    textcolor(BLACK);
    textbackground(BACK_CENARIO);
    for (i = 0; i < num_tuneis; i++) {
        // Determina caracter de acordo com a direcao de entrada do tunel
        switch(tuneis[i].direcao) {
            case 'b':
                direcao = '\x19';
                break;
            case 'c':
                direcao = '\x18';
                break;
            case 'e':
                direcao = '\x1b';
                break;
            case 'd':
                direcao = '\x1a';
                break;
            default:
                direcao = '0';
                break;
        }
        putchxy((tuneis[i].pos.x)+1, (tuneis[i].pos.y)+2, direcao); // Coloca tunel na tela
    }
}


// desenha_interface
/*
    Desenha a interface com as informacoes da partida
*/
void desenha_interface(int pontuacao, int velocidade, int tamanho, int cenario_atual) {
    char status[MAX_X_TELA];
    int i;

    // Todas as informacoes aparecem contanto que pontuacao seja menor do que 99999999, acima disso estoura o limite da tela
    sprintf(status, "Score: %d\tVelocidade: %d\t\tSNAKE\t\tTamanho: %d\tMapa: %d\n",  pontuacao, velocidade, tamanho, cenario_atual);
    textbackground(WHITE);
    for (i = 1; i <= MAX_X_TELA; i++) {
        putchxy(i, 1, ' ');
    }
    cputsxy(1,1,status);


}

// processa_input
/*
    Processa entradas do usuario durante a partida.
*/
void processa_input(SNAKE *p_snake, int *p_pause, int *p_encerrar, int *p_inicializar,/* tirar */ char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]) {
    int op, inicializado_agora = 0;

    if (kbhit()) {
            if (!(*p_inicializar)) {
                *p_inicializar = 1;
                inicializado_agora = 1;
                *p_pause = 0;
            }
            op = getch();

            if (op == TECLADO_ESTENDIDO /*-32*/) {
                switch(getch()) {
                    case ASCII_CIMA:
                        if (p_snake->direcao != 'b') {
                            p_snake->direcao = 'c';
                        }

                        break;
                    case ASCII_BAIXO:
                        if (p_snake->direcao != 'c') {
                            p_snake->direcao = 'b';
                        }
                        break;
                    case ASCII_DIREITA:
                        if (p_snake->direcao != 'e') {
                            p_snake->direcao = 'd';
                        }
                        break;
                    case ASCII_ESQUERDA:
                        if (p_snake->direcao != 'd') {
                            p_snake->direcao = 'e';
                        }
                        break;
                    default:
                        break;
                }

            } else if (op == ASCII_SPACEBAR) {
                if (*p_pause) {
                    *p_pause = 0;
                } else if (!inicializado_agora){ // Para evitar de pausar o jogo logo quando inicia, se primeira tecla apertada for espaco
                    *p_pause = 1;
                }
            } else if (op == ASCII_ESC) {
                *p_encerrar = USER_EXIT;
            } else if (op == 'w') {
                if (p_snake->direcao != 'b') {
                    p_snake->direcao = 'c';
                }
            } else if (op == 's') {
                if (p_snake->direcao != 'c') {
                    p_snake->direcao = 'b';
                }
            } else if (op == 'd') {
                if (p_snake->direcao != 'e') {
                    p_snake->direcao = 'd';
                }
            } else if (op == 'a') {
                if (p_snake->direcao != 'd') {
                    p_snake->direcao = 'e';
                }
            } else if (op == 'g') {
                if (p_snake->tamanho < MAX_SNAKE - 1) {
                    p_snake->tamanho++;
                }
            } else if (op == 'n') {
                gera_novo_item(cenario);
            }
        }
}

// calcula_pontos
/*
    Calcula quantos pontos o usuario deve receber ao pegar determinado item
*/
int calcula_pontos(int velocidade, int tamanho, char item) {
    int pts_base, pontos_obtidos;
    switch(item) {
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

    pontos_obtidos = pts_base * (tamanho / 5) * velocidade;

    return pontos_obtidos;
}

// processa_proximo_movimento
/*
    Controla a logica da movimentacao a cada turno da partida
*/
void processa_proximo_movimento(COORDENADA proxima_coord, int *p_pontuacao, int *p_velocidade, SNAKE *snake, int max_tamanho, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL *tuneis, int num_tuneis, int *p_encerrar, int num_cenario){
    char item_no_proximo_movimento = cenario[ proxima_coord.y-OFFSET_Y ][ proxima_coord.x-OFFSET_X ];

    if (item_no_proximo_movimento != '0') {
        processa_colisao(p_pontuacao, p_velocidade, &snake->tamanho, p_encerrar, item_no_proximo_movimento, max_tamanho, cenario, tuneis, num_tuneis, snake, &proxima_coord);
        desenha_interface(*p_pontuacao, *p_velocidade, snake->tamanho, num_cenario);
    }

    // Atualiza posicao da cobra na estrutura
    movimenta_snake(snake, proxima_coord);

    // Atualiza posicao da cobra na matriz do cenario
    cenario[ snake->corpo[0].y-OFFSET_Y ][ snake->corpo[0].x-OFFSET_X ] = 'B';
    cenario[ snake->corpo[snake->tamanho].y-OFFSET_Y ][ snake->corpo[snake->tamanho].x-OFFSET_X ] = '0';
}

// processa_colisao
/*
    Faz o processamento necessario quando o jogador pega um item
*/
void processa_colisao(int *p_pontuacao, int *p_velocidade, int *p_tamanho, int *p_encerrar, char item, int max_tamanho, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL *tuneis, int num_tuneis, SNAKE *snake, COORDENADA *proxima_coord) {
    COORDENADA coord_temp;

    switch(item) {
        case '1': // Obstaculo
        case 'B': // Corpo da cobra
            *p_encerrar = GAME_OVER;
            break;
        case 'C': // Comida
            *p_pontuacao += calcula_pontos(*p_velocidade, *p_tamanho, item);
            if (*p_tamanho < max_tamanho - 1) {
                *p_tamanho += 1;
            } else {
                *p_encerrar = CENARIO_COMPLETO; // Passa de cenario ao atingir tamanho maximo da cobra
            }
            gera_novo_item(cenario);
            break;
        case 'S': // Slower
            *p_pontuacao += calcula_pontos(*p_velocidade, *p_tamanho, item);
            gera_novo_item(cenario);
            if (*p_velocidade > MIN_VELOCIDADEINICIAL) {
                *p_velocidade -= 1;
            }
            break;
        case 'F': // Faster
            *p_pontuacao += calcula_pontos(*p_velocidade, *p_tamanho, item);
            gera_novo_item(cenario);
            if (*p_velocidade < MAX_VELOCIDADEINICIAL) {
                *p_velocidade += 1;
            }
            break;
        case 'V': // Skip = vitoria = cenario completo
            *p_pontuacao += calcula_pontos(*p_velocidade, *p_tamanho, item);
            *p_encerrar = CENARIO_COMPLETO;
            break;
        case 'T': // Tunel
            if (!entra_tunel(tuneis, proxima_coord, &snake->direcao, num_tuneis )) {
                coord_temp.x = proxima_coord->x+OFFSET_X;
                coord_temp.y = proxima_coord->y+OFFSET_Y;
                coord_temp = proxima_coordenada(coord_temp, snake->direcao);
                *proxima_coord = coord_temp;

                // Chama uma versao atualizada de si propria para processar o caso de haver um item significativo
                // logo na frente do tunel
                processa_colisao(p_pontuacao, p_velocidade, p_tamanho, p_encerrar, cenario[ proxima_coord->y-OFFSET_Y ][ proxima_coord->x-OFFSET_X ], max_tamanho, cenario, tuneis, num_tuneis, snake, proxima_coord);

            } else {
                *p_encerrar = GAME_OVER;
            }
            break;
        default:
            break;

    }
}

// busca_tunel
/*
    Encontra o tunel em uma determinada coordenada, retorna sua id no array
*/
int busca_tunel(TUNEL *tuneis, COORDENADA coord, int num_tuneis) {
    int i, i_encontrado = -1; //printf("\n\n\n%d\t%d\t%d\t%d", tuneis[0].pos.x, tuneis[0].pos.y, coord.x, coord.y); getch();

    for (i = 0; i < num_tuneis; i++) {
        if ((tuneis[i].pos.x == coord.x -OFFSET_X ) && (tuneis[i].pos.y == coord.y - OFFSET_Y)) { // Arrumar offsets nas representacoes das pos x, y de cobra e tunel
            i_encontrado = i;
        }
    }

    return i_encontrado;
}

// entra_tunel
/*
    Processa a logica da entrada em um tunel, returna 1 se entrou pela direcao errada, 0 se deu tudo certo
*/
int entra_tunel(TUNEL *tuneis, COORDENADA *corpo, char *direcao, int num_tuneis) {
    int i, novo_x, novo_y;
    char nova_direcao;

    i = busca_tunel(tuneis, *corpo, num_tuneis);

    if (*direcao != tuneis[i].direcao) {
        return 1; // Cobra entrou pela direcao errada, morreu
    }

    novo_x = tuneis[tuneis[i].id_saida].pos.x;
    novo_y = tuneis[tuneis[i].id_saida].pos.y;
    nova_direcao = tuneis[tuneis[i].id_saida].direcao;

    corpo->x = novo_x;
    corpo->y = novo_y;
    *direcao = nova_direcao;

    return 0; // Sucesso

}

// proxima_coordenada
/*
    Recebendo a coordenada atual da cabeca da cobra e sua direcao atual, retorna a proxima coordenada em que ela deve estar.
*/
COORDENADA proxima_coordenada(COORDENADA coord_atual, char direcao) {
    COORDENADA proxima_coord;

    switch(direcao) {
        case 'c':
            proxima_coord.x = coord_atual.x;
            proxima_coord.y = coord_atual.y - 1;
            break;
        case 'b':
            proxima_coord.x = coord_atual.x;
            proxima_coord.y = coord_atual.y + 1;
            break;
        case 'd':
            proxima_coord.x = coord_atual.x + 1;
            proxima_coord.y = coord_atual.y;
            break;
        case 'e':
            proxima_coord.x = coord_atual.x - 1;
            proxima_coord.y = coord_atual.y;
            break;
    }

    return proxima_coord;
}

// movimenta_snake
/*
    Dada a proxima coordenada da cabeca da cobra, atualiza todo o array de coordenadas.
*/
void movimenta_snake(SNAKE *p_snake, COORDENADA prox_coord) {
    int i;

    for (i=p_snake->tamanho; i > 0; i--) {
            p_snake->corpo[i].x = p_snake->corpo[i-1].x;
            p_snake->corpo[i].y = p_snake->corpo[i-1].y;
    }
    p_snake->corpo[0] = prox_coord;
}


// escolhe_item
/*
    Escolhe um item aleatoriamente e retorna um caracter correspondente.
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

// gera_novo_item
/*
    Cria um novo item e o coloca em uma posicao aleatoria no cenario que nao esteja ocupada
*/
void gera_novo_item(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]) {
    int novo_x, novo_y;
    char novo_item = escolhe_item();

    do {
        novo_y = ((int) (rand() / (double) RAND_MAX * (LINHAS_CENARIO - 2) )) + 1; // Ajusta a escolha do numero aleatorio para evitar
        novo_x = ((int) (rand() / (double) RAND_MAX * (COLUNAS_CENARIO - 3))) + 1; // testes nas extremidades (que sempre estao ocupadas com obstaculos)
    } while (cenario[novo_y][novo_x] != '0');

    cenario[novo_y][novo_x] = novo_item;
    putchxy(novo_x+OFFSET_X, novo_y+OFFSET_Y, novo_item);

}

// fim_cenario
/*
    Processa o final de uma partida
*/
void fim_cenario(int result, int pontuacao, int num_cenario) {
    char mensagem[MAXSIZE_MSGS_FIMCENARIO];
    char mensagem_pontuacao[MAXSIZE_MSGS_FIMCENARIO];
    int mostrar_pontuacao = 1;

    switch(result) {
        case GAME_OVER:
            sprintf(mensagem, "   GAME OVER   ");
            break;
        case CENARIO_COMPLETO:
            sprintf(mensagem, "CENARIO COMPLETO");
            if (num_cenario != NUM_CENARIOS) { // Nao finalizou o ultimo cenario
                mostrar_pontuacao = 0;
            }
            break;
        case USER_EXIT:
            sprintf(mensagem, "   VOCE SAIU   ");
            break;
        default:
            break;
    }

    limpa_retangulo(LINHA_INICIO_FIMCENARIO, LINHA_FIM_FIMCENARIO, COLUNA_INICIO_FIMCENARIO, COLUNA_FIM_FIMCENARIO, WHITE);

    textcolor(BLACK);
    cputsxy(COLUNA_MSG_FIMCENARIO, LINHA_MSG_FIMCENARIO, mensagem);
    if (mostrar_pontuacao) {
        sprintf(mensagem_pontuacao, "%s%8d", "PONTUACAO FINAL: ", pontuacao);
        cputsxy(COLUNA_PONTUACAO_FIMCENARIO, LINHA_PONTUACAO_FIMCENARIO, mensagem_pontuacao);
    }
    cputsxy(COLUNA_SAIR_FIMCENARIO, LINHA_SAIR_FIMCENARIO, "Aperte ENTER para sair.");

    while(getch() != ASCII_ENTER);
}

// processa_score_final
/*
    Verifica se a pontuacao final foi suficiente para entrar no ranking de High Scores.
    Em caso positivo, inicia o processo de insercao nele.
*/
void processa_score_final(int pontuacao){
    SCORE scores[NUM_HIGH_SCORES], novo_high_score;
    int i = 0, entra = 0;

    carrega_score(scores);

    while (i < NUM_HIGH_SCORES && !entra) {
        if (pontuacao > scores[i].pontuacao) {
            entra = 1;
        }
        i++;
    }

    if(entra) {
        novo_high_score.pontuacao = pontuacao;
        limpa_retangulo(LINHA_INICIO_ENTRAHIGHSCORE, LINHA_FIM_ENTRAHIGHSCORE, COLUNA_INICIO_ENTRAHIGHSCORE, COLUNA_FIM_ENTRAHIGHSCORE, WHITE);
        cputsxy(COLUNA_INICIO_ENTRAHIGHSCORE+5, LINHA_INICIO_ENTRAHIGHSCORE+1, "VOCE ENTROU NO TOP 10!!!");
        pega_nome(novo_high_score.nome);
        insere_score(scores, novo_high_score);
        salva_scores(scores);
    }

}

// pega_letra
/*
    Funcao auxiliar a pega_nome, usada apenas para pegar o nome de um jogador que tenha conseguido entrar
    para o ranking de melhores pontuacoes. Implementa uma escolha de letra atraves de selecao pela setas do teclado.
*/
char pega_letra(int x) {
    char letra = 'A';
    int op, fim = 0;

    putchxy(x, LINHA_NOME_HIGHSCORE, letra); // Mostra a letra atualmente selecionada
    gotoxy(x, LINHA_NOME_HIGHSCORE);

    while(!fim){

        if (kbhit()) {
            op = getch();
            if (op == TECLADO_ESTENDIDO) {
                switch(getch()) {
                    case ASCII_CIMA:
                        letra++; // Tratando char como int, facilita a operacao
                        if (letra > 'Z') { // Limita escolhas ao intervalo 'A-Z'
                            letra = 'A';
                        }
                        break;
                    case ASCII_BAIXO:
                        letra--;
                        if (letra < 'A') { // Idem acima
                            letra = 'Z';
                        }
                        break;
                }
                putchxy(x, LINHA_NOME_HIGHSCORE, letra); // Atualiza a letra na tela
                gotoxy(x, LINHA_NOME_HIGHSCORE);
            } else if(op == ASCII_ENTER) {
                fim = 1;
            }
        }

    }

    return letra;
}

// pega_nome
/*
    Pega o nome do jogador para entrar no ranking, preenchendo a string da estrutura
*/
void pega_nome(char *nome) {
    cputsxy(COLUNA_NOME_HIGHSCORE, LINHA_NOME_HIGHSCORE, "Nome: ");
    nome[0] = pega_letra(COLUNA_NOME_HIGHSCORE + 7); // Cada vez aumenta um para que as letras aparecam uma do lado da outra
    nome[1] = pega_letra(COLUNA_NOME_HIGHSCORE + 8);
    nome[2] = pega_letra(COLUNA_NOME_HIGHSCORE + 9);
    nome[3] = '\0';
    //fgets(nome, 4, stdin);
    fflush(stdin);
}

// roda_jogo
/*
    Logica principal do jogo, controla o processamento de uma partida do comeco ao fim
*/
int roda_jogo(int *score, int *num_cenario, CONFIG *opcoes) {
    // Inicializacao de variaveis
    char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], item_no_proximo_movimento;
    TUNEL tuneis[MAX_TUNEIS] = {0};
    int num_tuneis, encerrar = 0, pause = 1, inicializado = 0, op, i;
    int velocidade = opcoes->velocidade_inicial;
    SNAKE snake = {0};
    COORDENADA proxima_coord;

    // Inicio do processamento
    textbackground(BROWN);
    textcolor(BLACK);
    clrscr();

    inicializa_cenario(cenario, *num_cenario, tuneis, &num_tuneis);

    inicializa_snake(&snake, INI_TAM_SNAKE, cenario);

    desenha_interface(*score, velocidade, snake.tamanho, *num_cenario);

    textbackground(BROWN); // Garante que alteracoes no display nas funcoes anteriores nao interfiram
    textcolor(BLACK);

    // Inicializa os itens
    for(i = 0; i < opcoes->maxitens ; i++) {
        gera_novo_item(cenario);
    }

    // Loop principal do jogo
    while (!encerrar) {

        // Entradas do usuario
        processa_input(&snake, &pause, &encerrar, &inicializado, cenario);

        if (!pause) {

            proxima_coord = proxima_coordenada(snake.corpo[0], snake.direcao);

            item_no_proximo_movimento = cenario[ proxima_coord.y-OFFSET_Y ][ proxima_coord.x-OFFSET_X ];

            // Parte logica da movimentacao
            processa_proximo_movimento(proxima_coord, score, &velocidade, &snake, opcoes->maxtamanho, cenario, tuneis, num_tuneis, &encerrar, *num_cenario);

            // Parte visual da movimentacao, de acordo com a versao atualizada da parte logica
            desenha_snake(snake.corpo[0].x, snake.corpo[0].y, snake.corpo[snake.tamanho].x, snake.corpo[snake.tamanho].y);

        }

        // Controle da velocidade
        Sleep(UM_SEGUNDO_EM_MS/velocidade);

    }

    fim_cenario(encerrar, *score, *num_cenario);

    if (encerrar == CENARIO_COMPLETO) {
        *num_cenario += 1;
        *score += BONUS_COMPLETA_CENARIO; // Pontuacao extra ao completar cenario
    }

    return encerrar;
}
