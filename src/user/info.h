void show_header(void);
void acessar_informacoes_monetarias(void);
void acessar_informacoes_conta(void);
void informacoes_usuario(void);
void saldo_usuario(void);
void deposito_usuario(void);
void saque_usuario(void);
void abrir_arquivo(char modo[]);

struct estrutura
{
    char tipo[2];
    float valor;
    char data[11];
};

struct path_usuario 
{
	char file[14];
};

struct usuario
{
	char nome[30];
	char cpf[12];
	char senha[255];
};

typedef struct estrutura Transacao;