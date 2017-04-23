/*
   Dado os preços e identificações de 3 produtos, informar valor médio de ICMS pago por eles (considerando taxa do RS: 17%)
*/
#include<stdio.h>
#define ICMS_RS 0.17

int main() {
    char id_produto_1, id_produto_2, id_produto_3;
    float preco_produto_1, preco_produto_2, preco_produto_3;
    float valor_icms_1, valor_icms_2, valor_icms_3;
    
    /* Recebe os dados relevantes */
    printf("Identificador produto 1: ");
    scanf("%c", &id_produto_1);
    printf("Preco produto 1: ");
    scanf("%f", &preco_produto_1);
    
    getchar(); /* Limpa buffer de entrada para scanf nao bugar */
    printf("Identificador produto 2: ");
    scanf("%c", &id_produto_2);
    printf("Preco produto 2: ");
    scanf("%f", &preco_produto_2);
    
    getchar(); 
    printf("Identificador produto 3: ");
    scanf("%c", &id_produto_3);
    printf("Preco produto 3: ");
    scanf("%f", &preco_produto_3);
    
    /* Calcula valores */
    valor_icms_1 = preco_produto_1 * ICMS_RS;
    valor_icms_2 = preco_produto_2 * ICMS_RS;
    valor_icms_3 = preco_produto_3 * ICMS_RS;
    
    /* Apresenta resultados */
    printf("\n---\n");
    printf("ICMS pago pelo produto %c: %.2f\n", id_produto_1, valor_icms_1);
    printf("ICMS pago pelo produto %c: %.2f\n", id_produto_2, valor_icms_2);
    printf("ICMS pago pelo produto %c: %.2f\n", id_produto_3, valor_icms_3);

    return 0;
}
