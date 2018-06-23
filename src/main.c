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

    int system_status = 1;    
    int option = 0;

    while (system_status)
    {
        show_main_header();
        printf("DIGITE UMA DAS OPÇÕES ABAIXO: \n");
        printf("-------------------------------------------------------\n");
        printf("Digite 1 - Para criar uma conta.\n");
        printf("Digite 2 - Para efetuar o login no sistema.\n");
        printf("Digite 3 - Para acessar como Admin.\n");
        printf("Digite 4 - Para Sair do sistema.\n");
        printf("-------------------------------------------------------\n");
        scanf("%d", &option);

        __fpurge(stdin);

        if (option == 1)
        {
            new_user();
        }
        else if (option == 2) 
        {
            login();
        }
        else if  (option == 3) 
        {
            login_admin();
        }
        else 
        {
           system_status = 0; 
        }
    }
}