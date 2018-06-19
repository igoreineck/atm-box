int new_user(void);
void show_header_signup(void);
void save_user(const char* name);
int cpf_verification(char* cpf);

struct user
{
	char name[30];
	char cpf[12];
	char password[255];
};