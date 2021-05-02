


typedef struct Node {
    int balancingFactor;
    int height;
    int _id;
    struct NodeElement *element;
    struct Node *left, *right, *father;
} Node;



typedef struct Tree{       // referencia a raiz e ao tamanho
    Node *root;
    int size;
    int lastNodeId;
} Tree;


int max(int a, int b)
{
    return a > b ? a : b;
}

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


Node* newNode(Tree *tree, NodeElement *element)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    newNode->element = element;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->father = NULL;
    newNode->height = 0;
    newNode->balancingFactor = 0;
    newNode->_id = generateNodeId(tree);
    return newNode;
}

//Atualiza a altura e fb do nó 
void update(Node *node)
{
    int leftNodeHeight = (node->left == NULL) ? -1 : node->left->height;
    int rightNodeHeight = (node->right == NULL) ? -1 : node->right->height;

    // Atualiza a altura desse nó
    node->height = 1 + max(leftNodeHeight, rightNodeHeight);

    // Atualiza o fator de balanceamento
    node->balancingFactor = rightNodeHeight - leftNodeHeight;
}

//Realiza uma rotação para esquerda em um nó (deve ser chama pelas funções case)
//Precisa receber a árovre, pois em uma rotação, pode acontecer do root mudar.
Node *_leftRotation(Tree *tree, Node *node) {
    Node *parentOfNode = node->father;
    Node *newParent = node->right;

    node->right = newParent->left;
    if (node->right != NULL)
        node->right->father = node;
    
        
    newParent->left = node;
    node->father = newParent;

    //Novo root
    if (parentOfNode == NULL)
        tree->root = newParent;
    newParent->father = parentOfNode;
        
    update(node);
    update(newParent);
    return newParent;
}

//Realiza uma rotação para Direita em um nó (deve ser chama pelas funções case)
//Precisa receber a árovre, pois em uma rotação, pode acontecer do root mudar.
Node *_rightRotation(Tree *tree, Node *node) {
    Node *parentOfNode = node->father;
    Node *newParent = node->left;

    node->left = newParent->right;
    if (node->left != NULL)
        node->left->father = node;

    newParent->right = node;
    node->father = newParent;

    //Novo root
    if (parentOfNode == NULL)
        tree->root = newParent;
    newParent->father = parentOfNode;

    update(node);
    update(newParent);
    return newParent;
}

//Executa uma rotação Right
Node *leftLeftCase(Tree *tree, Node *node) {
    return _rightRotation(tree, node);
}

//Executa uma rotação Left e depois Right
Node *leftRightCase(Tree *tree, Node *node) {
    node->left = _leftRotation(tree, node->left);
    return leftLeftCase(tree, node);
}

//Executa uma rotação Left
Node *rightRightCase(Tree *tree, Node *node) {
    return _leftRotation(tree, node);
}

//Executa uma rotação Right e depois Left
Node *rightLeftCase(Tree *tree, Node *node) {
    node->right = _rightRotation(tree, node->right);
    return rightRightCase(tree, node);
}



// Método recursivo para procurar por valores repetidos na árvore
int contains(Node *node, NodeElement *value) {
    if (node == NULL) 
        return 0;

    NodeComparision cmp = compareNodes(value, node->element);

    // Procura no nó da esquerda
    if (cmp == Less) 
        return contains(node->left, value);

    // Procura no nó da direita
    if (cmp == Higher ) 
        return contains(node->right, value);

        // Valor já existe na árvore
    return 1;
}

//Realiza a rotação do nó (se necessário)
Node *balance(Tree *tree, Node *node)
{
    // Nó desbalanceado na esquerda
    if (node->balancingFactor == -2) {
        // Desbalanceado LeftLeft
        if (node->left->balancingFactor <= 0) 
            return leftLeftCase(tree, node);
        //Desbalanceado LeftRight
        else
            return leftRightCase(tree, node);

      
    } 
    else if (node->balancingFactor == 2) {
        // Desbalanceado RightRight
        if (node->right->balancingFactor >= 0) 
            return rightRightCase(tree, node);
        // Desbalanceado LeftRight
        else 
            return rightLeftCase(tree, node);
    }

    // Após o balanceamento (tendo o ocorrido ou não, o BF desse nó deve estar em -1, 0 ou +1)
    // então retorne-o para a chamada recursiva da função insert
    return node;
} 


/* Inserção de Valores na Arovre AVL */

//Helper da função de inserção (recursiva)
Node *insertRecursive(Tree *tree, Node *node, NodeElement *nodeValue)
{
    // Nó não existe (deve ser inserido aqui)
    if (node == NULL) 
        return newNode(tree, nodeValue);

    // Compare current value to the value in the node.
    NodeComparision cmp = compareNodes(nodeValue, node->element);

    
    if (cmp == Less){
        node->left = insertRecursive(tree, node->left, nodeValue);
        node->left->father = node;
    }
    else{
        node->right = insertRecursive(tree, node->right, nodeValue);
        node->right->father = node;
    }
    
    //Atualiza os faotres de balaceamento deste nó
    update(node);

    // Efetua rotações em nós desbalanceados (se necessário)
    return balance(tree, node);
}

// função inserir nó na arvore 
int insert(Tree *tree, NodeElement *element)
{
    //Valor vazio
    if (element == NULL) 
        return 0;

    //Verifica se o valor já não existe na árvore
    if (!contains(tree->root, element)) {
        tree->root = insertRecursive(tree, tree->root, element);
        tree->size++; // nro de nós
        return 1;
    }

    return 0;
}



// Encontra o menor valor nas subarvores da esquerda
Node *findMin(Node *node) {
    Node *aux = node;
    while (aux->left != NULL) 
        aux = aux->left;
    return aux;
}

// Encontra o maior valor nas subarvores da direita
Node *findMax(Node *node) {
    Node *aux = node;
    while (aux->right != NULL) 
        aux = aux->right;
    return aux;
}


// Função recursiva para procurar e remover um valor de uma árvore AVL
Node *removeRecursive(Tree *tree, Node *node, NodeElement *element) {
    if (node == NULL) 
        return NULL;

    NodeComparision cmp = compareNodes(element, node->element);

    // Procura na subarvore da esquerda, pois o valor que estamos procurando
    // é menor que o atual
    if (cmp == Less) {
        node->left = removeRecursive(tree, node->left, element);
    } 
    // Procura na subarvore da direita, pois o valor que estamos procurando
    // é maior que o atual
    else if (cmp == Higher) {
        node->right = removeRecursive(tree, node->right, element);
    } 
    //Nó Encontrado!!
    else {
        // Caso onde há somente uma subárvore na direita do que quer ser removido (ou nenhuma subarvore)
        // Apenas trocar o nó que queremos remover pelo seu filho direito
        if (node->left == NULL) {
            if (node->right != NULL){

                //Removendo nó ROOT
                if (node->father == NULL)
                    tree->root = node->right;

                node->right->father = node->father;
            }
            //Removendo nó root, e não existe nenhum outro nó abaixo
            else if (node->father == NULL)
                tree->root = NULL;

            Node *aux = node->right;
            free(node);
            return aux;
        } 
        // Caso onde há somente uma subarvore na esquerda (ou nenhuma subarvore)
        //  Apenas trocar o nó que queremos remover pelo seu filho esquerdo
        else if (node->right == NULL) {
            if (node->left != NULL){
                
                //Removendo nó ROOT
                if (node->father == NULL)
                    tree->root = node->left;
                node->left->father = node->father;
            }
            //Removendo nó root, e não existe nenhum outro nó abaixo
            else if (node->father == NULL)
                tree->root = NULL;
            

            Node *aux = node->left;
            free(node);
            return aux;     
        } 

        // Ao remover um nó que possui dois filhos (direita e esquerda)
        // Seu sucessor deve ser o menor valor encontrado
        // nas subárvores da esquerda, ou o maior nas da direita
        // Aqui eu escolho sempre da subarvore com maior altura
        // Pensando que isso vai ajudar no balanceamento da árvore
        else {

            if (node->left->height > node->right->height) {

                // Troca os valores do no que está sendo removido com seu sucessor
                Node *successorNode = findMax(node->left);

                node->element = successorNode->element;
                node->_id = successorNode->_id;

                //Como nós só alteramos o  valor do nó que queriamos remover com o maior da esquerda,
                // e não "excluimos" ele da árvore
                //Agora existem dois nós duplicados, e devemos efetivamente remover este "maior da esquerda"
                //Ao chamar a função de novo indo no nó da esquerda
                //Quando ela achar o nó duplicado, irá cair em um dos dois casos acima, onde o nó será efetivamente removido
                node->left = removeRecursive(tree, node->left, successorNode->element);

            } else {

                // Troca os valores do no que está sendo removido com seu sucessor
                Node *successorNode = findMin(node->right);

                node->element = successorNode->element;
                node->_id = successorNode->_id;

                //Como nós só alteramos o  valor do nó que queriamos remover com o menor da direita,
                // e não "excluimos" ele da árvore
                //Agora existem dois nós duplicados, e devemos efetivamente remover este "menor da direita"
                //Ao chamar a função de novo indo no nó da esquerda
                //Quando ela achar o nó duplicado, irá cair em um dos dois casos acima, onde o nó será efetivamente removido
                node->right = removeRecursive(tree, node->right, successorNode->element);
            }
        }
    }

    // Atualiza altura e FB do nó atual
    update(node);

    // Efetua rotações se necessário
    return balance(tree, node);
}

// Remove um valor na arvore binária AVL (se existir)
int removeNode(Tree *tree, NodeElement *element) {
    if (element == NULL) 
        return 0;

    if (contains(tree->root, element)) {
        tree->root = removeRecursive(tree, tree->root, element);
        tree->size--;
        return 1;
    }

    return 0;
}


//Inicializa uma arvore AVL
Tree* initialize(){
    Tree *newTree = (Tree*)malloc(sizeof(Tree));
    newTree->root = NULL;
    newTree->size = 0;
    newTree->lastNodeId = 0;
    return newTree;
}