/*
     Dadas três notas, calcula a média ponderada final
*/
#include<stdio.h>
#define PESO_PROVA_1 0.4
#define PESO_PROVA_2 0.1
#define PESO_PROVA_3 0.5

int main() {
    
    float nota_prova_1, nota_prova_2, nota_prova_3, nota_final;
    
    printf("Nota da primeira prova: ");
    scanf("%f", &nota_prova_1);
    
    printf("Nota da segunda prova: ");
    scanf("%f", &nota_prova_2);
    
    printf("Nota da terceira prova: ");
    scanf("%f", &nota_prova_3);
    
    nota_final = nota_prova_1 * PESO_PROVA_1 + nota_prova_2 * PESO_PROVA_2 + nota_prova_3 * PESO_PROVA_3;
    
    
    printf("\nResultado: %.2f\n", nota_final);
    fflush(stdin);
    getchar();
    
    return 0;

}
