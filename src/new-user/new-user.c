#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include "new-user.h"

void show_header_signup(void) 
{
    system("clear");

    printf(" .o88b.  .d8b.  d8888b.  .d8b.  .d8888. d888888b d8888b.  .d88b.  \n");
    printf("d8P  Y8 d8' `8b 88  `8D d8' `8b 88'  YP `~~88~~' 88  `8D .8P  Y8. \n");
    printf("8P      88ooo88 88   88 88ooo88 `8bo.      88    88oobY' 88    88 \n");
    printf("8b      88~~~88 88   88 88~~~88   `Y8b.    88    88`8b   88    88 \n");
    printf("Y8b  d8 88   88 88  .8D 88   88 db   8D    88    88 `88. `8b  d8' \n");
    printf(" `Y88P' YP   YP Y8888D' YP   YP `8888Y'    YP    88   YD  `Y88P'  \n\n");
}

int cpf_verification(char * cpf) 
{
    int icpf[12];

    int i, 
    	somador = 0, 
    	digito1, 
    	result1, 
    	result2, 
    	digito2, 
    	valor; 

    //Efetua a conversao de array de char para um array de int.  
    for (i = 0; i < 11; i++) 
    {  
        icpf[i] = cpf[i] - 48;  
    }  
 
    //PRIMEIRO DIGITO.  
    for (i = 0; i < 9; i++) {  
        somador += icpf[i] * (10 - i);  
    }  
 
    result1 = somador % 11;  
 
    if ((result1 == 0) || (result1 == 1)) {  
        digito1 = 0;  
    } 
    else 
    {  
        digito1 = 11 - result1;  
    }  
 
    //SEGUNDO DIGITO.  
    somador = 0;  
 
    for (i = 0; i < 10; i++) 
    {  
        somador += icpf[i] * (11 - i);  
    }  
 
    valor = (somador / 11) * 11;  
    result2 = somador - valor;  
 
    if ((result2 == 0) || (result2 == 1)) 
    {  
        digito2 = 0;  
    } 
    else 
    {  
        digito2 = 11 - result2;  
    }  
 
    //RESULTADOS DA VALIDACAO.  
    if ((digito1 == icpf[9]) && (digito2 == icpf[10])) 
    {  
        return 1;  
    } 
    else 
    {  
        return 0;  
  	} 
}

int novoUsuario(void)
{
    FILE *file;

    int totalUsuariosAtual = 0, 
    	novoTotalUsuarios = 0;

    file = fopen("../src/new-user/total.bin", "rb");

    if (file == NULL)
    {
        file = fopen("../src/new-user/total.bin", "w+b");

        novoTotalUsuarios = 1;
        
        fwrite(&novoTotalUsuarios, sizeof(int), 1, file);
	}
    else
    {
        fread(&totalUsuariosAtual, 1 , sizeof(int), file);
        
        novoTotalUsuarios = totalUsuariosAtual + 1;

        file = fopen("../src/new-user/total.bin", "w+b");
        
        fwrite(&novoTotalUsuarios, sizeof(int), 1, file);
    }

    fclose(file);

    return totalUsuariosAtual;
}

char *gerarCaminho(int numeroUsuario, char *arquivo)
{
	char caminho[] = "../data/usuario_";
	char totalUsuariosAtualString[20];

	snprintf(totalUsuariosAtualString, 20, "%d", numeroUsuario);
	
	strcat(caminho, totalUsuariosAtualString);

	mkdir(caminho, 0777);

	strcat(caminho, arquivo);
	
	char *buffer = malloc(sizeof(char) * strlen(caminho));

	for (int i = 0; i < strlen(caminho); ++i) 
	{
		buffer[i] = caminho[i];
	}
	
	return buffer;
}

void salvarUsuario(const char *path, char *conteudo)
{
    FILE *file;
    char conteudoCopy[strlen(conteudo)];
    char pathCopy[strlen(path)];

    strcpy(conteudoCopy, conteudo);
    strcpy(pathCopy, path);

    if ((file = fopen(pathCopy, "w+b")) == NULL)
    {
    	printf("Erro ao abrir o arquivo.\n");
    	exit(1);
    }
    
    fwrite(conteudoCopy, sizeof(conteudoCopy[0]), sizeof(conteudoCopy)/sizeof(conteudoCopy[0]), file);

    fclose(file);
}

int new_user(void) 
{
	int cpf_status = 0, 
		passwordSize = 0, 
		passsword_verification_status = 0,
		i, 
		newTotal;

	char password_verification[255],
		 totalUsersString[2], 
		 totalUsers[2];

	struct users 
	{
		char name[30];
		char cpf[12];
		char password[255];
	} user;

	show_header_signup();

	printf("Digite seu nome: ");
	fgets(user.name, 30, stdin);

	__fpurge(stdin);

	while (!cpf_status)
	{
		printf("Digite seu CPF: ");
		fgets(user.cpf, 12, stdin);

		__fpurge(stdin);

	 	if (cpf_verification(user.cpf))
		{
	 		cpf_status = 1; 	

	 		show_header_signup();		

	 		printf("Digite seu nome: %s", user.name);
	 		printf("Digite seu CPF: %s\n", user.cpf);
			printf("Digite a sua senha com 6 caracteres: ");

			fgets(user.password, 255, stdin);

			printf("%s", user.password);
		
			__fpurge(stdin);

			if (strlen(user.password) == 7)
			{
				while (!passwordSize)
				{
					show_header_signup();		

					printf("Digite seu nome: %s", user.name);
					printf("Digite seu CPF: %s\n", user.cpf);
					printf("Confirme sua senha: ");

					fgets(password_verification, 255, stdin);

					__fpurge(stdin);
					
					if (strlen(password_verification) == 7)
					{
						if (strcmp(user.password, password_verification) == 0)
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

			while (!passwordSize)
			{		
				show_header_signup();		

				printf("Digite seu nome: %s", user.name);
				printf("Digite seu CPF: %s\n", user.cpf);

				printf("Digite a sua senha com 6 caracteres: ");

				fgets(user.password, 255, stdin);

				__fpurge(stdin);

				if (strlen(user.password) == 7)
				{
					while (!passwordSize)
					{
						show_header_signup();		

						printf("Digite seu nome: %s", user.name);
						printf("Digite seu CPF: %s\n", user.cpf);
						printf("Confirme sua senha: ");

						fgets(password_verification, 255, stdin);

						__fpurge(stdin);
						
						if (strlen(password_verification) == 7)
						{
							if (strcmp(user.password, password_verification) == 0)
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
	 		printf("CPF invalido, digite novamente\n");
	 	}
	}

	system("clear");

 	int numeroUsuario = novoUsuario();
 	const char *buffer;

	char arquivo_cpf[] = "/cpf.bin";
    buffer = gerarCaminho(numeroUsuario, arquivo_cpf);
	salvarUsuario(buffer, user.cpf);
	free(buffer);

	char arquivo_nome[] = "/nome.bin";
   	buffer = gerarCaminho(numeroUsuario , arquivo_nome);
    salvarUsuario(buffer, user.name);
	free(buffer);

	char arquivo_senha[] = "/senha.bin";
    buffer = gerarCaminho(numeroUsuario , arquivo_senha); 
	salvarUsuario(buffer, user.password);
	free(buffer);
}

