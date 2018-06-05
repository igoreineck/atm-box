#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "info.h"

void show_header(void) 
{
    system("clear");

    printf("888888  d8.     88  d888888  .d88b.  \n");
    printf("  88    888.    88  88      .8P  Y8. \n");
    printf("  88    88 .8.  88  88888   88    88 \n");
    printf("  88    88  .8. 88  88      88    88 \n");
    printf("  88    88   .8.88  88      `8b  d8' \n");
    printf("888888  88    .88b  88       `Y88P'  \n\n");
}

void saldo_usuario(void)
{
    FILE *file;
    float valor_saldo;

    if ((file = fopen("../data/usuario/caixa.bin", "rb")) == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    if (fread(&valor_saldo, sizeof(float), 1, file) != 1)
    {
        printf("Erro na leitura do arquivo.\n");
    }

    fclose(file);

    show_header();
    printf("Saldo: %0.4f \n", valor_saldo);
}

void deposito_usuario(void)
{
    FILE *file;
    float valor_para_deposito;

    show_header();
    printf("\nDigite um valor para deposito: ");
    scanf("%f", &valor_para_deposito);

    if ((file = fopen("../data/usuario/caixa.bin", "wb")) == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
        exit(1);
    }

    if (fwrite(&valor_para_deposito, sizeof(float), 1, file) != 1)
    {
        printf("Erro na escrita do arquivo.\n");
    }
    else 
    {
        show_header();
        printf("\nDepósito efetuado com sucesso!\n");
    }

    fclose(file);
}

void saque_usuario(void)
{
    FILE *file;
    float valor_para_saque;
    float saldo;

    show_header();
    printf("\nDigite um valor para saque: ");
    scanf("%f", &valor_para_saque);

    if ((file = fopen("../data/usuario/caixa.bin", "rb")) == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
    }

    if (fread(&saldo, sizeof(float), 1, file) != 1)
    {
        printf("Erro na escrita do arquivo\n");
    }

    fclose(file);

    show_header();
    printf("\nSaldo atual: %0.4f \n", saldo);

    if (saldo > 0) {
        saldo -= valor_para_saque;
    }
    else if (saldo == 0)
    {
        show_header();
        printf("\nSeu saldo está zerado. Não será possível realizar um saque.\n");
    }
    else 
    {
        show_header();
        printf("\nSeu saldo está negativo. Não será possível realizar um saque.\n");
    }

    if ((file = fopen("../data/usuario/caixa.bin", "wb")) == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
    }

    if (fwrite(&saldo, sizeof(float), 1, file) != 1)
    {
        printf("Erro na escrita do arquivo.\n");
    }

    fclose(file);

    show_header();
    printf("\nNovo saldo: %0.4f \n", saldo);
}

void acessar_informacoes_monetarias(void) 
{
    int opcao = 0;

    show_header();
    printf("\nDigite uma op��o abaixo: \n");
    printf("1 - Saldo \n");
    printf("2 - Dep�sito \n");
    printf("3 - Saque \n");
    scanf("%d", &opcao);

    __fpurge(stdin);

    if (opcao == 1) 
    {
        saldo_usuario();
    }
    else if (opcao == 2)
    {
        deposito_usuario();
    }
    else
    {
        saque_usuario();
    }
}

void acessar_informacoes_conta(void) 
{

}

void informacoes_usuario(void) 
{
    int opcao = 0;

    show_header();
    printf("\nDigite uma das opções abaixo: \n");
    printf("1 - Informações da Conta \n");
    printf("2 - Informações monetárias da Conta \n");
    // printf("3 - Editar conta") -> Adicionar posteriormente
    scanf("%d", &opcao);

    __fpurge(stdin);

    if (opcao == 1) 
    {
        acessar_informacoes_conta();
    } 
    else if (opcao == 2)
    {
        acessar_informacoes_monetarias();
    }
}

