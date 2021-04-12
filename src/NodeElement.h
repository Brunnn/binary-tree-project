

typedef struct NodeElement{
    char *name;
    int length;
} NodeElement;


char *getName(NodeElement node){
    return node.name;
}

int getNodeLength(NodeElement node){
    return node.length;
}

NodeElement* readNewNode(){
    NodeElement* newNode = malloc(sizeof(NodeElement));
    newNode->length = 0;

    return newNode;
}

