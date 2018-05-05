/* 
Métodos:

Opcao 1 - Digitar CPF

Opcao 2 - Digitar Nome

Opcao 3 (Implícita) - Geração automática de senha (6 dígitos) 

* Após criação, retornar os dados do usuário (somente: nome e cpf)

*/
void save_user(void)
{
    // FILE *file;

    // file = fopen("contas/igor/deposito.txt");

    // if (file != NULL)
}

char password_generate(char *) {}

void new_user(void)
{
	struct user
	{
		char name[20];
		long int CPF;
		char password[255];
		char *encrypted_password;
	};

	printf("Digite seu nome: ");
	fgets(user.name, 20, stdin);

	__fpurge(stdin);

	printf("Digite seu CPF: ");
	scanf("%ld \n", user.CPF);

	printf("Digite a sua senha com no máximo 6 caracteres: ");
	fgets(user.password, 255, stdin);

	__fpurge(stdin);

	user.encrypted_password = &user.password;
	password_generate(encrypted_password);

	save_user(user);

	printf("Sua conta foi criada com sucesso!");
}
