#include <stdio.h>
#include <time.h>


int main() {


   
    char cpf_motorista[11];
    int carregador;
    char horario[20];
   
   
    printf("     CHARGERID INTELLIGENCE - GOODWE\n");
    printf("------------------------------------------\n");
    printf("         INICIO DA SESSAO DE RECARGA\n");




   
    printf("Informe seu CPF: ");
    scanf("%s", cpf_motorista);


   
    carregador = 0;
    while (carregador < 1 || carregador > 3) {
        printf("Escolha o carregador (1, 2 ou 3): ");
        scanf("%d", &carregador);


       
        if (carregador < 1 || carregador > 3) {
            printf("  Numero invalido! Digite apenas 1, 2 ou 3.\n\n");
        }
    }
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    strftime(horario, 20, "%d/%m/%Y  %H:%M", t);
   
   
    printf("  SESSAO INICIADA COM SUCESSO!\n");
    printf("  Motorista  : %s\n", cpf_motorista);
    printf("  Carregador : Box %d\n", carregador);
    printf("  Horario  : %s\n", horario);
   
   


    return 0;
}
