#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "admin.h"

void show_header_admin(void) 
{
    system("clear");

    printf(" .d8b.   8888b.     .d8b     d8b.  YPPPPPPY  .d8b     YP \n");
    printf("d8' `8b  88  .db.   88 .8. .8. 88     88     88 .8.   88 \n");
    printf("88ooo88  88   .db.  88  .d8b.  88     88     88  .8.  88 \n");
    printf("88~~~88  88   .db.  88   .8.   88     88     88   .8. 88 \n");
    printf("88   88  88  .db.   88    .    88     88     88    .8.d8 \n");
    printf("YP   YP  888db.     YP         YP  YPPPPPPY  YP     .d8b \n\n");
}

int varredura_de_pastas(void)
{
    struct dirent *de;

    int quantidade_pastas = 0;

    DIR *dr = opendir("../data");

    if (dr == NULL)
    {
        printf("Could not open current directory" );
        exit(1);
    }

    while ((de = readdir(dr)) != NULL)
    {
        if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
        {
            quantidade_pastas++;
        }
    }

    closedir(dr);

    return quantidade_pastas;
}

void backlog_usuarios(void)
{
    FILE *file;
    int quantidade_pastas = varredura_de_pastas();

    if ((file = fopen("../backlog/log_users.bin", "wb")) == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    if (fwrite(&quantidade_pastas, sizeof(int), 1, file) != 1)
    {
        printf("Erro na escrita do arquivo.\n");
    }

    fclose(file);
}

/**
 * LEMBRAR!! APLICAR FUNÇÃO DE RETORNO PARA A LEITURA DOS NOMES DAS PASTAS SALVAS EM DATA
 * ARMAZENAR RETORNO EM ARRAY DE DADOS PARA FACILITAR O ACESSO AS PASTAS
 * UTILIZAR O ARRAY DE DADOS PARA ACESSAR AS INFORMAÇÕES BANCÁRIAS DE CADA USUÁRIO
 */

void quantidade_clientes(void)
{
    FILE *file;
    int quantidade_clientes;

    if ((file = fopen("../backlog/log_users.bin", "rb")) == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    if (fread(&quantidade_clientes, sizeof(int), 1, file) != 1)
    {
        printf("Erro na leitura do arquivo.\n");
    }

    fclose(file);

    show_header_admin();
    printf("Quantidade de clientes cadastrados: %d\n", quantidade_clientes);
}

// void quantidade_clientes_sem_debito(void)
// {
//     // show_header_admin()
//     int quantidade_pastas = varredura_de_pastas();
//     const char *usuarios[quantidade_pastas + 1];

//     struct dirent *de;

//     DIR *dr = opendir("../data");

//     if (dr == NULL)
//     {
//         printf("Não é possível abrir o diretório.\n");
//         exit(1);
//     }

//     int contador = 0;
//     while ((de = readdir(dr)) != NULL)
//     {
//         if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
//         {
//             usuarios[contador] = de->d_name;

//             contador++;
//         }
//     }

//     closedir(dr);
// }

// void quantidade_clientes_com_debito(void)
// {
    // show_header_admin();
// }

// void valor_mais_baixo_em_conta(void)
// {
    // show_header_admin();
// }

// void valor_mais_alto_em_conta(void)
// {
    // show_header_admin();
// }

void opcoes_admin(void)
{
    backlog_usuarios();
    show_header_admin();

    int opcao = 0;

    printf("\nDigite uma das opções abaixo: \n");
    printf("1 - Quantidade de clientes cadastrados.\n");
    printf("2 - Quantidade de clientes sem débito.\n");
    printf("3 - Quantidade de clientes com débito.\n");
    printf("4 - Valor mais baixo em conta.\n");
    printf("5 - Valor mais alto em conta.\n");
    scanf("%d", &opcao);

    if (opcao == 1)
    {
        quantidade_clientes();
    }
    else if (opcao == 2)
    {
        // quantidade_clientes_sem_debito();
    }
    // else if (opcao == 3)
    // {
    //     quantidade_clientes_com_debito();
    // }
    // else if (opcao == 4)
    // {
    //     valor_mais_baixo_em_conta();
    // }
    // else
    // {
    //     valor_mais_alto_em_conta();
    // }
}