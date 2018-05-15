/* 
Métodos

Opcao 1 - Saldo
    Exibir valor em caixa (variável saldo)

Opcao 2 - Deposito (valor)
    Inserir valor no saldo
    Retornar novo saldo

Opcao 3 - Saque (valor)
    Remover valor a partir do saldo
    Retornar novo saldo

Opcao 4 - Informacoes da conta
    Exibir CPF
    Exibir nome

Opcao 5 - Redefinir senha
    Senha encriptada

*/


#include <stdio.h>
#include <stdlib.h>
#include "info.h"

// definir função no .h
float* saldo_usuario(void)
{
	float saldo;

	FILE *file;

	file = fopen("../../data/usuario-1/saldo.txt", "r");

	fscanf(file, "%f\n", &saldo);

	printf("%4f", saldo);

	fclose(file);


	// return saldo;
}

void acessar_informacoes_monetarias(void) 
{
    int opcao = 0;

    printf("Digite uma op��o abaixo: \n");
    printf("1 - Saldo \n");
    printf("2 - Dep�sito \n");
    printf("3 - Saque \n");
    scanf("%d", &opcao);

    __fpurge(stdin);

    if (opcao == 1) 
    {
    	saldo_usuario();
    }
}

void acessar_informacoes_conta(void) 
{

}

void informacoes_usuario(void) 
{
	int opcao = 0;

	printf("Digite uma das opções abaixo: \n");
	printf("1 - Informações da Conta \n");
	printf("2 - Informações monetárias da Conta \n");
	// printf("3 - Editar conta") -> Adicionar posteriormente
	scanf("%d", &opcao);

	__fpurge(stdin);

	if (opcao == 1) 
	{
		acessar_informacoes_conta();
	} 
	else if (opcao == 2)
	{
		acessar_informacoes_monetarias();
	}
}

