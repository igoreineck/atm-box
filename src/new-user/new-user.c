/* 
Métodos:

Opcao 1 - Digitar CPF

Opcao 2 - Digitar Nome

Opcao 3 (Implícita) - Geração automática de senha (6 dígitos) 

* Após criação, retornar os dados do usuário (somente: nome e cpf)

*/

void new_user(void)
{
	char name[20];
	long int CPF;
	char password[255];

	printf("Digite seu nome: ");
	fgets(name, 20, stdin);

	__fpurge(stdin);

	printf("Digite seu CPF: ");
	scanf("%ld \n", CPF);

	password = password_generate();

	printf("Sua conta foi criada com sucesso!");
}
