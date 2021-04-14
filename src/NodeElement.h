

//Less | Equal | Higher
typedef enum NodeComparision { Less = 1, Equal, Higher } NodeComparision;

//dsahudshuaudhsa
typedef struct NodeElement{
    char *name;
    int length;
} NodeElement;


char *getName(NodeElement *node){
    return node->name;

}

int getNodeLength(NodeElement *node){
    return node->length;
}

NodeElement* readNewNode(){
    NodeElement* newNode = malloc(sizeof(NodeElement));
    newNode->length = 0;

    return newNode;
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




