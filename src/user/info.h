void show_header(void);
void acessar_informacoes_monetarias(char * path);
void acessar_informacoes_conta(char * path);
void informacoes_usuario(char * path);
void saldo_usuario(char * path);
void deposito_usuario(char * path);
void saque_usuario(char * path);
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