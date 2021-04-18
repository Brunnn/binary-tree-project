

//Less | Equal | Higher
typedef enum NodeComparision { Less = 1, Equal, Higher } NodeComparision;


typedef struct NodeElement{
    char *name;
    int length;
} NodeElement;


NodeElement* NewNode(char *string){
    NodeElement* newNode = malloc(sizeof(NodeElement));
    newNode->length = strlen(string);
    newNode->name = string;
    return newNode;
}

NodeElement* readNewNode(){
    char *s = scanString(s);
    s = strTrim(s);
    return NewNode(s);
}




char *getName(NodeElement *node){
    return node->name;
}

//bruno santos
char *getNamePrintable(NodeElement *node){
    char *nodeName = getName(node);
    int nameLen = strlen(nodeName);
    char *formattedName = NULL;
 
    //Nome muito grande para ser printado, formatar
    formattedName = (char *) malloc(sizeof(char) * 20);

    if (nameLen  >= 18){
        strncpy(formattedName, nodeName, 16);
        formattedName[16] = formattedName[17] = formattedName[18] = '.';
        formattedName[19] = '\0';
    }
    else{
        int i;
        strcpy(formattedName, nodeName);
        formattedName[nameLen] = ' ';
        for (i=nameLen+1; i < 19; i++)
            formattedName[i] = ' ';
        formattedName[19] = '\0';
    }
    return formattedName;

}

int getNodeLength(NodeElement *node){
    return node->length;
}


NodeComparision compareNodes(NodeElement *heldNode, NodeElement *targetNode){
    char *s1 = removeWhiteSpaces(getName(heldNode));
    char *s2 = removeWhiteSpaces(getName(targetNode));
    int comparision = strcmp(s1, s2);
    free(s1);
    free(s2);
    NodeComparision cmpResult;
    if (comparision < 0)
        cmpResult = Less;
    else if (comparision == 0)
        cmpResult = Equal;
    else
        cmpResult = Higher;

    return cmpResult; 
}




