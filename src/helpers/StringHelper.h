
//Essa função só move o ponteiro da string, então se der um Free no ponteiro original o valor da substr retornado também é desalocado
char *strTrim(char *str){
    char *end;

    //Move o inicio do ponteiro para o primeiro caracter (que não é espaço da string)
    while(isspace((unsigned char)*str)) str++;

    //String é só espaços?
    if(*str == 0)  
        return str;


    //Move o caracter terminador para o ultimo não-espaço da string
    end = str + strlen(str) - 1;
    while(end > str && isspace((unsigned char)*end)) end--;
    end[1] = '\0';

    return str;
}

//Le uma string do Input (teclado)
char* scanString(char *string){
    int c;
    string = malloc(sizeof(char)); 

    string[0]='\0';

    fflush(stdin);
    for(int i=0; i<100 && (c=getchar())!='\n' && c != EOF ; i++)
    {
        string = realloc(string, (i+2)*sizeof(char)); 
        string[i] = (char) c; 
        string[i+1] = '\0'; 
    }

    return string;
}



//Cria uma copia de uma string, com seus espaços removidos (necessário dar free no retorno após uso)
char* removeWhiteSpaces(char *string){
    char *stringWithoutSpaces = (char*)malloc(sizeof(char)); 
    int len = 0;
    char *c;

    stringWithoutSpaces[len] = '\0';
    for (c = string; *c != '\0'; c++){
        if (!isspace(*c)){
            len++;
            stringWithoutSpaces = realloc(stringWithoutSpaces, (sizeof(char) * len) + 1);
            stringWithoutSpaces[len-1] = *c;
            stringWithoutSpaces[len] = '\0';
        }
    }
    return stringWithoutSpaces;
}

