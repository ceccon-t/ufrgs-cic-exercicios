/*
  Calcula o salario bruto baseado no numero de horas trabalhadas
*/
#include<stdio.h>
#define SALARIO_FAMILIA 100

int main() {
    
    float num_horas, valor_hora, salario_bruto;
    int num_filhos;
    
    printf("Numero de horas trabalhadas: ");
    scanf("%f", &num_horas);
    
    printf("Valor da hora trabalhada: ");
    scanf("%f", &valor_hora);
    
    printf("Numero de filhos com menos de 14 anos: ");
    scanf("%d", &num_filhos);
    
    salario_bruto = num_horas * valor_hora + num_filhos * SALARIO_FAMILIA;
    
    printf("\nSalario bruto: %.2f\n", salario_bruto);
    
    
    return 0;

}
