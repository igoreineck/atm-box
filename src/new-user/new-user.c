//gcc new-user.c -o teste -w
// comando para compilar, o -w ignora os warnings gerados pelo __fpurge(stdin)

#include <stdio.h>
#include "new-user.h"
/* 
Métodos:

Opcao 1 - Digitar CPF

Opcao 2 - Digitar Nome

Opcao 3 (Implícita) - Geração automática de senha (6 dígitos) 

* Após criação, retornar os dados do usuário (somente: nome e cpf)

*/
// void save_user(void)
// {
   // FILE *file;

     // file = fopen("contas/igor/deposito.txt");

     // if (file != NULL)
// }

// char password_generate(char *) {}




int cpf_status = 0;

struct users {
    char name[40];
    char cpf[12];
    char password[255];
    char *encrypted_password;
};

struct users user;

system("clear");
show_header();

printf("Digite seu nome: ");
fgets(user.name, 40, stdin);

__fpurge(stdin);

while (!cpf_status) {
    printf("Digite seu CPF: ");
    fgets(user.cpf, 12, stdin);

    __fpurge(stdin);

    if (cpf_verification(user.cpf)) {
        cpf_status = 1; 
        
        system("clear");
        
        show_header();
        
        printf("Digite seu nome: %s", user.name);
        printf("Digite seu CPF: %s\n", user.cpf);
        printf("Digite sua senha: ");
        
        fgets(user.password, 255, stdin);
        
        __fpurge(stdin);
        
    } else {
        printf("CPF Invalido, Digite novamente\n");
    }
}

    // printf("Digite a sua senha com no máximo 6 caracteres: ");
    // fgets(user.password, 255, stdin);

    // __fpurge(stdin);

    // user.encrypted_password = &user.password;
    // // password_generate(encrypted_password);

    // // save_user(user);

    // printf("Sua conta foi criada com sucesso!");
