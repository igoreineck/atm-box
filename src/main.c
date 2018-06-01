/* 
COMANDO PARA EXECUTAR MÚLTIPLOS ARQUIVOS EM C: gcc -Wall arquivo1.c arquivo2.c -o app

Métodos do trabalho

Opcao 1 - Admin
    abrir funcoes

Opcao 2 - User
    abrir funcoes
    
Opcao 3 - New user
    abrir funcoes
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "new-user/new-user.h"

void show_main_header(void);

void show_main_header(void)
{
    system("clear");

    printf("888888  d8.     88  d888888  .d88b.  \n");
    printf("  88    888.    88  88      .8P  Y8. \n");
    printf("  88    88.8.   88  88      88    88 \n");
    printf("  88    88 .8.  88  88888   88    88 \n");
    printf("  88    88  .8. 88  88      88    88 \n");
    printf("  88    88   .8.88  88      `8b  d8' \n");
    printf("888888  88    .88b  88       `Y88P'  \n\n");
}

int main(void) {
    
    int option = 0;

    show_main_header();
    printf("\nDigite uma das opções abaixo: \n");
    printf("Digite 1 - Para criar uma conta. \n");
    printf("Digite 2 - Para acessar as informações da sua conta. \n");
    printf("Digite 3 - Para acessar as opções de Administrador. \n");
    scanf("%d", &option);

    __fpurge(stdin);

    if (option == 1)
    {
        new_user();
    }
    else if (option == 2) 
    {
        informacoes_usuario();
    }
    else
    {
        opcoes_admin();
    }
}