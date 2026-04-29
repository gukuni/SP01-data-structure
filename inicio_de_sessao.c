#include <stdio.h>
#include <time.h>
#include <stdlib.h>


int main() {


   
    char cpf_motorista[12];
    int carregador;
    char horario[20];
   
   
    printf("     CHARGERID INTELLIGENCE - GOODWE\n");
    printf("------------------------------------------\n");
    printf("       INICIO DA SESSAO DE RECARGA\n");




   
    printf("Informe seu CPF (apenas numeros): ");
    scanf("%s", cpf_motorista);


   
    carregador = 0;
    printf("1 carregador - CCS2 (50kW - 350 kW)\n");
    printf("2 carregador - AC (7kW - 22kW) \n");
    printf("3 carregador - CHAdeMO (50kW)\n");
    printf("Qual carregador voce deseja utilizar? (1 , 2 ou 3)\n");
    scanf("%d", &carregador);
    while (carregador < 1 || carregador > 3) {
        printf("  Numero invalido! Digite apenas 1, 2 ou 3.\n\n");
        scanf("%d", &carregador);
        
    }
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    strftime(horario, 20, "%d/%m/%Y  %H:%M", t);
   
   
    printf("  SESSAO INICIADA COM SUCESSO!\n");
    printf("  Motorista  : %s\n", cpf_motorista);
    printf("  Carregador : Box %d\n", carregador);
    printf("  Horario  : %s\n", horario);
   
   

    system ("pause");
    return 0;
}
