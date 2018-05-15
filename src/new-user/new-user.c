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
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "new-user.h"



//char password_generate(char *);
int cpf_verification(char* cpf) {
    int icpf[12];
    int i, somador = 0, digito1, result1, result2, digito2, valor; 
    //Efetua a conversao de array de char para um array de int.  
    for (i = 0; i < 11; i++) {  
        icpf[i] = cpf[i] - 48;  
    }  
 
    //PRIMEIRO DIGITO.  
 
    for (i = 0; i < 9; i++) {  
        somador += icpf[i] * (10 - i);  
    }  
 
    result1 = somador % 11;  
 
    if ((result1 == 0) || (result1 == 1)) {  
        digito1 = 0;  
    } else {  
        digito1 = 11 - result1;  
    }  
 
    //SEGUNDO DIGITO.  
 
    somador = 0;  
 
    for (i = 0; i < 10; i++) {  
        somador += icpf[i] * (11 - i);  
    }  
 
    valor = (somador / 11) * 11;  
    result2 = somador - valor;  
 
    if ((result2 == 0) || (result2 == 1)) {  
        digito2 = 0;  
    } else {  
        digito2 = 11 - result2;  
    }  
 
    //RESULTADOS DA VALIDACAO.  
 
    if ((digito1 == icpf[9]) && (digito2 == icpf[10])) {  
        return 1;  
    } else {  
        return 0;  
  } 
}

void show_header_signup(void) {
    system("clear");

    printf(" .o88b.  .d8b.  d8888b.  .d8b.  .d8888. d888888b d8888b.  .d88b.  \n");
    printf("d8P  Y8 d8' `8b 88  `8D d8' `8b 88'  YP `~~88~~' 88  `8D .8P  Y8. \n");
    printf("8P      88ooo88 88   88 88ooo88 `8bo.      88    88oobY' 88    88 \n");
    printf("8b      88~~~88 88   88 88~~~88   `Y8b.    88    88`8b   88    88 \n");
    printf("Y8b  d8 88   88 88  .8D 88   88 db   8D    88    88 `88. `8b  d8' \n");
    printf(" `Y88P' YP   YP Y8888D' YP   YP `8888Y'    YP    88   YD  `Y88P'  \n\n");
}

void save_user(const char *name)
{
	// int i;

	// // strcat(pathname, user.name);
	// FILE * fPointer;
	// fPointer = fopen("../data/total.txt", "r");
	// char cQuantidade[2], quantidade[2];

	// while(!feof(fPointer))
	// {
	// 	fgets(cQuantidade, 2, fPointer);
	// 	puts(cQuantidade);
	// }

	
	// for (i = 0; i < 11; i++) {  
    //     quantidade[i] = cQuantidade[i] - 48;  
    // } 

	// int teste = quantidade[0] + 1;

	// fclose(fPointer);

	// FILE * a;
    // int b = 1;
	// a = fopen("../data/total.txt", "w");

	// fprintf(a, "a");

	// fclose(a);	

    //char pathname[20] = "../data/";

    //strcat(pathname, );

    //mkdir(pathname, 777); 
}

// int info_user(const char *name) {
    // INSERIR AQUI OS MÉTODOS PARA ARMAZENAMENTO DAS INFORMAÇÕES DO USUÁRIO
    // UTILIZAR AS FUNÇÕES DE SALVAMENTO DE ARQUIVOS
    // ENVIAR PARA A PASTA DATA
// }

//char* info_user(void) {
//    char name[30];
//    char *namePtr;

//    printf("Digite seu nome: ");
//   fgets(name, 30, stdin);

    // pause();

 //   namePtr = (char *)malloc(sizeof(name));

 //   namePtr = name;

 //   return namePtr;
//}

//int new_user(void) {
//    show_header_signup();

//    char *userPtr;

//    userPtr = info_user();
//    save_user(userPtr);

//    return 0;
//}

// char password_generate(char *) {}

	


//}

int new_user(void) {

	// char password_generate(char *) {}

	int cpf_status = 0, passwordSize = 0 , passsword_verification_status = 0, fPointer;
	char password_verification[255];

	struct users {
		char name[30];
		char cpf[13];
		char password[255];
		//char *encrypted_password;
	};

	struct users user;

	show_header_signup();

	printf("Digite seu nome: ");
	fgets(user.name, 30, stdin);

	save_user(user.name);

	__fpurge(stdin);

	while (!cpf_status)
	{
		printf("Digite seu CPF: ");
		fgets(user.cpf, 13, stdin);

		__fpurge(stdin);

	 	if (cpf_verification(user.cpf))
		{
	 		cpf_status = 1; 	

	 		show_header_signup();		

	 		printf("Digite seu nome: %s", user.name);
	 		printf("Digite seu CPF: %s", user.cpf);
			printf("Digite a sua senha com 6 caracteres: ");
			fgets(user.password, 255, stdin);
			printf("%s", user.password);
		
			__fpurge(stdin);

			if(strlen(user.password) == 7)
			{
				while(!passwordSize)
				{
					show_header_signup();		

					printf("Digite seu nome: %s", user.name);
					printf("Digite seu CPF: %s", user.cpf);
					printf("Confirme sua senha: ");
					fgets(password_verification, 255, stdin);
					__fpurge(stdin);
					
					if(strlen(password_verification) == 7)
					{
						if(strcmp(user.password, password_verification) == 0)
						{
							passwordSize = 1;

							
							printf("acabo");

						}
						else
						{
							break;
						}
					}
					else
					{
						break;
					}
				}
			}

			while(!passwordSize)
			{		
				show_header_signup();		

				printf("Digite seu nome: %s", user.name);
				printf("Digite seu CPF: %s\n", user.cpf);
				printf("Digite a sua senha com 6 caracteres: ");
				fgets(user.password, 255, stdin);
				__fpurge(stdin);

				if(strlen(user.password) == 7)
				{
					while(!passwordSize)
					{
						show_header_signup();		

						printf("Digite seu nome: %s", user.name);
						printf("Digite seu CPF: %s\n", user.cpf);
						printf("Confirme sua senha: ");
						fgets(password_verification, 255, stdin);
						__fpurge(stdin);
						
						if(strlen(password_verification) == 7)
						{
							if(strcmp(user.password, password_verification) == 0)
							{
								passwordSize = 1;
							}
							else
							{
								break;
							}
						}
						else
						{
							break;
						}
					}
				}
			}

	 	}
		else
		{
	 		printf("CPF Invalido, Digite novamente\n");
	 	}
	}
	char pathname[20] = "../data/batata/data.txt";

	// strcat(pathname, user.name);
	fPointer = fopen(pathname, "w");

	fprintf(fPointer, user.name);
	fprintf(fPointer, user.cpf);
	fprintf(fPointer, user.password);

	fclose(fPointer);		
}


     //user.encrypted_password = &user.password;


     // password_generate(encrypted_password);
     // save_user(user);

    // printf("Sua conta foi criada com sucesso!");