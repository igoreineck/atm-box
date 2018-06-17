#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "info.h"
#include <time.h>

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

void acessar_informacoes_conta(char * path) 
{
    char pathCopy[strlen(path)];
    char absolute_path[100];
    
    strcpy(pathCopy, path);

    struct path_usuario *Arquivo = malloc(sizeof(struct path_usuario));
    struct usuario *Usuario = malloc(sizeof(struct usuario));

    strcpy(Arquivo->file, "user_data.bin");

    FILE *arquivo;

    strcpy(absolute_path, pathCopy);

    char absolute_path_copy[100];
    strcpy(absolute_path_copy, absolute_path);
    strcat(absolute_path_copy, Arquivo->file);

    struct usuario *objeto = malloc(sizeof(struct usuario));

    arquivo = fopen(absolute_path_copy, "rb");

    if (arquivo != NULL)
    {
        fread(objeto, sizeof(struct usuario), 1, arquivo);
        fclose(arquivo);
    }
    else
    {
        printf("Não foi possível abrir o arquivo nome.bin\n");
        exit(1);
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

void informacoes_usuario(char * path) 
{
    char pathCopy[strlen(path)];
    strcpy(pathCopy, path);
    int status_user = 1,
        did_action = 0;
    
    while(status_user)
    {
        if(did_action)
        {
            printf("\ndigite qualquer tecla para voltar ao menu\n");
            getchar();
        }
        did_action = 1;
        int opcao = 0;

        show_header();
    
        printf("\nDigite uma das opções abaixo: \n");
        printf("1 - Informações da Conta \n");
        printf("2 - Informações monetárias da Conta \n");
        printf("3 - Deslogar \n");
        // printf("3 - Editar conta") -> Adicionar posteriormente
        scanf("%d", &opcao);

        __fpurge(stdin);

        if (opcao == 1) 
        {
            acessar_informacoes_conta(pathCopy);
        } 
        else if (opcao == 2)
        {
            acessar_informacoes_monetarias(pathCopy);
        }
        else if (opcao == 3)
        {
            status_user = 0;
        }
    }
}

void acessar_informacoes_monetarias(char * path) 
{
    int opcao = 0;
    char pathCopy[strlen(path)];
    
    strcpy(pathCopy, path);
    
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
        saldo_usuario(pathCopy);
    }
    else if (opcao == 2)
    {
        deposito_usuario(pathCopy);
    }
    else if (opcao == 3)
    {
        saque_usuario(pathCopy);
    }
    else 
    {
        // modificar_extrato_da_conta();
        acessar_extrato_da_conta(pathCopy);
    }
}

char *exibir_data(void)
{
    time_t current_time;
    char *c_time_string;

    current_time = time(NULL);

    if (current_time == ((time_t)-1))
    {
        (void) fprintf(stderr, "Failure to obtain the current time.\n");
        exit(EXIT_FAILURE);
    }

    c_time_string = ctime(&current_time);

    if (c_time_string == NULL)
    {
        (void) fprintf(stderr, "Failure to convert the current time.\n");
        exit(EXIT_FAILURE);
    }

    return c_time_string;
}

void saldo_usuario(char * path)
{
    show_header();

    FILE *file;
    float valor_saldo;    
    char pathCopy[strlen(path)+15];
    
    strcpy(pathCopy, path);
    strcat(pathCopy, "caixa.bin");

    printf("Url: %s\n", pathCopy);

    if ((file = fopen(pathCopy, "rb")) == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    if (fread(&valor_saldo, sizeof(float), 1, file) != 1)
    {
        printf("Erro na leitura do arquivo.\n");
    }

    fclose(file);

    printf("Saldo: %0.2f \n", valor_saldo);
}

void deposito_usuario(char * path)
{
    show_header();

    FILE *file;
    float valor_para_deposito = 0;
    float saldo_existente = 0;
    char pathCopy[strlen(path)];
    char pathCopyAlso[strlen(path)];
    const char *data_atual; 
    data_atual = exibir_data();
    
    strcpy(pathCopy, path);
    strcpy(pathCopyAlso, path);

    strcat(pathCopy, "caixa.bin");


    printf("\nDigite um valor para deposito: ");
    scanf("%f", &valor_para_deposito);

    file = fopen(pathCopy, "rb");

    if (file == NULL)
    {
        file = fopen(pathCopy, "w+b");

        fwrite(&valor_para_deposito, sizeof(float), 1, file);
    }
    else
    {
        fread(&saldo_existente, sizeof(float), 1, file);

        file = fopen(pathCopy, "w+b");

        valor_para_deposito = valor_para_deposito + saldo_existente;

        fwrite(&valor_para_deposito, sizeof(float), 1, file);
    }

    fclose(file);

    printf("\nDepósito efetuado com sucesso!\n");

    struct estrutura *depositar = malloc(sizeof(struct estrutura));
    strcpy(depositar->tipo, "Deposito");
    depositar->valor = valor_para_deposito;
    strcpy(depositar->data, data_atual);

    adicionar_transacao(depositar, pathCopyAlso);

    free(depositar);
    getchar();
}

void saque_usuario(char * path)
{
    show_header();

    FILE *file;
    float valor_para_saque;
    float saldo;
    char pathCopy[strlen(path)];
    char pathCopyAlso[strlen(path)];
    const char *data_atual;
    data_atual = exibir_data();

    strcpy(pathCopy, path);
    strcpy(pathCopyAlso, path);
    strcat(pathCopy, "caixa.bin");

    printf("\nDigite um valor para saque: ");
    scanf("%f", &valor_para_saque);

    if ((file = fopen(pathCopy, "rb")) == NULL)
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

    if ((file = fopen(pathCopy, "wb")) == NULL)
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

    strcpy(sacar->tipo, "Saque");
    sacar->valor = valor_para_saque;
    strcpy(sacar->data, data_atual);

    adicionar_transacao(sacar, pathCopyAlso);

    free(sacar);
    getchar();
}

int gerar_registro_da_transacao(char * path)
{
    FILE *arquivo;
    int contador;
    char pathCopy[100];
    
    strcpy(pathCopy, path);
    strcat(pathCopy, "backlog_transacoes/log_transacoes.bin");

    arquivo = fopen(pathCopy, "rb");

    if (arquivo == NULL)
    {
        arquivo = fopen(pathCopy, "w+b");

        contador = 1;

        fwrite(&contador, sizeof(int), 1, arquivo);
    }
    else
    {
        fread(&contador, sizeof(int), 1, arquivo);

        contador++;

        arquivo = fopen(pathCopy, "w+b");

        fwrite(&contador, sizeof(int), 1, arquivo);
    }

    fclose(arquivo);

    return contador;
}

void adicionar_transacao(struct estrutura *transacao, char * path)
{
    char pathCopy[100];

    strcpy(pathCopy, path);

    int registro_da_transacao = gerar_registro_da_transacao(pathCopy);

    strcat(pathCopy, "transacoes/transacao_");

    char aux[sizeof(registro_da_transacao)];
    snprintf(aux, sizeof(registro_da_transacao), "%d", registro_da_transacao);

    strcat(pathCopy, aux);
    strcat(pathCopy, ".bin");

    FILE *arquivo;

    arquivo = fopen(pathCopy, "rb");

    if (arquivo == NULL)
    {
        arquivo = fopen(pathCopy, "w+b");

        fwrite(transacao, sizeof(struct estrutura), 1, arquivo);
    }

    fclose(arquivo);
}

void acessar_extrato_da_conta(char * path)
{
    struct dirent *entry;

    char pathCopy[100];
    char copy_path_transacao[100];
    
    strcpy(pathCopy, path);
    strcat(pathCopy, "transacoes/");

    FILE *arquivo;

    DIR *diretorio = opendir(pathCopy);

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
            
            strcpy(copy_path_transacao, pathCopy);
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