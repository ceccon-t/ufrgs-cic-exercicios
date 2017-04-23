/*
  Calcula numero de onibus e microonibus necessarios para transportar o numero de torcedores informado.
*/
#include<stdio.h>
#define LOTACAO_ONIBUS 43
#define LOTACAO_MICRO 12

int main() {
    
    int num_torcedores, num_onibus, num_micros;
    
    printf("Numero de torcedores: ");
    scanf("%d", &num_torcedores);
    
    num_onibus = num_torcedores / LOTACAO_ONIBUS;
    
    /* Atualiza num. de torcedores restantes apos preencher onibus */
    num_torcedores = num_torcedores % LOTACAO_ONIBUS;
    
    num_micros = num_torcedores / LOTACAO_MICRO;
    
    /* Caso a divisao para os micros apresente resto, acrescenta um micro */
    if (num_torcedores % LOTACAO_MICRO > 0) {
        num_micros = num_micros + 1;
    }
    
    printf("\nNumero de onibus: %d\nNumero de microonibus: %d\n", num_onibus, num_micros);
    
    return 0;
    
}
