#include<stdio.h>
#include<conio2.h>
#include<windows.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>


#define MAX_X_TELA 80
#define MAX_Y_TELA 25
#define NUM_OPCOES 5
#define LINHA_INICIO_MENU 15
#define LINHA_INICIO_HIGH_SCORES 12

#define NOVO_JOGO 0
#define HIGH_SCORES 1
#define OPCOES 2
#define CREDITOS 3
#define SAIR 4

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

#define PTS_BASE_COMIDA 2
#define PTS_BASE_SLOWER 1
#define PTS_BASE_FASTER 3
#define PTS_BASE_SKIP 40

#define NUM_CENARIOS 3
#define LINHAS_CENARIO 24
#define COLUNAS_CENARIO 80

#define MAX_TUNEIS 5

#define FILENAME_HIGH_SCORES "scores.txt"
#define MAX_NOME 3
#define NUM_HIGH_SCORES 10


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


void cria_arquivo_tuneis();
int carrega_score(SCORE *scores);
void display_high_scores();
void ordena_score(SCORE *scores);
void insere_score(SCORE *scores, SCORE novo_score);
int salva_scores(SCORE *scores);
void display_menu(int selecionado);
void controla_menu(int opts[10]);
void display_menu_opcoes(int selecionado, int opts[10]);
void controla_menu_opcoes(int opts[10]);
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
void fim_cenario(int result);
void processa_score_final(int pontuacao);
char pega_letra(int x);
void pega_nome(char *nome);
int roda_jogo(int opts[10]);

/*
=====================================
TODO: Passos para movimentar a SNAKE

;; Prox_Coord: Coord Char -> Coord
-> Prox_Coord()
V

;; "Colidiu": ? -> ?
-> "Colidiu"()  "processa_movimento" "processa_passo"
V

;; Mov._Snake: Snake Coord -> Void
-> Mov._Snake()
V

=====================================
TODO:
logica da velocidade V
- usar pulsos para separar velocidade da cobra do input do usuario?

=====================================
TODO:
jogo deve comecar pausado, cobra deve comecar com 5 posicoes ocupadas
V
- provavelmente vai precisar de um "inicializa_snake" ou algo do genero
V

=====================================
TODO:
refatorar o input do usuario, separar do movimento em si
V
- tirar debug/cheats ?

=====================================

=====================================
TODO:
popula_cenario deve receber o numero exato do cenario
apos isso, ajustar na funcao (atualmente esta decrementando o numero para compatibilidade)
V
- o que fazer quando nao encontrar arquivo do mapa?
V

=====================================
TODO:
desenha_cenario deve jah receber a matriz do cenario
e soh desenhar, sem chamar popula_cenario redundantemente
V
- limpar coisas que eram do inicio do desenvolvimento
V

=====================================
TODO:
trocar todas as ocorrencias do cenario para usar 24 linhas
V
(e talvez 79 colunas)
X

=====================================
TODO:
verificar logica de gera_novo_item (para evitar de testar as bordas do cenario)
V

=====================================
TODO:
inicializa_cenario?
V

=====================================
TODO:
verificar why nao esta zerando toda a tela do prompt, deixando 4 linhas na parte superior a cada partida
V


=====================================

=====================================
TODO:
toda a parte dos tuneis
- carregar tuneis de arquivo (armazenar num_cenario na estrutura tunel? V)
V
- fazer logica da 'colisao'
V
- - encontrar tunel
V
- - movimentar snake alem do tunel
V
- determinar posicao fixa dos tuneis nos cenarios respectivos
V

=====================================
TODO:
toda a parte de scores
- estrutura score
V
- carregar/ordenar/salvar score (pegar das aulas praticas?)
V
- integrar scores ao menu
V
- cores diferentes para o top 3 ??
V
- pegar letras individualmente
V

=====================================
TODO:
config deve ser uma struct com campos OPCAO
OPCAO tem valor atual, valor minimo e valor maximo

=====================================
TODO:
refazer TODA a parte visual do menu
- deixar melhor estruturado
- integrar com struct CONFIG e OPCAO
- redenhar apenas partes necessarias

=====================================
TODO:
dividir em varios arquivos
- io
- game
- file_management
- ?

=====================================

*/




int main() {
    //int velocidade = 1, tamanho = 5, score = 0, num_cenario = 1;
    int opts[10] = {0};
    opts[I_OPTS_VELOCIDADE] = 10;
    opts[I_OPTS_MAXTAMANHO] = 50;
    opts[I_OPTS_MAXITENS] = 5;
    opts[I_OPTS_NUMCENARIO] = 1;
    opts[I_OPTS_SCORE] = 0;

    srand(time(0));

    //display_menu(2);

    controla_menu(opts);
    //ini_display_menu();

    //display_creditos();

    // Jogo encerrado, volta as cores para o padrao do terminal
    //textbackground(0);
    textbackground(BLACK);
    clrscr();
    //textcolor(15);
    textcolor(WHITE);

    //getchar();
    return 0;
}

void display_menu(int selecionado) {
    char items_menu[NUM_OPCOES][20] = {"   NOVO JOGO  ", "  HIGH SCORES ", "    OPCOES    ", "   CREDITOS   ", "     SAIR     "};
    int i;

//    textbackground(15);
//    textcolor(1);
    //cputsxy(10, 10, teststring);
    //textbackground(6);
    textbackground(BROWN);
    clrscr();
    ini_display_menu();
    for (i = 0; i < NUM_OPCOES; i++) {
        if (i == selecionado) {
//            textbackground(0);
//            textcolor(2);
            textbackground(BLACK);
            textcolor(LIGHTGREEN);
        }
        cputsxy(( MAX_X_TELA - strlen(items_menu[i]))/2, LINHA_INICIO_MENU + i, items_menu[i]);
        if (i == selecionado) {
//            textbackground(6);
//            textcolor(0);
            textbackground(BROWN);
            textcolor(BLACK);
        }
    }
}

void controla_menu(int opts[10]) {
    int encerrar = 0, selecionado = 0, op, result;
    display_menu(selecionado);

    while (!encerrar) {
        if (kbhit()) {
            op = getch();

            if (op == 224) {
                switch(getch()) {
                    case ASCII_CIMA:
                        selecionado--;
                        if (selecionado < 0) selecionado = NUM_OPCOES - 1;
                        selecionado = selecionado % NUM_OPCOES;
                        break;
                    case ASCII_BAIXO:
                        selecionado++;
                        selecionado = selecionado % NUM_OPCOES;
                        break;
                    default:
                        break;
                }
            } else if (op == 13) {
                switch (selecionado) {
                    case NOVO_JOGO:
                        opts[I_OPTS_SCORE] = 0;
                        result = 0;
                        do {
                            result = roda_jogo(opts);
                        } while (result == CENARIO_COMPLETO && opts[I_OPTS_NUMCENARIO] != 4);
                        processa_score_final(opts[I_OPTS_SCORE]);
                        opts[I_OPTS_NUMCENARIO] = 1;

                        break;
                    case HIGH_SCORES:
                        display_high_scores();
                        break;
                    case OPCOES:
                        controla_menu_opcoes(opts);
                        break;
                    case CREDITOS:
                        display_creditos();
                        break;
                    case SAIR:
                        encerrar = 1;
                        break;
                }
                //display_creditos();
            } else if (op == 27) {
                encerrar = 1;
            }

            display_menu(selecionado);
        }

    }
    clrscr();
    printf("Bye");
}

void display_menu_opcoes(int selecionado, int opts[10]) {
    char items_menu[5][20] = {"VELOCIDADE\t", "MAX TAMANHO\t", "MAX ITENS\t", "CENARIO\t", "VOLTAR"};
    char str_opcao[23];
    int i;

//    textbackground(15);
//    textcolor(1);
    //cputsxy(10, 10, teststring);
//    textbackground(6);
    textbackground(BROWN);
    clrscr();
    ini_display_menu();
    for (i = 0; i < 5; i++) {
        if (i == selecionado) {
//            textbackground(0);
//            textcolor(2);
            textbackground(BLACK);
            textcolor(LIGHTGREEN);
        }
        if (i != 4) {
            sprintf(str_opcao, "%s%3d", items_menu[i], opts[i]);
        } else {
            strcpy(str_opcao, items_menu[i]);
        }
        //cputsxy(35, 15 + i, items_menu[i]);
        cputsxy(35, 15 + i, str_opcao);
        if (i == selecionado) {
//            textbackground(6);
//            textcolor(0);
            textbackground(BROWN);
            textcolor(BLACK);
        }
    }

}

void controla_menu_opcoes(int opts[10]) {
    int voltar = 0, selecionado = 0, op;
    display_menu_opcoes(selecionado, opts);

    while (!voltar) {
        if (kbhit()) {
            op = getch();

            if (op == 224) {
                switch(getch()) {
                    case ASCII_CIMA:
                        selecionado--;
                        if (selecionado < 0) selecionado = 4;
                        selecionado = selecionado % 5;
                        break;
                    case ASCII_BAIXO:
                        selecionado++;
                        selecionado = selecionado % 5;
                        break;
                    case ASCII_DIREITA:
                        switch(selecionado) {
                            case 0: // Velocidade Inicial
                                if (opts[I_OPTS_VELOCIDADE] < 10) {
                                    opts[I_OPTS_VELOCIDADE] += 1;
                                }
                                break;
                            case 1: // MaxTamanho
                                if (opts[I_OPTS_MAXTAMANHO] < 100) {
                                    opts[I_OPTS_MAXTAMANHO] += 1;
                                }
                                break;
                            case 2: // MaxItens
                                if (opts[I_OPTS_MAXITENS] < 10) {
                                    opts[I_OPTS_MAXITENS] += 1;
                                }
                                break;
                            case 3: // Cenario
                                if (opts[I_OPTS_NUMCENARIO] < 3) {
                                    opts[I_OPTS_NUMCENARIO] += 1;
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    case ASCII_ESQUERDA:
                        switch(selecionado) {
                            case 0: // Velocidade Inicial
                                if (opts[I_OPTS_VELOCIDADE] > 1) {
                                    opts[I_OPTS_VELOCIDADE] -= 1;
                                }
                                break;
                            case 1: // MaxTamanho
                                if (opts[I_OPTS_MAXTAMANHO] > 10) {
                                    opts[I_OPTS_MAXTAMANHO] -= 1;
                                }
                                break;
                            case 2: // MaxItens
                                if (opts[I_OPTS_MAXITENS] > 1) {
                                    opts[I_OPTS_MAXITENS] -= 1;
                                }
                                break;
                            case 3:
                                if (opts[I_OPTS_NUMCENARIO] > 1) {
                                    opts[I_OPTS_NUMCENARIO] -= 1;
                                }
                                break;
                            default:
                                break;
                        }
                        break;
                    default:
                        break;
                }
            } else if (op == 13) {
                switch (selecionado) {
                    case 4:
                        voltar = 1;
                        break;
                    default:
                        break;
                }
                //display_creditos();
            } else if (op == 27) {
                voltar = 1;
            }

            display_menu_opcoes(selecionado, opts);
        }
    }
}

void display_creditos() {
    int i, linhas;
    char creditos[][80] = {"Desenvolvido por Tiago Ceccon e Manuel Micas.",
                           "Para a cadeira de Algoritmos E Programacao (INF01202)",
                           "do curso de Ciencia da Computacao da UFRGS.",
                           "2017-01"};


    //clrscr();
    limpa_tela_menu();

    linhas = sizeof(creditos)/sizeof(creditos[0]);
    for (i = 0; i < linhas; i++) {
        cputsxy((MAX_X_TELA - strlen(creditos[i]))/2, LINHA_INICIO_MENU + i, creditos[i]);
    }

    textbackground(BLACK);
    textcolor(LIGHTGREEN);
    cputsxy(35, LINHA_INICIO_MENU+i+2, "  VOLTAR  ");
    textbackground(BROWN);
    textcolor(BLACK);
    gotoxy(42, LINHA_INICIO_MENU+i+2);

    while(getch() != ASCII_ENTER);
}

void display_high_scores() {
    SCORE scores[NUM_HIGH_SCORES];
    int i = 0;
    char str_score[15];

    carrega_score(scores);
    //clrscr();
    ordena_score(scores);
    //display_scores(scores, NUM_HIGH_SCORES);

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
        cputsxy(30, LINHA_INICIO_HIGH_SCORES+i, str_score);
    }

    textbackground(BLACK);
    textcolor(LIGHTGREEN);
    cputsxy(34, LINHA_INICIO_HIGH_SCORES+i+1, "  VOLTAR  ");
    textbackground(BROWN);
    textcolor(BLACK);
    gotoxy(41, LINHA_INICIO_HIGH_SCORES+i+1);

    while(getch() != ASCII_ENTER);
}

void limpa_tela_menu() {
    int i, j;
    textbackground(BROWN);
    for (i = LINHA_INICIO_MENU; i < MAX_Y_TELA; i++) {
        for (j = 2; j < MAX_X_TELA; j++) {
                putchxy(j, i, ' ');
        }
    }
}

void ini_display_menu() {
    int i, j;
//    char tela[25][80] = {
//                            {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000011111001111011001111100110011001111100000000000000000000001"},
//                            {"10000000000000000000011000001111011001101100110110001100000000000000000000000001"},
//                            {"10000000000000000000011111001101011001111100111100001111100000000000000000000001"},
//                            {"10000000000000000000000011001101111001101100110110001100000000000000000000000001"},
//                            {"10000000000000000000011111001101111001101100110011001111100000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"10000000000000000000000000000000000000000000000000000000000000000000000000000001"},
//                            {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"}};

    char tela[11][80] = {
//                            {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"},
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
//                            {"11111111111111111111111111111111111111111111111111111111111111111111111111111111"}};

    // Desenha moldura
//    textbackground(2);
    textbackground(GREEN);
    for (i = 1; i < 81; i++) {
        putchxy(i, 1, ' ');
        putchxy(i, 25, ' ');
    }
    for (i = 1; i < 26; i++) {
        putchxy(1, i, ' ');
        putchxy(80, i, ' ');
    }
    gotoxy(1,1);

    // Desenha titulo
//    textbackground(6);
    textbackground(BROWN);
    for (i = 1; i < 11; i++) {
        for (j = 0; j < 80; j++) {
            if (tela[i][j] == '1') {
//                textbackground(2);
                textbackground(GREEN);
                putchxy(j+1, i+1, ' ');
            } else {
//                textbackground(6);
                textbackground(BROWN);
                putchxy(j+1, i+1, ' ');
            }
        }
    }
//    textbackground(6);
    textbackground(BROWN);
    gotoxy(1,1); // Volta o cursor para o início da tela
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
//    textcolor(WHITE);
//    printf("\n%d\nAAAAAAAAAAAAA", p_snake->tamanho); getchar();

    p_snake->direcao = 'd';

    //p_snake->corpo[0].x = INI_X_SNAKE;
    //p_snake->corpo[0].y = INI_Y_SNAKE;

    textbackground(BACK_SNAKE);
    for (i = 0; i < tamanho; i++) { //TODO: tirar constante
        p_snake->corpo[i].x = INI_X_SNAKE - i;
        p_snake->corpo[i].y = INI_Y_SNAKE;
        cenario[p_snake->corpo[i].y - 2][p_snake->corpo[i].x - 1] = 'B';
        putchxy(p_snake->corpo[i].x, p_snake->corpo[i].y, ' ');
    }



}


void desenha_snake(int x_cabeca, int y_cabeca, int x_cauda, int y_cauda) {
    textbackground(BACK_SNAKE);
    putchxy(x_cabeca, y_cabeca, ' ');
    textbackground(BACK_CENARIO);
    putchxy(x_cauda, y_cauda, ' ');
    textbackground(BACK_CENARIO);
}

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

void popula_cenario(char addr_cenario[LINHAS_CENARIO][COLUNAS_CENARIO], int numero_cenario) {
    int i, j;
    FILE *arq_mapa;
    char nome_arq[9];
    char buf[COLUNAS_CENARIO + 1];
    char cenario[3][LINHAS_CENARIO][COLUNAS_CENARIO] = {{
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

/*
    inicializa_cenario: Popula array do cenario, faz a inicializacao dele na tela e trata tuneis.
*/
void inicializa_cenario(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], int numero_cenario, TUNEL tuneis[MAX_TUNEIS], int *num_tuneis) {

    // Cenario
    popula_cenario(cenario, numero_cenario);
    desenha_cenario(cenario);

    // Tuneis
    *num_tuneis = inicializa_tuneis(tuneis, numero_cenario);
    posiciona_tuneis_no_cenario(cenario, tuneis, *num_tuneis);
    //textbackground(WHITE);
    //printf("OASOGIHAUGHAUIGHAUIGHA\t%d", *num_tuneis); getch();
    desenha_tuneis(tuneis, *num_tuneis);
    //getch();

}

// inicializa_tuneis
/*
    Inicializa o array de tuneis
*/
int inicializa_tuneis(TUNEL tuneis[MAX_TUNEIS], int numero_cenario){
    //tuneis[0] = {NULL};
    //tuneis[1] = {{ {3, 4} , 0, 'd', 1} , { {60,4} , 1, 'e', 0}};
    //int i;
    /*
    // Tuneis do CENARIO 2
    TUNEL t1 = { {10, 4} , 0, 'd', 1, 2};
    TUNEL t2 = {{60,4} , 1, 'e', 0, 2};
    */

    /*
    // Tuneis do CENARIO 3
    TUNEL t1 = { {15, 12} , 0, 'e', 1, 3};
    TUNEL t2 = {{30,4} , 1, 'e', 2, 3};
    TUNEL t3 = { {50, 3} , 2, 'd', 3, 3};
    TUNEL t4 = {{60,20} , 3, 'e', 4, 3};
    TUNEL t5 = { {27, 18} , 4, 'd', 0, 3};

    tuneis[0] = t1;
    tuneis[1] = t2;
    tuneis[2] = t3;
    tuneis[3] = t4;
    tuneis[4] = t5;

    return 5;
    */
    int tamanho = 0, tam_buff;
    TUNEL tun_buff;
    FILE *arq_tuneis;

    arq_tuneis = fopen("tuneis.bin", "rb");

    while (!feof(arq_tuneis)) {
        tam_buff = fread(&tun_buff, sizeof(TUNEL), 1, arq_tuneis);

        if (tam_buff == 1 && tun_buff.cenario == numero_cenario) {
            tuneis[tamanho] = tun_buff;
            tamanho += tam_buff;
        }
    }

    fclose(arq_tuneis);

    return tamanho;



    //tuneis[2] = {NULL};

    /*{
        {
            NULL
        },
        {
            {{3, 4}, 0, 'd', 1},
            {{60, 4}, 1, 'e', 0}
        },
        {
            NULL
        }
            }; */
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



void desenha_interface(int pontuacao, int velocidade, int tamanho, int cenario_atual) {
    char status[80];
    int i;

    // Todas as informacoes aparecem contanto que pontuacao seja menor do que 99999999, acima disso estoura o limite da tela
    sprintf(status, "Score: %d\tVelocidade: %d\t\tSNAKE\t\tTamanho: %d\tMapa: %d\n",  pontuacao, velocidade, tamanho, cenario_atual);
    textbackground(WHITE);
    for (i = 1; i < 81; i++) {
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

void processa_proximo_movimento(COORDENADA proxima_coord, int *p_pontuacao, int *p_velocidade, SNAKE *snake, int max_tamanho, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL *tuneis, int num_tuneis, int *p_encerrar, int num_cenario){
    char item_no_proximo_movimento = cenario[ proxima_coord.y-OFFSET_Y ][ proxima_coord.x-OFFSET_X ];

    //movimenta_snake(&snake, proxima_coord);
    //printf("%d\t%d", proxima_coord.x, proxima_coord.y); getch();
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


void processa_colisao(int *p_pontuacao, int *p_velocidade, int *p_tamanho, int *p_encerrar, char item, int max_tamanho, char cenario[LINHAS_CENARIO][COLUNAS_CENARIO], TUNEL *tuneis, int num_tuneis, SNAKE *snake, COORDENADA *proxima_coord) {
    COORDENADA coord_temp;

    switch(item) {
        case '1': // Obstaculo
        case 'B': // Corpo da cobra
            //*p_encerrar = 1;
            *p_encerrar = GAME_OVER;
            break;
        case 'C': // Comida
            //*p_pontuacao += 2 * (*p_tamanho / 5) * *p_velocidade;
            *p_pontuacao += calcula_pontos(*p_velocidade, *p_tamanho, item);
            if (*p_tamanho < max_tamanho) {
                *p_tamanho += 1;
            }
            gera_novo_item(cenario);
            break;
        case 'S': // Slower
            *p_pontuacao += calcula_pontos(*p_velocidade, *p_tamanho, item);
            gera_novo_item(cenario);
            if (*p_velocidade > 1) { // TODO: tirar numero constante
                *p_velocidade -= 1;
            }
            break;
        case 'F': // Faster
            *p_pontuacao += calcula_pontos(*p_velocidade, *p_tamanho, item);
            gera_novo_item(cenario);
            if (*p_velocidade < 10) { // TODO: tirar numero constante
                *p_velocidade += 1;
            }
            break;
        case 'V': // Skip = vitoria = cenario completo
            *p_pontuacao += calcula_pontos(*p_velocidade, *p_tamanho, item);
            *p_encerrar = CENARIO_COMPLETO;
            break;
        case 'T': // Tunel
            //if (!entra_tunel(tuneis, snake->corpo, &snake->direcao, num_tuneis )) {
            if (!entra_tunel(tuneis, proxima_coord, &snake->direcao, num_tuneis )) {
                //coord_temp.x = snake->corpo[0].x+OFFSET_X;
                //coord_temp.y = snake->corpo[0].y+OFFSET_Y; // TODO: Offset, again
                coord_temp.x = proxima_coord->x+OFFSET_X;
                coord_temp.y = proxima_coord->y+OFFSET_Y; // TODO: Offset, again
                //movimenta_snake(snake, proxima_coordenada(coord_temp, snake->direcao));
                coord_temp = proxima_coordenada(coord_temp, snake->direcao);
                //snake->corpo[0] = coord_temp;
                *proxima_coord = coord_temp;

                // Chama uma versao atualizada de si propria para processar o caso de haver um item significativo
                // logo a frente do tunel
                processa_colisao(p_pontuacao, p_velocidade, p_tamanho, p_encerrar, cenario[ proxima_coord->y-OFFSET_Y ][ proxima_coord->x-OFFSET_X ], max_tamanho, cenario, tuneis, num_tuneis, snake, proxima_coord);

            } else {
                *p_encerrar = GAME_OVER;
            } //printf("UGHAUIGUGUAGSAGS");
            break;

        default:
            //*p_pontuacao += 20;
            break;
    }
}

// busca_tunel: funcao do dia 14/06
/*
    Entrada: Um vetor de tunel , uma coordenada .
    Saida: O index do tunel correspondente a coordenada de entrada.
*/
int busca_tunel(TUNEL *tuneis, COORDENADA coord, int num_tuneis) {
    int i, i_encontrado = -1; //printf("\n\n\n%d\t%d\t%d\t%d", tuneis[0].pos.x, tuneis[0].pos.y, coord.x, coord.y); getch();

    for (i = 0; i < num_tuneis; i++) {
        if ((tuneis[i].pos.x == coord.x -1 ) && (tuneis[i].pos.y == coord.y - 2)) { // Arrumar offsets nas representacoes das pos x, y de cobra e tunel
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

    //i = busca_tunel(tuneis, corpo[0], num_tuneis);
    i = busca_tunel(tuneis, *corpo, num_tuneis);
    //printf("\n\n\n\n%c", *direcao); // TODO: limpar debug
    //return 0;

    if (*direcao != tuneis[i].direcao) {
        return 1; // Cobra entrou pela direcao errada, morreu
    }

    novo_x = tuneis[tuneis[i].id_saida].pos.x; //printf("NovoX:%d\n", novo_x);
    novo_y = tuneis[tuneis[i].id_saida].pos.y; //printf("NovoY:%d\n", novo_y);
    nova_direcao = tuneis[tuneis[i].id_saida].direcao; //printf("NovaD:%c\n", nova_direcao);

    //corpo[0].x = novo_x;
    //corpo[0].y = novo_y;
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

void gera_novo_item(char cenario[LINHAS_CENARIO][COLUNAS_CENARIO]) {
    int novo_x, novo_y;
    char novo_item = escolhe_item();

    do {
//        novo_y = ((int) (rand() / (double) RAND_MAX * (22+1))) + 2;
//        novo_x = ((int) (rand() / (double) RAND_MAX * (78+1))) + 1;
        novo_y = ((int) (rand() / (double) RAND_MAX * (LINHAS_CENARIO - 2) )) + 1;
        novo_x = ((int) (rand() / (double) RAND_MAX * (COLUNAS_CENARIO - 3))) + 1;
    } while (cenario[novo_y][novo_x] != '0');

    cenario[novo_y][novo_x] = novo_item;
    putchxy(novo_x+1, novo_y+2, novo_item);

}

void fim_cenario(int result) {
    char mensagem[50];
    switch(result) {
        case GAME_OVER:
            sprintf(mensagem, "GAME OVER");
            break;
        case CENARIO_COMPLETO:
            sprintf(mensagem, "CENARIO COMPLETO");
            break;
        case USER_EXIT:
            sprintf(mensagem, "VOCE SAIU");
            break;
        default:
            break;
    }

    textbackground(BROWN);
    textcolor(LIGHTRED);

    cputsxy(36, 12, mensagem);
    cputsxy(30, 13, "Aperte ENTER para sair.");

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
        cputsxy(30, 18, "VOCE ENTROU NO TOP 10!!!");
        pega_nome(novo_high_score.nome);
        insere_score(scores, novo_high_score);
        salva_scores(scores);
        //printf("HIGH SCORE!!!!!\n%s", novo_high_score.nome);
        //display_scores(scores, NUM_HIGH_SCORES);
        //getch();
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

    putchxy(x, 20, letra); // Mostra a letra atualmente selecionada
    gotoxy(x, 20);

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
                putchxy(x, 20, letra); // Atualiza a letra na tela
                gotoxy(x, 20);
            } else if(op == ASCII_ENTER) {
                fim = 1;
            }
        }

    }

    return letra;
}

void pega_nome(char *nome) {
    //cputsxy(30, 20, "Nome (3 caracteres): ");
    cputsxy(30, 20, "Nome: ");
    nome[0] = pega_letra(37);
    nome[1] = pega_letra(38);
    nome[2] = pega_letra(39);
    nome[3] = '\0';
    //fgets(nome, 4, stdin);
    fflush(stdin);
}


int roda_jogo(int opts[10]) {
    //int snake[101][2] = {0}; // Verificar como contornar inicializacao do array com num variavel
    int proximo_movimento[2] = {1,0} ;
    char cenario[LINHAS_CENARIO][COLUNAS_CENARIO];
    TUNEL tuneis[MAX_TUNEIS] = {0};
    int num_tuneis;
    char item_no_proximo_movimento;
    int encerrar = 0, pause = 1, inicializado = 0;
    int op;
    int i;
    int aux_x, aux_y;
//    int velocidade = 1, tamanho = 5, score = 0;
    int velocidade = opts[I_OPTS_VELOCIDADE];
    int tamanho = 5;
    //int score = 0;
    //SNAKE snake = {{0}, 'd', 5};
    SNAKE snake = {0};
    COORDENADA proxima_coord;


    //snake[0][X_POS] = 40;
    //snake[0][Y_POS] = 15;
    /*
    snake[0][X_POS] = 20;
    snake[0][Y_POS] = 10;
    */
//    snake.corpo[0].x = 20;
//    snake.corpo[0].y = 12;

    //snake.corpo[0].x = INI_X_SNAKE;  |||
    //snake.corpo[0].y = INI_Y_SNAKE;  |||

//    snake.corpo[1].x = 19;
//    snake.corpo[1].y = 12;
//    snake.corpo[2].x = 18;
//    snake.corpo[2].y = 12;
//    snake.corpo[3].x = 17;
//    snake.corpo[3].y = 12;
//    snake.corpo[4].x = 16;
//    snake.corpo[4].y = 12;

//    snake[1][X_POS] = 39;
//    snake[1][Y_POS] = 15;
//    snake[2][X_POS] = 38;
//    snake[2][Y_POS] = 15;
//    snake[3][X_POS] = 37;
//    snake[3][Y_POS] = 15;
//    snake[4][X_POS] = 36;
//    snake[4][Y_POS] = 15;
//    snake[5][X_POS] = 35;
//    snake[5][Y_POS] = 15;

//    printf("Escolha o cenario: ");
//    scanf("%d", &num_cenario);
//
    textbackground(BROWN);
    textcolor(BLACK);
    clrscr();

    // Gera array do cenario para logica do jogo
    // TODO: Mudar popula_cenario para que pegue do arquivo txt V
    //popula_cenario(cenario, opts[I_OPTS_NUMCENARIO]);

    // Gera cenario na tela
    // TODO: Mudar desenha_cenario para que ela receba o cenario e desenhe V
    //desenha_cenario(cenario);

    // Gerencia toda a inicializacao do cenario
    inicializa_cenario(cenario, opts[I_OPTS_NUMCENARIO], tuneis, &num_tuneis);

    inicializa_snake(&snake, INI_TAM_SNAKE, cenario);
    desenha_interface(opts[I_OPTS_SCORE], velocidade, snake.tamanho, opts[I_OPTS_NUMCENARIO]);

    //cenario[snake[0][Y_POS]-2][snake[0][X_POS]-1] = 'B'; // Evita que o primeiro item seja colocado na cabeca da cobra
    //cenario[snake.corpo[0].y - 2][snake.corpo[0].x - 1] = 'B'; // Evita que o primeiro item seja colocado na cabeca da cobra

    textbackground(BROWN);
    textcolor(BLACK);
//    gera_novo_item(cenario);
    for(i = 0; i < opts[I_OPTS_MAXITENS]; i++) {
        gera_novo_item(cenario);
    }

    while (!encerrar) {

        processa_input(&snake, &pause, &encerrar, &inicializado, cenario);

        if (!pause) {

            proxima_coord = proxima_coordenada(snake.corpo[0], snake.direcao);

            //movimenta_snake(&snake, proxima_coord);

            // Debug
            //gotoxy(1,1);
            //printf("%c\t%d\t%d\n", cenario[snake[0][Y_POS]-1 ][ snake[0][X_POS]-1], snake[0][Y_POS], snake[0][X_POS]);

            //item_no_proximo_movimento = cenario[ snake[0][Y_POS]-2 ][ snake[0][X_POS]-1 ];
//            item_no_proximo_movimento = cenario[ snake.corpo[0].y-OFFSET_Y ][ snake.corpo[0].x-OFFSET_X ];
            item_no_proximo_movimento = cenario[ proxima_coord.y-OFFSET_Y ][ proxima_coord.x-OFFSET_X ];
            //if (cenario[ snake[0][Y_POS]-2 ][ snake[0][X_POS]-1 ] == '1') {
//            if (item_no_proximo_movimento == '1') {
//                pause = 1;
//                encerrar = 1;
//            }


            processa_proximo_movimento(proxima_coord, &opts[I_OPTS_SCORE], &velocidade, &snake, opts[I_OPTS_MAXTAMANHO], cenario, tuneis, num_tuneis, &encerrar, opts[I_OPTS_NUMCENARIO]);
            //colidiu(&opts[I_OPTS_SCORE], &velocidade, &snake.tamanho, &encerrar, item_no_proximo_movimento, opts[I_OPTS_MAXTAMANHO], cenario, tuneis, num_tuneis, &snake);

            //movimenta_snake(&snake, proxima_coord);

            //if (item_no_proximo_movimento != '0') {
            //    desenha_interface(opts[I_OPTS_SCORE], velocidade, snake.tamanho, opts[I_OPTS_NUMCENARIO]);
            //}


            /*desenha_snake(snake[0][X_POS], snake[0][Y_POS], snake[tamanho][X_POS], snake[tamanho][Y_POS]);

            // Atualiza posicao da cobra na matriz do cenario
            cenario[ snake[0][Y_POS]-2 ][ snake[0][X_POS]-1 ] = 'B';
            cenario[ snake[tamanho][Y_POS]-2 ][ snake[tamanho][X_POS]-1 ] = '0';
            */

            desenha_snake(snake.corpo[0].x, snake.corpo[0].y, snake.corpo[snake.tamanho].x, snake.corpo[snake.tamanho].y);

//            // Atualiza posicao da cobra na matriz do cenario
//            cenario[ snake.corpo[0].y-OFFSET_Y ][ snake.corpo[0].x-OFFSET_X ] = 'B';
//            cenario[ snake.corpo[snake.tamanho].y-OFFSET_Y ][ snake.corpo[snake.tamanho].x-OFFSET_X ] = '0';

        }
        //gotoxy(1,1);

        Sleep(1000/velocidade); // TODO: tirar numero constante

    }




    //getch();

    fim_cenario(encerrar);

    if (encerrar == CENARIO_COMPLETO) {
        opts[I_OPTS_NUMCENARIO] += 1;
        opts[I_OPTS_SCORE] += 1000;
    }

    //gotoxy(1, 29);

    return encerrar;
}
