void new_user(void);
char password_generate(char *);
void save_user(void);
int cpf_verification( char cpf[12]);

int cpf_verification( char cpf[12]) {

    int icpf[12];  
    int i,somador=0,digito1,result1,result2,digito2,valor; 

    //Efetua a conversao de array de char para um array de int.  
    for(i=0;i<11;i++)  
    {  
    icpf[i]=cpf[i]-48;  
    }  
    
    //PRIMEIRO DIGITO.  
    
    for(i=0;i<9;i++)  
    {  
    somador+=icpf[i]*(10-i);  
    }  
    
    result1=somador%11;  
    
    if( (result1==0) || (result1==1) )  
    {  
    digito1=0;  
    }  
    
    else  
    {  
    digito1 = 11-result1;  
    }  
    
    //SEGUNDO DIGITO.  
    
    somador=0;  
    
    for(i=0;i<10;i++)  
    {  
    somador+=icpf[i]*(11-i);  
    }  
    
    valor=(somador/11)*11;  
    result2=somador-valor;  
    
    if( (result2==0) || (result2==1) )  
    {  
    digito2=0;  
    }  
    
    else  
    {  
    digito2=11-result2;  
    }  
    
    //RESULTADOS DA VALIDACAO.  
    
    if((digito1==icpf[9]) && (digito2==icpf[10]))  
    {  
    return 1;  
    }  
    else  
    {  
    return 0;  
    } 
}

void show_header(){
    printf(" .o88b.  .d8b.  d8888b.  .d8b.  .d8888. d888888b d8888b.  .d88b.  \n");
    printf("d8P  Y8 d8' `8b 88  `8D d8' `8b 88'  YP `~~88~~' 88  `8D .8P  Y8. \n");
    printf("8P      88ooo88 88   88 88ooo88 `8bo.      88    88oobY' 88    88 \n");
    printf("8b      88~~~88 88   88 88~~~88   `Y8b.    88    88`8b   88    88 \n");
    printf("Y8b  d8 88   88 88  .8D 88   88 db   8D    88    88 `88. `8b  d8' \n");
    printf(" `Y88P' YP   YP Y8888D' YP   YP `8888Y'    YP    88   YD  `Y88P'  \n\n");
}