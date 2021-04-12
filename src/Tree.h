


typedef struct Node {
    struct NodeElement element;
    struct Node *left, *right, *father;
} Node;



typedef struct Tree{       // referencia a raiz e ao tamanho
    Node *root;
    int size;
} Tree;



// operação de busca - encontrar o pai do elemento onde quero incluir/procurar
Node* searchParent(Tree *tree, NodeElement element, int forInsert, int *Found){
    Node *p = tree->root;
    Node *parent = NULL;


    while (p != NULL && (forInsert || strcmp(getName(p->element), getName(element)) != 0)) // rep até achar o elemento
    {
        parent = p; // guardo o pai antes de descer
        if(strcmp(getName(element), getName(p->element)) < 0)
            p = p->left;
        else
            p = p->right;
    }
    if(p == NULL)
        *Found = 0;
    else
        *Found = 1;
    return parent;
}
// operação de busca de um elemento na árvore.
Node* search(Tree *tree, NodeElement element){
    int found;
    Node *parent = searchParent(tree, element, 0, &found);
    Node *p = NULL;

    if(found){
        if(parent == NULL)
            p = tree->root;
        else if(strcmp(getName(element), getName(parent->left->element)) == 0)
            p = parent->left;
        else
            p = parent->right;
    }
    return p;
}
// --- função inserir nó na arvore ----
Node* insert(Tree *tree, NodeElement element)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->element = element;
    newNode->left = NULL;
    newNode->right = NULL;

    if(tree->root == NULL)
        tree->root = newNode;
    else{
        int found;
        Node *parent = searchParent(tree, element, 1, &found);
        if(strcmp(getName(element), getName(parent->element)) == 0)
            parent->left = newNode;  // adiciona na esquerda
        else
            parent->right = newNode;  // adiciona na direita
    }

    tree->size++; // nro de nós e não nro de niveis...???
    return newNode;
}




Tree* initialize(){
    Tree *newTree = (Tree*)malloc(sizeof(Tree));
    newTree->root = NULL;
    newTree->size = 0;
    return newTree;
}



// - BUSCAR: Em Ordem, Pré-Ordem e Pós-Ordem

void inOrderR(Node *sroot){
    if(sroot->left != NULL)
        inOrderR(sroot->left);

    printf("%d, ",sroot->element);

    if(sroot->right != NULL)
        inOrderR(sroot->right);
}

void inOrder(Tree *tree)
{
    if(tree->root != NULL)
        inOrderR(tree->root);
}

//---------------------------------------------
void preOrderR(Node *sroot) // recursivo
{
    printf("%d, ",sroot->element);

    if(sroot->left != NULL)
        preOrderR(sroot->left);

    if(sroot->right != NULL)
        preOrderR(sroot->right);
}

void preOrder(Tree *tree)
{
    if(tree->root != NULL)
        preOrderR(tree->root);
}

//---------------------------------------------
void posOrderR(Node *sroot) // recursivo
{
    if(sroot->left != NULL)
        posOrderR(sroot->left);

    if(sroot->right != NULL)
        posOrderR(sroot->right);

    printf("%d, ",sroot->element);
}

void posOrder(Tree *tree)
{
    if(tree->root != NULL)
        posOrderR(tree->root);
}

int size(Tree *tree)
{
    return tree->size;
}