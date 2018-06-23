#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../new-user/new-user.h"
#include "login.h"

void show_header_admin_login(void)
{
    system("clear");

    printf("db       .d88b.   d888b  d888888b d8b   db\n"); 
    printf("88      .8P  Y8. 88' Y8b   `88'   888o  88\n"); 
    printf("88      88    88 88         88    88V8o 88\n"); 
    printf("88      88    88 88  ooo    88    88 V8o88\n"); 
    printf("88booo. `8b  d8' 88. ~8~   .88.   88  V888\n"); 
    printf("Y88888P  `Y88P'   Y888P  Y888888P VP   V8P\n\n\n"); 
}

int login_admin(void)
{
    show_header_admin_login();

    int status = 0;

    struct admin_info *a_info_saved = (char *)malloc(sizeof(struct admin_info));
    struct admin_info *login = (char *)malloc(sizeof(struct admin_info));

    FILE *file;

    file = fopen("../data_admin/admin_info.bin", "rb");

    if (file == NULL)
    {
        printf("Erro ao abrir o arquivo.\n");
        exit(1);
    }

    fread(a_info_saved, sizeof(struct admin_info), 1, file);

    printf("Digite o ID: ");
    scanf("%s", &login->admin_name);

    __fpurge(stdin);

    printf("Digite a senha: ");
    scanf("%s", &login->admin_pass);

    __fpurge(stdin);

    if (
        strcmp(a_info_saved->admin_name, login->admin_name) == 0 && 
        strcmp(a_info_saved->admin_pass, login->admin_pass) == 0)
    {
        status = 1;

        fclose(file);
        free(a_info_saved);
        free(login);

        opcoes_admin();
    }
    else 
    {
        if (!status)
        {
            printf("CPF ou senha inválidos\n");
            printf("digite qualquer tecla para voltar ao menu principal\n");
            getchar();
        }
    }
}