/* 
    - gcc new-user.c -o teste -w
    - comando para compilar, o -w ignora os warnings gerados pelo __fpurge(stdin)

Métodos:

Opcao 1 - Digitar CPF

Opcao 2 - Digitar Nome

Opcao 3 (Implícita) - Geração automática de senha (6 dígitos) 

* Após criação, retornar os dados do usuário (somente: nome e cpf)

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "new-user.h"

void show_header_signup(void) {
    system("cls");
    system("PAUSE");

    printf(" .o88b.  .d8b.  d8888b.  .d8b.  .d8888. d888888b d8888b.  .d88b.  \n");
    printf("d8P  Y8 d8' `8b 88  `8D d8' `8b 88'  YP `~~88~~' 88  `8D .8P  Y8. \n");
    printf("8P      88ooo88 88   88 88ooo88 `8bo.      88    88oobY' 88    88 \n");
    printf("8b      88~~~88 88   88 88~~~88   `Y8b.    88    88`8b   88    88 \n");
    printf("Y8b  d8 88   88 88  .8D 88   88 db   8D    88    88 `88. `8b  d8' \n");
    printf(" `Y88P' YP   YP Y8888D' YP   YP `8888Y'    YP    88   YD  `Y88P'  \n\n");
}

void save_user(const char *name) {
    char pathname[20] = "../data/";

    strcat(pathname, name);

    mkdir(pathname, 777); 
}

// int info_user(const char *name) {
    // INSERIR AQUI OS MÉTODOS PARA ARMAZENAMENTO DAS INFORMAÇÕES DO USUÁRIO
    // UTILIZAR AS FUNÇÕES DE SALVAMENTO DE ARQUIVOS
    // ENVIAR PARA A PASTA DATA
// }

int new_user(void) {
    show_header_signup();

    char name[30];

    printf("Digite seu nome: ");
    fgets(name, 30, stdin);

    save_user(name);
    // info_user(name);

    return 0;
}

// char password_generate(char *) {}

// int cpf_status = 0;

// struct users {
//     char name[40];
//     char cpf[12];
//     char password[255];
//     char *encrypted_password;
// };

// struct users user;

// system("clear");
// show_header();

// printf("Digite seu nome: ");
// fgets(user.name, 40, stdin);

// __fpurge(stdin);

// while (!cpf_status) {
//     printf("Digite seu CPF: ");
//     fgets(user.cpf, 12, stdin);

//     __fpurge(stdin);

//     if (cpf_verification(user.cpf)) {
//         cpf_status = 1; 
        
//         system("clear");
        
//         show_header();
        
//         printf("Digite seu nome: %s", user.name);
//         printf("Digite seu CPF: %s\n", user.cpf);
//         printf("Digite sua senha: ");
        
//         fgets(user.password, 255, stdin);
        
//         __fpurge(stdin);
        
//     } else {
//         printf("CPF Invalido, Digite novamente\n");
//     }
// }

    // printf("Digite a sua senha com no máximo 6 caracteres: ");
    // fgets(user.password, 255, stdin);

    // __fpurge(stdin);

    // user.encrypted_password = &user.password;
    // // password_generate(encrypted_password);

    // // save_user(user);

    // printf("Sua conta foi criada com sucesso!");