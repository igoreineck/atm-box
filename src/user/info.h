void show_header(void);
void acessar_informacoes_monetarias(const char * path);
void acessar_informacoes_conta(const char * path);
void informacoes_usuario(const char * path);
void saldo_usuario(const char * path);
void deposito_usuario(const char * path);
void saque_usuario(const char * path);
void abrir_arquivo(char modo[]);
char *exibir_data(void);

struct estrutura
{
    char tipo[15];
    float valor;
    char data[30];
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