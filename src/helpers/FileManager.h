#define MAX_LINE_LENGTH 200
typedef struct FileManager{
    int success;
    int length;
    char **lines;
} FileManager;


void initFileManager(FileManager *fm){
    fm->lines = NULL;
    fm->success = 0;
    fm->length = 0;
}

FileManager* readFileFromPath(char *path){
    char* buffer = NULL;
    FileManager* fm = malloc(sizeof(FileManager));
    FILE* fp = fopen(path, "r");
    initFileManager(fm);

    if (fp == NULL)
        printf("Ocorreu um erro ao abrir ao abrir %s\n", path);
    else{
        fm->success = 1;

        size_t bufferFinalLength;
        char *buffer = (char*) malloc(sizeof(char) * MAX_LINE_LENGTH);
        while (fgets(buffer, MAX_LINE_LENGTH - 1, fp))
        {
            buffer[strcspn(buffer, "\n")] = 0;
            buffer = strTrim(buffer);
            bufferFinalLength = strlen(buffer);
            if (bufferFinalLength >= 1){
                void *tmp = realloc(fm->lines, (fm->length+1) * sizeof(*(fm->lines)));
                if (tmp == NULL)
                {
                    perror("Error ao expandir array de pointers");
                    for (int i=0; i<fm->length; ++i)
                        free(fm->lines[i]);
                    free(fm->lines);
                    fm->lines = NULL;
                    fm->success = 0;
                    fm->length = 0;
                    break;
                }
                fm->lines = tmp;
                fm->lines[fm->length] = (char*) malloc((sizeof(char) * bufferFinalLength) + 1);
                strcpy(fm->lines[fm->length], buffer);
                fm->length++;
            }

        }
    }

    fclose(fp);
    return fm;
}


void printFileManagerLines(FileManager *fm){
    printf("\nFileManager Lines: %i\n", fm->length);
    if (fm->success == 1){
        int i;
        for (i=0; i < fm->length; i++)
            printf("(%i) | %s\n", strlen(fm->lines[i]), fm->lines[i]);
    }
    else{
        printf("Essa instancia de FileManager nao obteve sucesso ao ler o arquivo");
    }
}


int fileSuccess(FileManager *fm)
{
    return fm->success;
}

//Retorna a quantidade de palavras lidas
size_t fileRecordLen(FileManager *fm)
{
    return fm->length;
}

//Retorna uma cópia das palavras lidas no arquivo de texto
char **fileRecords(FileManager *fm){
    int i;
    size_t recordCount = fileRecordLen(fm);
    char **copiedWords = NULL;
    size_t wordLen;
    if (recordCount >= 1) {
        copiedWords = (char**) malloc(sizeof(char*) * recordCount); 
        for (i = 0; i < recordCount; i++){
            wordLen = strlen(fm->lines[i]);
            copiedWords[i] = (char*) malloc((sizeof(char) * wordLen) + 1);
            strcpy(copiedWords[i], fm->lines[i]);
        }
    }
    return copiedWords;
}