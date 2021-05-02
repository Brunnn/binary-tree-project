/*============================== BUSCA E PRINT de dados ná árvore AVL =============================== */

void inOrderR(Node *sroot){
    if(sroot->left != NULL)
        inOrderR(sroot->left);

    printf("%s, ",getName(sroot->element));

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