#import <stdio.h>
#import <stdlib.h>
#include "../new-user/new-user.h"
#include "login.h"

int login(void)
{

    int i = 0, qnt_usuario;
    char i_str[5];
    char path[40], cpf[12], senha[255];

    printf("CPF: ");
    fgets(cpf, 12, stdin);
    __fpurge(stdin);

    printf("senha: ");
    fgets(senha, 255, stdin);
    __fpurge(stdin);

    FILE *file_qnt_user;
    file_qnt_user = fopen("../src/new-user/total.bin", "rb");
    fread(&qnt_usuario, 1 , sizeof(int), file_qnt_user);
    fclose(file_qnt_user);

    for (i = 0; i < qnt_usuario; i++)
    {
        snprintf(i_str, 5, "%d", i);
        strcpy(path,"../data/usuario_");
        strcat(path, i_str);
        strcat(path, "/user_data.bin");

        struct user *object=malloc(sizeof(struct user));
        FILE * file= fopen(path, "rb");
        if (file != NULL) {
            fread(object, sizeof(struct user), 1, file);
            fclose(file);
        }

        if(strcmp(object->cpf, cpf) == 0 && strcmp(object->password, senha) == 0)
        {
            informacoes_usuario();
        }
    }

    printf("CPF ou senha inválidos\n");

    exit(1);
}