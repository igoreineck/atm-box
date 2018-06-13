#import <stdio.h>
#import <stdlib.h>
#import <string.h>
#include "../new-user/new-user.h"
#include "login.h"

int login(void)
{
    show_header_login();

    int i = 0, 
        qnt_usuario,
        status = 0;

    char i_str[5],
         path[40],
         root_path[40], 
         cpf[12], 
         senha[255];

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
        
        strcpy(root_path, path);
        strcat(root_path, "/");
          
        strcat(path, "/user_data.bin");

        struct user *object = malloc(sizeof(struct user));

        FILE * file= fopen(path, "rb");

        if (file != NULL) 
        {
            fread(object, sizeof(struct user), 1, file);
            fclose(file);
        }

        if (strcmp(object->cpf, cpf) == 0 && strcmp(object->password, senha) == 0)
        {
            status = 1;
            informacoes_usuario(root_path);
        }
    }
    if(!status)
    {
        printf("CPF ou senha inválidos\n");
        printf("digite qualquer tecla para voltar ao menu principal\n");
        getchar();
    }

}

void show_header_login(void)
{
    system("clear");

    printf("db       .d88b.   d888b  d888888b d8b   db\n"); 
    printf("88      .8P  Y8. 88' Y8b   `88'   888o  88\n"); 
    printf("88      88    88 88         88    88V8o 88\n"); 
    printf("88      88    88 88  ooo    88    88 V8o88\n"); 
    printf("88booo. `8b  d8' 88. ~8~   .88.   88  V888\n"); 
    printf("Y88888P  `Y88P'   Y888P  Y888888P VP   V8P\n\n\n"); 
}