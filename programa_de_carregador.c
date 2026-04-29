#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>


int main() {


   
    char cpf_motorista[12];
    int carregador;
    char horario[20];
    time_t inicio, fim;
    double segundos_usados;
    double minutos_usados;
    float preco_por_minuto = 1.50;
    float total;
    
   
   
    printf("     CHARGERID INTELLIGENCE - GOODWE\n");
    printf("------------------------------------------\n");
    printf("       INICIO DA SESSAO DE RECARGA\n");




   
   while (1) {
    printf("Informe seu CPF (apenas numeros): ");
    scanf("%s", cpf_motorista);

    if (strlen(cpf_motorista) == 11) {
        break;  
    } else {
        printf("  CPF invalido! Digite apenas os 11 numeros.\n\n");
    }
}


   
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

    inicio = time(NULL);
    time_t agora = time(NULL);
    struct tm *t = localtime(&agora);
    strftime(horario, 20, "%d/%m/%Y  %H:%M", t);

   
   
    printf("  SESSAO INICIADA COM SUCESSO!\n");
    printf("  Usuario  : %s\n", cpf_motorista);
    printf("  Carregador : Box %d\n", carregador);
    printf("  Horario  : %s\n", horario);

    printf("Pressione ENTER para desconectar o carregador...\n");
    getchar();
    getchar();

    fim = time(NULL);

    segundos_usados = difftime(fim, inicio);
    minutos_usados = segundos_usados /60 ;
    total = minutos_usados * preco_por_minuto;
    printf("Horario finalizado %s", inicio);
    printf("Esse e o valor total: %f\n", total);
    

    
    return 0;
}
