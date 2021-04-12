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
    size_t len = 0;
    ssize_t read;
    char * line = NULL;
    FileManager* fm = malloc(sizeof(FileManager));
    FILE* fp = fopen(path, "r");

    initFileManager(fm);

    if (fp == NULL)
        printf("Ocorreu um erro ao abrir o arquivo/caminho");
    else{
        fm->success = 1;
        fm->lines = (char**) malloc(sizeof(char*));

        while ((read = getline(&line, &len, fp)) != -1) {
            line = strTrim(line);
            size_t readStringLength = strlen(line);
            printf("line len: %i\n", readStringLength);
            if (readStringLength >= 1){
                fm->length++;
                fm->lines = (char**) realloc( fm->lines, fm->length * sizeof(char*));
                fm->lines[fm->length-1] = (char*) malloc((sizeof(char) * (int)readStringLength) + 1);
                strcpy(fm->lines[fm->length-1], line);
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