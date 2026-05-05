#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int main() {

    char cpf_motorista[12];
    int carregador;
    char horario[20];
    time_t inicio, fim;
    double segundos_usados = 0;
    double minutos_usados = 0;
    float preco_por_minuto = 1.50;
    float total;

    int sessao_ativa = 0;
    int carregador_livre = 1;
    int veiculo_conectado = 0;

    float potencia_kw;
    float min_kw, max_kw;

    int tipo_recarga;
    float meta_tempo = 0;
    float meta_energia = 0;
    float energia_total = 0;

    int forma_pagamento;
    float saldo_usuario = 50.0;

    float capacidade_bateria;

    float porcentagem_inicial = 0;
    float porcentagem_final = 0;

    printf("     CHARGERID INTELLIGENCE - GOODWE\n");

    
    while (1) {
        printf("Informe seu CPF: ");
        scanf("%s", cpf_motorista);

        if (strlen(cpf_motorista) == 11) break;
        printf("CPF invalido!\n\n");
    }

    printf("Informe a capacidade da bateria (kWh): ");
    scanf("%f", &capacidade_bateria);

    
    printf("\n1 carregador - CCS2 (50kW - 350 kW)\n");
    printf("2 carregador- AC (7kW - 22kW)\n");
    printf("3 carregador- CHAdeMO (50KW - 50kW)\n");
    scanf("%d", &carregador);

    while (carregador < 1 || carregador > 3) {
        printf("Numero invalido!\n");
        scanf("%d", &carregador);
    }

    if (carregador == 1) {
        min_kw = 50; max_kw = 350;
    } else if (carregador == 2) {
        min_kw = 7; max_kw = 22;
    } else {
        min_kw = 50; max_kw = 50;
    }

    do {
        printf("Escolha a potencia (%.0f a %.0f kW): ", min_kw, max_kw);
        scanf("%f", &potencia_kw);
    } while (potencia_kw < min_kw || potencia_kw > max_kw);

    printf("Veiculo conectado? (1=sim, 0=nao): ");
    scanf("%d", &veiculo_conectado);

    printf("\nTipo de recarga:\n");
    printf("1 - Por tempo\n");
    printf("2 - Por energia\n");
    printf("3 - Ate 100%%\n");
    scanf("%d", &tipo_recarga);

    if (tipo_recarga == 1) {
        printf("Tempo desejado (min): ");
        scanf("%f", &meta_tempo);
    } 
    else if (tipo_recarga == 2) {
        printf("Energia desejada (kWh): ");
        scanf("%f", &meta_energia);
    } 
    else {
        printf("Informe a porcentagem atual da bateria (0 a 100): ");
        scanf("%f", &porcentagem_inicial);

        while (porcentagem_inicial < 0 || porcentagem_inicial > 100) {
            printf("Valor invalido! Digite entre 0 e 100: ");
            scanf("%f", &porcentagem_inicial);
        }
    }

    if (carregador_livre == 1 && veiculo_conectado == 1) {

        sessao_ativa = 1;
        carregador_livre = 0;

        inicio = time(NULL);
        struct tm *t = localtime(&inicio);
        strftime(horario, 20, "%d/%m/%Y %H:%M", t);

        printf("\nSESSAO INICIADA!\n");
        printf("Usuario: %s\n", cpf_motorista);
        printf("Carregador: %d\n", carregador);
        printf("Potencia: %.1f kW\n", potencia_kw);
        printf("Horario: %s\n", horario);

    } else {
        printf("\nNao foi possivel iniciar.\n");
        return 0;
    }

    printf("\nCarregando... pressione ENTER para cancelar\n");

    time_t ultimo = time(NULL);

    while (1) {

        time_t agora = time(NULL);

        if (agora != ultimo) {

            ultimo = agora;

            segundos_usados = difftime(agora, inicio);
            minutos_usados = segundos_usados / 60;

            energia_total = potencia_kw * (minutos_usados / 60);

            if (tipo_recarga == 3) {
                porcentagem_final = porcentagem_inicial +
                    (energia_total / capacidade_bateria) * 100;
            } else {
                porcentagem_final =
                    (energia_total / capacidade_bateria) * 100;
            }

            if (porcentagem_final > 100) porcentagem_final = 100;

            printf("Bateria: %.2f%% | Tempo: %.1f min | Energia: %.2f kWh\r",
                   porcentagem_final, minutos_usados, energia_total);

            if (kbhit()) {
                char tecla = getch();
                if (tecla == 13) {
                    printf("\n\nRecarga interrompida pelo usuario!\n");
                    break;
                }
            }

            if (tipo_recarga == 1 && minutos_usados >= meta_tempo) {
                printf("\nTempo atingido!\n");
                break;
            }

            if (tipo_recarga == 2 && energia_total >= meta_energia) {
                printf("\nEnergia atingida!\n");
                break;
            }

            if (tipo_recarga == 3 && porcentagem_final >= 100) {
                printf("\nCarga completa!\n");
                break;
            }
        }
    }

    fim = time(NULL);

    total = minutos_usados * preco_por_minuto;

    printf("\n\nSESSAO FINALIZADA\n");
    printf("Tempo: %.2f minutos\n", minutos_usados);
    printf("Energia: %.2f kWh\n", energia_total);

    if (tipo_recarga == 3) {

        printf("Bateria inicial: %.2f%%\n", porcentagem_inicial);
        printf("Bateria final: %.2f%%\n", porcentagem_final);

        printf("Carga adicionada: %.2f%%\n",
            (energia_total / capacidade_bateria) * 100);
    } else {
        printf("Equivalente carregado: %.2f%%\n", porcentagem_final);
    }

    printf("Valor: R$ %.2f\n", total);

    FILE *arquivo = fopen("historico.txt", "a");
    if (arquivo != NULL) {
        fprintf(arquivo, "CPF: %s | Tempo: %.2f | Energia: %.2f | Valor: %.2f\n",
                cpf_motorista, minutos_usados, energia_total, total);
        fclose(arquivo);
    }

   printf("\n----PAGAMENTO----\n");
printf("Valor total: R$ %.2f\n", total);

printf("\nEscolha a forma de pagamento:\n");
printf("1 - Cartao de credito\n");
printf("2 - Pix\n");
printf("3 - Saldo na carteira\n");


while (scanf("%d", &forma_pagamento) != 1 || forma_pagamento < 1 || forma_pagamento > 3) {
    printf("Opcao invalida! Escolha 1, 2 ou 3: ");
    while (getchar() != '\n'); 
}

switch (forma_pagamento) {

    case 1:
        printf("\nPagamento aprovado no cartao!\n");
        break;

    case 2:
        printf("\nPagamento via Pix realizado com sucesso!\n");
        break;

    case 3:

        if (saldo_usuario >= total) {

            saldo_usuario -= total;

            printf("\nPagamento realizado com saldo!\n");
            printf("Saldo restante: R$ %.2f\n", saldo_usuario);

        } else {

            printf("\nSaldo insuficiente!\n");

            
            do {
                printf("Escolha outra forma (1=Cartao, 2=Pix): ");
            } while (scanf("%d", &forma_pagamento) != 1 ||
                     (forma_pagamento != 1 && forma_pagamento != 2));

            if (forma_pagamento == 1) {
                printf("\nPagamento aprovado no cartao!\n");
            } else {
                printf("\nPagamento via Pix realizado com sucesso!\n");
            }
        }

        break;
}
    return 0;
}