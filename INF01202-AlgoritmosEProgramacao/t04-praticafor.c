/*
   Calcular venda de acoes
*/
#include<stdio.h>
#define ESTOQUE_INICIAL_1 5000
#define ESTOQUE_INICIAL_2 4500
#define ESTOQUE_INICIAL_3 500
#define ESTOQUE_INICIAL_4 2000
#define NUM_INTERACOES 5

int main() {

    // Declaraco de variaveis
    int i, continuar = 1;
    int disponivel_empresa_1 = ESTOQUE_INICIAL_1, disponivel_empresa_2 = ESTOQUE_INICIAL_2, disponivel_empresa_3 = ESTOQUE_INICIAL_3, disponivel_empresa_4 = ESTOQUE_INICIAL_4;
    float valor_empresa_1 = 4, valor_empresa_2 = 2.5, valor_empresa_3 = 2.5, valor_empresa_4 = 1.2;
    int codigo, qtd_comprar, vendidos_total = 0, vendas_com_sucesso = 0;
    float valor_pagar = 0, valor_total_vendido = 0;

    for(i = 0; i < NUM_INTERACOES; i++) {

        // Apresentar tabela de acoes disponiveis para compra
        printf("Codigo\tOpcao\t\tDisponivel\tValor(R$)\n");
        printf("1\tGerdau\t\t%d\t\t%.2f\n", disponivel_empresa_1, valor_empresa_1);
        printf("2\tPetrobras\t%d\t\t%.2f\n", disponivel_empresa_2, valor_empresa_2);
        printf("3\tAzaleia\t\t%d\t\t%.2f\n", disponivel_empresa_3, valor_empresa_3);
        printf("4\tGrendene\t%d\t\t%.2f\n", disponivel_empresa_4, valor_empresa_4);

        printf("\nCodigo de acao a ser comprada: ");
        scanf("%d", &codigo);

        switch(codigo) {
            case 1:
                printf("Numero de acoes a comprar: ");
                scanf("%d", &qtd_comprar);
                if(qtd_comprar > disponivel_empresa_1) {
                    printf("\n!!!!!!!!!!\n");
                    printf("\nA quantidade selecionada nao esta disponivel,  compra nao efetuada.\n");
                    printf("\n!!!!!!!!!!\n");
                    continuar = 0;
                } else {
                    disponivel_empresa_1 -= qtd_comprar;
                    valor_pagar = qtd_comprar * valor_empresa_1;
                }
                break;
            case 2:
                printf("Numero de acoes a comprar: ");
                scanf("%d", &qtd_comprar);
                if(qtd_comprar > disponivel_empresa_2) {
                    printf("\n!!!!!!!!!!\n");
                    printf("\nA quantidade selecionada nao esta disponivel,  compra nao efetuada.\n");
                    printf("\n!!!!!!!!!!\n");
                    continuar = 0;
                } else {
                    disponivel_empresa_2 -= qtd_comprar;
                    valor_pagar = qtd_comprar * valor_empresa_2;
                }
                break;
            case 3:
                printf("Numero de acoes a comprar: ");
                scanf("%d", &qtd_comprar);
                if(qtd_comprar > disponivel_empresa_3) {
                    printf("\n!!!!!!!!!!\n");
                    printf("\nA quantidade selecionada nao esta disponivel,  compra nao efetuada.\n");
                    printf("\n!!!!!!!!!!\n");
                    continuar = 0;
                } else {
                    disponivel_empresa_3 -= qtd_comprar;
                    valor_pagar = qtd_comprar * valor_empresa_3;
                }
                break;
            case 4:
                printf("Numero de acoes a comprar: ");
                scanf("%d", &qtd_comprar);
                if(qtd_comprar > disponivel_empresa_4) {
                    printf("\n!!!!!!!!!!\n");
                    printf("\nA quantidade selecionada nao esta disponivel,  compra nao efetuada.\n");
                    printf("\n!!!!!!!!!!\n");
                    continuar = 0;
                } else {
                    disponivel_empresa_4 -= qtd_comprar;
                    valor_pagar = qtd_comprar * valor_empresa_4;
                }
                break;
            default:
                continuar = 0;
                printf("\n!!!!!!!!!!\n");
                printf("\nCodigo invalido, compra nao efetuada.\n");
                printf("\n!!!!!!!!!!\n");

        }

        // Se nao foi identificado erro ate aqui, finaliza a compra
        if (continuar) {
            valor_total_vendido += valor_pagar;
            vendidos_total += qtd_comprar;
            vendas_com_sucesso++;
            printf("\n==========\n");
            printf("\nCompra efetuada com sucesso, %d acoes vendidas.\n", qtd_comprar);
            printf("\n==========\n");
        }
        fflush(stdin);
        getchar();
        system("cls");

    }


    // Apresenta tabela de vendas do dia
    printf("\n--------- RELATORIO DE VENDAS DO DIA ---------\n\n");
    printf("Empresa\t\tLotes vendidos\tTotal Faturado\n\n");
    printf("Gerdau\t\t%d\t\tR$ %.2f\n",  ESTOQUE_INICIAL_1 - disponivel_empresa_1, (ESTOQUE_INICIAL_1 - disponivel_empresa_1) * valor_empresa_1);
    printf("Petrobras\t%d\t\tR$ %.2f\n", ESTOQUE_INICIAL_2 - disponivel_empresa_2, (ESTOQUE_INICIAL_2 - disponivel_empresa_2) * valor_empresa_2);
    printf("Azaleia\t\t%d\t\tR$ %.2f\n", ESTOQUE_INICIAL_3 - disponivel_empresa_3, (ESTOQUE_INICIAL_3 - disponivel_empresa_3) * valor_empresa_3);
    printf("Grendene\t%d\t\tR$ %.2f\n", ESTOQUE_INICIAL_4 - disponivel_empresa_4, (ESTOQUE_INICIAL_4 - disponivel_empresa_4) * valor_empresa_4);
    printf("\n------\n");
    printf("\nTotal de vendas do dia\t\tR$ %.2f reais.\n", valor_total_vendido);
    printf("\nMedia das vendas\t\tR$ %.2f\n", valor_total_vendido/vendas_com_sucesso);
    printf("\n----------------------------------------------\n");


    fflush(stdin);
    getchar();

    return 0;

}
