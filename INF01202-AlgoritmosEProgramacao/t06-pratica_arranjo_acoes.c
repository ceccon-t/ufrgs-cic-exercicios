/*
Considere os arranjos:
1. Arranjo de strings Acoes contendo os nomes das N ações a serem vendidos na bolsa
de valores. Faça seu programa para funcionar com qualquer número de ações, não
apenas 4, mudando apenas as constantes.
Gerdau, Petrobras, Grendene, Vivo,
2. Um arranjo Vendas de N x Meses, que armazena o numero de ações vendidas em
cada mês.
Faca um programa que:
1- Leia um string do teclado e mostre o índice desse string no arranjo Acoes. Se o string
não existir, mostre -1.
2- Some e retorne o número de ações vendidas registrado no arranjo Vendas associado ao
índice identificado no item anterior. Se for retornado -1, dê uma mensagem ao usuário.
3- Identifique a ação com mais unidades vendidas no ano (use um vetor auxiliar int com
tamanho N para guardar resultados intermediários).
4- Zere todos os meses de venda desta ação na matriz.
5- Mostre ao usuário o nome da ação zerada lendo do vetor.
*/
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#define N_ACOES 4
#define MAX_NOME 20
#define N_MESES 12
#define RANGE_VENDAS 200

int main() {
    char acoes[N_ACOES][MAX_NOME] = {"Gerdau", "Petrobras", "Grendene", "Vivo"};
    int vendas[N_ACOES][12] = {0};
    int vendas_no_ano[N_ACOES] = {0};
    int venda_mes, val_maior_vendas_ano, pos_maior_vendas_ano;
    char acao_selecionada[MAX_NOME];
    int i, j, encontrado;

    srand(time(0));

    for(i = 0; i < N_ACOES; i++) {
        for(j = 0; j < N_MESES; j++) {
            // Popula a tabela de vendas com numeros aleatorios
            venda_mes = (int) (rand()/ (double) RAND_MAX * (RANGE_VENDAS + 1));
            vendas[i][j] = venda_mes;
            // Atualiza o total de vendas dessa acao no ano
            vendas_no_ano[i] += venda_mes;
        }
    }

    printf("Tabela de vendas:\n");
    for(i = 0; i < N_ACOES; i++) {
        puts(acoes[i]);
        for(j = 0; j < N_MESES; j++) {
            printf("%5d", vendas[i][j]);
        }
        printf("\nTotal no ano: %i", vendas_no_ano[i]);
        printf("\n");

    }

    printf("\nSelecione uma acao: ");
    gets(acao_selecionada);

    i = 0;
    while((i < N_ACOES) && ((strcmp(acao_selecionada, acoes[i])) != 0)) {
        i++;
    }

    if(i < N_ACOES) {
        printf("O indice da acao selecionada e: %i\n", i);
        printf("O total de vendas no ano dessa empresa foi: %i\n", vendas_no_ano[i]);
    } else {
        printf("O indice da acao selecionada e: -1\n");
        printf("Acao nao encontrada.\n");
    }

    getchar();

    printf("\nCalculando a acao com mais vendas no ano.");
    //val_maior_vendas_ano = vendas_no_ano[0];
    pos_maior_vendas_ano = 0;
    for (i = 1; i < N_ACOES; i++) {
        if (vendas_no_ano[i] > vendas_no_ano[pos_maior_vendas_ano]) {
            pos_maior_vendas_ano = i;
        }
    }

    printf("\nAcao com mais vendas no ano: %s.\nDeletando todas as suas vendas.\n", acoes[pos_maior_vendas_ano]);
    getchar();
    for(j = 0; j < N_MESES; j++) {
        vendas[pos_maior_vendas_ano][j] = 0;
    }
    vendas_no_ano[pos_maior_vendas_ano] = 0;


    printf("Tabela atualizada de vendas:\n\n");
    for(i = 0; i < N_ACOES; i++) {
        puts(acoes[i]);
        for(j = 0; j < N_MESES; j++) {
            printf("%5d", vendas[i][j]);
        }
        //printf("\nTotal no ano: %i", vendas_no_ano[i]);
        printf("\n");

    }



    getchar();
    return 0;
}
