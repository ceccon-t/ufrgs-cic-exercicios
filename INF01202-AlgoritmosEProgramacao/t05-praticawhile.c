/*
   Calcular venda de acoes
*/
#include<stdio.h>
#define ESTOQUE_INICIAL_1 10000
#define ESTOQUE_INICIAL_2 2000
#define ESTOQUE_INICIAL_3 5000
#define ESTOQUE_INICIAL_4 500

int main() {

    // Variaveis de controle do programa
    int codigo = 1, encerramento = 0, erro_encontrado = 0;

    // Variaveis para calculo das transacoes
    int disponivel_empresa_1 = ESTOQUE_INICIAL_1, disponivel_empresa_2 = ESTOQUE_INICIAL_2, disponivel_empresa_3 = ESTOQUE_INICIAL_3, disponivel_empresa_4 = ESTOQUE_INICIAL_4;
    float valor_empresa_1 = 14, valor_empresa_2 = 2.5, valor_empresa_3 = 1.2, valor_empresa_4 = 2.2;
    int qtd_comprar, vendidos_total = 0, vendas_com_sucesso = 0;
    float valor_pagar = 0, valor_total_vendido = 0;

    // Variaveis para saida
    int vendidos_empresa_1 = 0, vendidos_empresa_2 = 0, vendidos_empresa_3 = 0, vendidos_empresa_4 = 0;
    int codigo_mais_vendido;
    float valor_mais_vendido = 0;

    while(codigo > 0 && codigo < 5) {

        erro_encontrado = 0;

        // Apresentar tabela de acoes disponiveis para compra
        printf("Codigo\tOpcao\t\tDisponivel\tValor(R$)\n");
        printf("1\tGerdau\t\t%10d\t%8.2f\n", disponivel_empresa_1, valor_empresa_1);
        printf("2\tPetrobras\t%10d\t%8.2f\n", disponivel_empresa_2, valor_empresa_2);
        printf("3\tGrendene\t%10d\t%8.2f\n", disponivel_empresa_3, valor_empresa_3);
        printf("4\tVivo\t\t%10d\t%8.2f\n", disponivel_empresa_4, valor_empresa_4);

        printf("\nCodigo de acao a ser comprada: ");
        scanf("%d", &codigo);

        switch(codigo) {
            case 1:
                printf("Numero de acoes a comprar: ");
                scanf("%d", &qtd_comprar);
                if(qtd_comprar > disponivel_empresa_1) {
                    erro_encontrado = 1;
                    printf("\n!!!!!!!!!!\n");
                    printf("\nA quantidade selecionada nao esta disponivel. Ha %d acoes em estoque para essa empresa.\n", disponivel_empresa_1);
                    printf("\n!!!!!!!!!!\n");
                } else {
                    valor_pagar = qtd_comprar * valor_empresa_1;
                    vendidos_empresa_1 += qtd_comprar;
                    disponivel_empresa_1 -= vendidos_empresa_1;
                    if (vendidos_empresa_1 > valor_mais_vendido) {
                        valor_mais_vendido = vendidos_empresa_1;
                        codigo_mais_vendido = 1;
                    }
                }
                break;
            case 2:
                printf("Numero de acoes a comprar: ");
                scanf("%d", &qtd_comprar);
                if(qtd_comprar > disponivel_empresa_2) {
                    erro_encontrado = 1;
                    printf("\n!!!!!!!!!!\n");
                    printf("\nA quantidade selecionada nao esta disponivel. Ha %d acoes em estoque para essa empresa.\n", disponivel_empresa_2);
                    printf("\n!!!!!!!!!!\n");
                } else {
                    valor_pagar = qtd_comprar * valor_empresa_2;
                    vendidos_empresa_2 += qtd_comprar;
                    disponivel_empresa_2 -= vendidos_empresa_2;
                    if (vendidos_empresa_2 > valor_mais_vendido) {
                        valor_mais_vendido = vendidos_empresa_2;
                        codigo_mais_vendido = 2;
                    }
                }
                break;
            case 3:
                printf("Numero de acoes a comprar: ");
                scanf("%d", &qtd_comprar);
                if(qtd_comprar > disponivel_empresa_3) {
                    erro_encontrado = 1;
                    printf("\n!!!!!!!!!!\n");
                    printf("\nA quantidade selecionada nao esta disponivel. Ha %d acoes em estoque para essa empresa.\n", disponivel_empresa_3);
                    printf("\n!!!!!!!!!!\n");
                } else {
                    valor_pagar = qtd_comprar * valor_empresa_3;
                    vendidos_empresa_3 += qtd_comprar;
                    disponivel_empresa_3 -= vendidos_empresa_3;
                    if (vendidos_empresa_3 > valor_mais_vendido) {
                        valor_mais_vendido = vendidos_empresa_3;
                        codigo_mais_vendido = 3;
                    }
                }
                break;
            case 4:
                printf("Numero de acoes a comprar: ");
                scanf("%d", &qtd_comprar);
                if(qtd_comprar > disponivel_empresa_4) {
                    erro_encontrado = 1;
                    printf("\n!!!!!!!!!!\n");
                    printf("\nA quantidade selecionada nao esta disponivel. Ha %d acoes em estoque para essa empresa.\n", disponivel_empresa_4);
                    printf("\n!!!!!!!!!!\n");
                } else {
                    valor_pagar = qtd_comprar * valor_empresa_4;
                    vendidos_empresa_4 += qtd_comprar;
                    disponivel_empresa_4 -= vendidos_empresa_4;
                    if (vendidos_empresa_4 > valor_mais_vendido) {
                        valor_mais_vendido = vendidos_empresa_4;
                        codigo_mais_vendido = 4;
                    }
                }
                break;
            default:
                encerramento = 1;
        }

        // Finalizar compra e mostrar resultados
        if(!encerramento) {
            printf("\n==========\n");
            if (!erro_encontrado) {
                valor_total_vendido += valor_pagar;
                vendidos_total += qtd_comprar;
                vendas_com_sucesso++;
                printf("\nCompra efetuada com sucesso.\n\n");
            } else {
                qtd_comprar = 0;
                printf("\nCompra nao efetuada.\n\n");
            }
            printf("Codigo\tQtd comprada\tPreco a pagar\n%d\t%d\t\t%R$ %.2f\n", codigo, qtd_comprar, valor_pagar);
            printf("\n==========\n");
        } else {
            printf("\n==========\n");
            printf("\nCodigo de encerramento inserido, fechando o programa.\n");
            printf("\n==========\n");
        }

        fflush(stdin);
        getchar();
        system("cls");

    }

    // Apresenta tabela de vendas do dia
    printf("\n--------- RELATORIO DE VENDAS DO DIA ---------\n\n");
    printf("Empresa\t\tLotes vendidos\tTotal Faturado\n\n");
    printf("Gerdau\t\t%14d\tR$ %8.2f\n",  vendidos_empresa_1, vendidos_empresa_1 * valor_empresa_1);
    printf("Petrobras\t%14d\tR$ %8.2f\n", vendidos_empresa_2, vendidos_empresa_2 * valor_empresa_2);
    printf("Grendene\t%14d\tR$ %8.2f\n", vendidos_empresa_3, vendidos_empresa_3 * valor_empresa_3);
    printf("Vivo\t\t%14d\tR$ %8.2f\n", vendidos_empresa_4, vendidos_empresa_4 * valor_empresa_4);
    printf("\n------\n");
    printf("\nMedia das vendas\t\tR$ %5.2f\n", valor_total_vendido/vendas_com_sucesso);
    printf("\nCodigo da acao mais vendida\t\t%3d", codigo_mais_vendido);
    printf("\n----------------------------------------------\n");


    fflush(stdin);
    getchar();

    return 0;

}
