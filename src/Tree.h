
typedef enum RotationDirection { LeftLeft = 1, LeftRight, RightRight, RightLeft, NoRotation} RotationDirection;


typedef struct Node {
    int balancingFactor;
    int _id;
    struct NodeElement *element;
    struct Node *left, *right, *father;
} Node;



typedef struct Tree{       // referencia a raiz e ao tamanho
    Node *root;
    int size;
    int lastNodeId;
} Tree;


int size(Tree *tree)
{
    return tree->size;
}

int getNodeId(Node *n)
{
    return n->_id;
}

int generateNodeId(Tree *tree){
    return ++tree->lastNodeId;
}

// operação de busca - encontrar o pai do elemento onde quero incluir/procurar
Node* searchParent(Tree *tree, NodeElement *element, int forInsert, int *Found){
    Node *p = tree->root;
    Node *parent = NULL;


    while (p != NULL && (forInsert || compareNodes(p->element, element) != Equal)) // rep até achar o elemento
    {
        NodeComparision cmp = compareNodes(element, p->element);
        parent = p; // guardo o pai antes de descer
        if(cmp == Less)
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
Node* search(Tree *tree, NodeElement *element){
    int found;
    Node *parent = searchParent(tree, element, 0, &found);
    Node *p = NULL;

    if(found){
        if(parent == NULL)
            p = tree->root;
        else {
            NodeComparision cmp = compareNodes(element, parent->left->element);
            if (cmp == Less || cmp == Equal)
                p = parent->left;
            else
                p = parent->right;
        }
    }
    return p;
}



RotationDirection isNodeBalanced(Node* node)
{
    RotationDirection r = NoRotation; 
    if(node != NULL){
        if (node->balancingFactor > 1){
            if (node->right->right != NULL)
                r = LeftLeft;
            else 
                r = LeftRight;
        }
        else if (node->balancingFactor < -1){
            if (node->left->left != NULL)
                r = RightRight;
            else
                r = RightLeft;
        }
    }
    return r;
}

/* Ajusta os fatores de balanceamento depois de uma inserção */
Node* updateNode(Node *node)
{

    Node *nodeToRotate = NULL;
    Node *insertedNodeParent = node->father;
    //Não há necessidade de rotação (nó inserido como root)
    if (insertedNodeParent == NULL)
        return nodeToRotate;

    //Indica se há um nó no lado oposto do no inserido 
    int hasOppositeSideNode;

    //Nó inserido na direita
    if (insertedNodeParent->right == node)
    {
        insertedNodeParent->balancingFactor++;
        hasOppositeSideNode = insertedNodeParent->left != NULL ?  1 : 0;
    }
    //Nó inserido na esquerda
    else
    {
        insertedNodeParent->balancingFactor--;
        hasOppositeSideNode = insertedNodeParent->right != NULL ?  1 : 0;
    }

    //Se não tem nó existente no lado oposto, que dizer que o fator de balanceamento dos nós acima irão ser alterados
    if (!hasOppositeSideNode)
    {
        Node *aux = insertedNodeParent->father;
        Node *previousNode = insertedNodeParent;
        while (aux != NULL)
        {
            if (aux->left == previousNode)
                aux->balancingFactor--;
            else
                aux->balancingFactor++;
            
            if (nodeToRotate == NULL && isNodeBalanced(aux) != NoRotation)
                nodeToRotate = aux;
            previousNode = aux;
            aux = aux->father;
        }
    }
    return nodeToRotate;
}



/* Rotações */

/* Returns treeRootNode | null */
Node *LeftLeftRotate(Node *node)
{
    printf("Rotacionando node %i\n", node->_id);
    Node *rootNode = NULL;
    Node *father = node->father;
    Node *rightNode = node->right;

    //Verifica se o no rotacionado tem pai
    if (father == NULL){
        rootNode = rightNode;
        rightNode->father = NULL;
    }
    else{
        //Se o nó rotacionado tem pai, este precisa agora referenciar o nó da direita do rotacionado
        if (father->left == node)
            father->left = rightNode;
        else
            father->right = rightNode;

        rightNode->father = father;
    }

    //Aloca o nó da direita como pai do no rotacionado
    rightNode->left = node;
    node->father = rightNode;
    node->right = NULL;
    
    node->balancingFactor = 0;
    rightNode->balancingFactor = 0;


    //Ajusta os fatores de balaceamento dos ancestrais
    Node *aux = father;

    while(aux != NULL)
    {
        if (aux->right == rightNode)
            aux->balancingFactor--;
        else
            aux->balancingFactor++;
        
        aux = aux->father;
    }


    //Retorna um novo root node se houver
    return rootNode;
}

/* Returns treeRootNode | null */
Node *RightRightRotate(Node *node)
{
    Node *rootNode = NULL;
    Node *father = node->father;
    Node *leftNode = node->left;
    Node *leftNodeOfLeftNode = leftNode->left;

    //Verifica se o no rotacionado tem pai
    if (father == NULL){
        rootNode = leftNode;
        leftNode->father = NULL;
    }
    else{

        //Se o nó rotacionado tem pai, este precisa agora referenciar o nó da direita do rotacionado
        if (father->left == node)
            father->left = leftNode;
        else
            father->right = leftNode;
        leftNode->father = father;
    }

    //Aloca o nó da esquerda como pai do no rotacionado
    leftNode->right = node;
    node->father = leftNode;
    node->left = NULL;

    
    node->balancingFactor = 0;
    leftNode->balancingFactor = 0;


    //Ajusta os fatores de balaceamento dos ancestrais
    Node *aux = father;

    while(aux != NULL)
    {
        if (aux->right == leftNode)
            aux->balancingFactor--;
        else
            aux->balancingFactor++;
        
        aux = aux->father;
    }
    //Retorna um novo root node se houver
    return rootNode;
}

//rotaciona um nó desbalanceado
void RotateNode(Tree *tree, Node *node)
{
    Node *newRootNode = NULL;
    RotationDirection nodeBalanceDirection = isNodeBalanced(node);
    switch(nodeBalanceDirection)
    {
        case LeftLeft:
            newRootNode = LeftLeftRotate(node);
            break;
        case RightRight:
            newRootNode = RightRightRotate(node);
            break;
        case RightLeft:
            //RightRightRotate(node->right);
            //newRootNode = RightRightRotate(node);
            break;
        case LeftRight:
            //LeftLeftRotate(node->left);
            //newRootNode = LeftLeftRotate(node);
            break;
    }

    if (newRootNode != NULL)
        tree->root = newRootNode;
    return;
}

// --- função inserir nó na arvore ----
Node* insert(Tree *tree, NodeElement *element)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->element = element;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->father = NULL;
    newNode->balancingFactor = 0;
    newNode->_id = generateNodeId(tree);

    if(tree->root == NULL)
        tree->root = newNode;
    else{
        int found;
        Node *parent = searchParent(tree, element, 1, &found);
        NodeComparision cmp = compareNodes(element, parent->element);
        if(cmp == Less || cmp == Equal)
            parent->left = newNode;  // adiciona na esquerda
        else
            parent->right = newNode;  // adiciona na direita

        newNode->father = parent;
    }
    Node *nodeToRotate = updateNode(newNode);

    if (nodeToRotate != NULL){
        printf("No desbalanceado encontrado: %i\n",getNodeId(nodeToRotate));
        RotateNode(tree, nodeToRotate);
    }
    
    tree->size++; // nro de nós
    return newNode;
}




Tree* initialize(){
    Tree *newTree = (Tree*)malloc(sizeof(Tree));
    newTree->root = NULL;
    newTree->size = 0;
    newTree->lastNodeId = 0;
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
    printf("%s, ",getName(sroot->element));

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

    printf("%s, ",getName(sroot->element));
}

void posOrder(Tree *tree)
{
    if(tree->root != NULL)
        posOrderR(tree->root);
}




void _addPadding(char s, int times, int pad){
    int i,k;
    for ( i = 0; i < pad; i++ ){
        for (k=0; k < times; k++)
            putchar(s);
    }
}
void printTree(Node *root, int level){
    int i;

    if (root == NULL) {
        _addPadding( '\t', 3,level );
        puts("~");
    }
    else {
        printTree( root->right, level + 1 );
        _addPadding('\t', 3,level );
        printf ("(%i)(%i)(%s)\n", getNodeId(root), root->balancingFactor,getNamePrintable((root->element)));
        printTree ( root->left, level + 1 );
    }
}