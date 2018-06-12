#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
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

void acessar_informacoes_conta(void) 
{
    struct path_usuario *Arquivo = malloc(sizeof(struct path_usuario));
    struct usuario *Usuario = malloc(sizeof(struct usuario));

    strcpy(Arquivo->nome, "nome.bin");
    strcpy(Arquivo->cpf, "cpf.bin");
    strcpy(Arquivo->senha, "senha.bin");

    FILE *arquivo;

    char absolute_path[] = "../data/usuario_0/";

    char absolute_path_copy[strlen(absolute_path)];
    strcpy(absolute_path_copy, absolute_path);
    strcat(absolute_path_copy, Arquivo->nome);

    struct usuario *objeto = malloc(sizeof(struct usuario));

    arquivo = fopen(absolute_path_copy, "rb");

    if (arquivo != NULL)
    {
        fread(objeto->nome, sizeof(Usuario->nome), 1, arquivo);
        fclose(arquivo);
        memset(absolute_path_copy, 0, sizeof absolute_path_copy);
    }
    else
    {
        printf("Não foi possível abrir o arquivo nome.bin\n");
        exit(1);
    }

    strcpy(absolute_path_copy, absolute_path);
    strcat(absolute_path_copy, Arquivo->cpf);

    arquivo = fopen(absolute_path_copy, "rb");

    if (arquivo != NULL)
    {
        fread(objeto->cpf, sizeof(Usuario->cpf), 1, arquivo);
        fclose(arquivo);
        memset(absolute_path_copy, 0, sizeof absolute_path_copy);
    }
    else
    {
        printf("Não foi possível abrir o arquivo cpf.bin\n");
        exit(2);
    }

    strcpy(absolute_path_copy, absolute_path);
    strcat(absolute_path_copy, Arquivo->senha);

    arquivo = fopen(absolute_path_copy, "rb");

    if (arquivo != NULL)
    {
        fread(objeto->senha, sizeof(Usuario->senha), 1, arquivo);
        fclose(arquivo);
        memset(absolute_path_copy, 0, sizeof absolute_path_copy);
    }
    else
    {
        printf("Não foi possível abrir o arquivo senha.bin\n");
        exit(3);
    }

    show_header();

    printf("INFORMAÇÕES DA CONTA\n");
    printf("------------------------\n");
    printf("Nome: %s", objeto->nome);
    printf("CPF: %s\n", objeto->cpf);
    printf("Senha: %s", objeto->senha);
    printf("------------------------\n");

    printf("\n");

    free(Arquivo);
    free(Usuario);
    free(objeto);
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
        // criar_modulo_de_transacoes();
    }
}

void acessar_informacoes_monetarias(void) 
{
    int opcao = 0;

    show_header();
    printf("\nDigite uma op��o abaixo: \n");
    printf("1 - Saldo \n");
    printf("2 - Dep�sito \n");
    printf("3 - Saque \n");
    printf("4 - Extrato da conta \n");
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
    else if (opcao == 3)
    {
        saque_usuario();
    }
    else 
    {
        // modificar_extrato_da_conta();
        acessar_extrato_da_conta();
    }
}

void saldo_usuario(void)
{
    FILE *file;
    float valor_saldo;

    if ((file = fopen("../data/usuario_0/caixa.bin", "rb")) == NULL)
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
    printf("Saldo: %0.2f \n", valor_saldo);
}

void deposito_usuario(void)
{
    show_header();

    FILE *file;
    float valor_para_deposito = 0;
    float saldo_existente = 0;
    char path_deposito[] = "../data/usuario_0/caixa.bin";

    printf("\nDigite um valor para deposito: ");
    scanf("%f", &valor_para_deposito);

    file = fopen(path_deposito, "rb");

    if (file == NULL)
    {
        file = fopen(path_deposito, "w+b");

        fwrite(&valor_para_deposito, sizeof(float), 1, file);
    }
    else
    {
        fread(&saldo_existente, sizeof(float), 1, file);

        file = fopen(path_deposito, "w+b");

        valor_para_deposito = valor_para_deposito + saldo_existente;

        fwrite(&valor_para_deposito, sizeof(float), 1, file);
    }

    fclose(file);

    printf("\nDepósito efetuado com sucesso!\n");

    struct estrutura *depositar = malloc(sizeof(struct estrutura));
    strcpy(depositar->tipo, "D");
    depositar->valor = valor_para_deposito;
    strcpy(depositar->data, "12/06/2018");

    adicionar_transacao(depositar);

    free(depositar);
}

void saque_usuario(void)
{
    show_header();

    FILE *file;
    float valor_para_saque;
    float saldo;

    printf("\nDigite um valor para saque: ");
    scanf("%f", &valor_para_saque);

    if ((file = fopen("../data/usuario_0/caixa.bin", "rb")) == NULL)
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

    if (saldo > 0) 
    {
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

    if ((file = fopen("../data/usuario_0/caixa.bin", "wb")) == NULL)
    {
        printf("Erro na abertura do arquivo.\n");
    }

    if (fwrite(&saldo, sizeof(float), 1, file) != 1)
    {
        printf("Erro na escrita do arquivo.\n");
    }

    fclose(file);

    show_header();
    printf("\nNovo saldo: %0.2f \n", saldo);

    struct estrutura *sacar = malloc(sizeof(struct estrutura));

    strcpy(sacar->tipo, "S");
    sacar->valor = valor_para_saque;
    strcpy(sacar->data, "12/06/2018");

    adicionar_transacao(sacar);

    free(sacar);
}

int gerar_registro_da_transacao(void)
{
    FILE *arquivo;
    int contador;

    char path_transacoes[] = "../data/usuario_0/backlog_transacoes/log_transacoes.bin";

    arquivo = fopen(path_transacoes, "rb");

    if (arquivo == NULL)
    {
        arquivo = fopen(path_transacoes, "w+b");

        contador = 1;

        fwrite(&contador, sizeof(int), 1, arquivo);
    }
    else
    {
        fread(&contador, sizeof(int), 1, arquivo);

        contador++;

        arquivo = fopen(path_transacoes, "w+b");

        fwrite(&contador, sizeof(int), 1, arquivo);
    }

    fclose(arquivo);

    return contador;
}

void adicionar_transacao(struct estrutura *transacao)
{
    // criar_modulo_de_transacoes();
    int registro_da_transacao = gerar_registro_da_transacao();

    char path_transacoes[] = "../data/usuario_0/transacoes/transacao_";

    char aux[sizeof(registro_da_transacao)];
    snprintf(aux, sizeof(registro_da_transacao), "%d", registro_da_transacao);

    strcat(path_transacoes, aux);
    strcat(path_transacoes, ".bin");

    FILE *arquivo;

    arquivo = fopen(path_transacoes, "rb");

    if (arquivo == NULL)
    {
        arquivo = fopen(path_transacoes, "w+b");

        fwrite(transacao, sizeof(struct estrutura), 1, arquivo);
    }

    fclose(arquivo);
}

void acessar_extrato_da_conta()
{
    struct dirent *entry;

    char path_transacao[] = "../data/usuario_0/transacoes/";
    char copy_path_transacao[strlen(path_transacao)];

    FILE *arquivo;

    DIR *diretorio = opendir("../data/usuario_0/transacoes");

    if (diretorio == NULL)
    {
        printf("Erro ao abrir o diretorio.\n");
        return;
    }

    while ((entry = readdir(diretorio)) != NULL)
    {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
        {
            struct estrutura *objeto = malloc(sizeof(struct estrutura));
            
            strcpy(copy_path_transacao, path_transacao);
            strcat(copy_path_transacao, entry->d_name);

            arquivo = fopen(copy_path_transacao, "rb");

            if (arquivo != NULL)
            {
                fread(objeto, sizeof(struct estrutura), 1, arquivo);

                printf("[Tipo da transação: %s | ", objeto->tipo);
                printf("Valor da transação: %0.2f | ", objeto->valor);
                printf("Data da transação: %s]\n", objeto->data);
            }

            memset(copy_path_transacao, 0, sizeof copy_path_transacao);

            fclose(arquivo);
            free(objeto);
        }
    }

    closedir(diretorio);
}