/*
   Calcular venda de acoes
*/
#include<stdio.h>
#define COTACAO_DOLAR 2

int main() {

    /* Declaraco de variaveis */
    int codigo, qtd_comprar, disponivel_escolhido, continuar = 1;
    int disponivel_empresa_1 = 2000, disponivel_empresa_2 = 5000, disponivel_empresa_3 = 4500;
    float valor_empresa_1 = 4, valor_empresa_2 = 2.5, valor_empresa_3 = 2.5;
    int vendidos_empresa_1 = 0, vendidos_empresa_2 = 0, vendidos_empresa_3 = 0;
    float faturado_empresa_1 = 0.0, faturado_empresa_2 = 0.0, faturado_empresa_3 = 0.0;
    float valor_pagar = 0;

    /* Apresentar tabela de acoes disponiveis para compra */
    printf("Codigo\tOpcao\t\tDisponivel\tValor(R$)\n");
    printf("1\tGerdau\t\t%d\t\t%.2f\n", disponivel_empresa_1, valor_empresa_1);
    printf("2\tPetrobras\t%d\t\t%.2f\n", disponivel_empresa_2, valor_empresa_2);
    printf("3\tAzaleia\t\t%d\t\t%.2f\n", disponivel_empresa_3, valor_empresa_3);

    /* Define qual acao vai ser comprada e pega os dados relevantes */
    printf("\nCodigo de acao a ser comprada: ");
    scanf("%d", &codigo);

    if(codigo == 1) {
        disponivel_escolhido = disponivel_empresa_1;
    } else {
        if(codigo == 2) {
            disponivel_escolhido = disponivel_empresa_2;
        } else {
            if(codigo == 3) {
                disponivel_escolhido = disponivel_empresa_3;
            } else {
                printf("\n!!!!!!!!!!\n");
                printf("\nCodigo invalido, encerrando programa.\n");
                printf("\n!!!!!!!!!!\n");
                continuar = 0;
            }
        }
    }

    /* Processa a quantidade a ser comprada */
    if(continuar > 0) {
        printf("Numero de acoes a comprar: ");
        scanf("%d", &qtd_comprar);

        if(qtd_comprar > disponivel_escolhido) {
            printf("\n!!!!!!!!!!\n");
            printf("\nA quantidade selecionada nao esta disponivel, encerrando programa.\n");
            printf("\n!!!!!!!!!!\n");
            continuar = 0;
        } else {
            if (codigo == 1) {
                vendidos_empresa_1 = qtd_comprar;
                faturado_empresa_1 = qtd_comprar * valor_empresa_1;
                valor_pagar = faturado_empresa_1;
                if(valor_empresa_1 < COTACAO_DOLAR) {
                    faturado_empresa_1 = faturado_empresa_1 * 0.97;
                    valor_pagar = valor_pagar * 0.97; /* Desconto para Gerdau */
                }
            } else {
                if(codigo == 2) {
                    vendidos_empresa_2 = qtd_comprar;
                    faturado_empresa_2 = qtd_comprar * valor_empresa_2;
                    valor_pagar = faturado_empresa_2;
                } else {
                    vendidos_empresa_3 = qtd_comprar;
                    faturado_empresa_3 = qtd_comprar * valor_empresa_3;
                    valor_pagar = faturado_empresa_3;
                }
            }
        }
    }

    /* Se nao foi identificado erro ate aqui, informa que a compra foi realizada */
    if (continuar) {
        printf("\n==========\n");
        printf("\nCompra efetuada com sucesso.\n");
        printf("\n==========\n");
    }

    /* Apresenta tabela de vendas do dia */
    fflush(stdin);
    getchar();
    system("cls");
    printf("\n--------- RELATORIO DE VENDAS DO DIA ---------\n\n");
    printf("Acao\t\tQuantidade\tTotal Faturado\n\n");
    printf("Gerdau\t\t%d\t\t%.2f\n", vendidos_empresa_1, faturado_empresa_1);
    printf("Petrobras\t%d\t\t%.2f\n", vendidos_empresa_2, faturado_empresa_2);
    printf("Azaleia\t\t%d\t\t%.2f\n", vendidos_empresa_3, faturado_empresa_3);
    printf("\nTotal de vendas do dia: (R$) %.2f reais.\n\n", valor_pagar);
    printf("----------------------------------------------\n");

    fflush(stdin);
    getchar();

    return 0;

}
