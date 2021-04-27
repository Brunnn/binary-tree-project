#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// typedef struct NodeElement NodeElement;
// typedef struct Node Node;
// typedef struct Tree Tree;

#include "./helpers/StringHelper.h"
#include "./NodeElement.h"
#include "./Tree.h"
#include "./helpers/FileManager.h"

void cls(){
    //system('cls');
}

void main()
{
    Tree *tree;
    int action;
    NodeElement input;
    Node *exist;
    FileManager* fm = NULL;
    tree = initialize();

    do{
        printf("\n\n---- ARVORE BINARIA -----");
        printf("\n----: 1 - Inserir");
        printf("\n----: 2 - Verifica se Existe");
        printf("\n----: 3 - Excluir");
        printf("\n----: 4 - Tamanho");
        printf("\n----: 5 - Em Ordem");
        printf("\n----: 6 - Pre-Ordem");
        printf("\n----: 7 - Pos-Ordem");
        printf("\n----: 0 - SAIR");
        printf("\n----: 10 - Ler Arquivo de Texto");
        printf("\n----: 11 - Inserir Valores do arquivo lido");
        printf("\n----: 12 - Printar Arvore");
        printf("\n----> Digite uma opcao: ");
        scanf("%d",&action);

        switch(action){
            case 1:
                cls();
                printf("\nDigite um nome proprio: ");
                NodeElement* node = readNewNode();
                insert(tree, node);
                break;
            case 2:
                printf("\n-- Digite o Elemento: ");
                scanf("%d", &input);
                exist = search(tree, &input);
                if(exist != NULL)
                    printf("\n-- Elemento Exite.");
                else
                    printf("\n-- Elemento nao existe.");
                break;
            case 3:
                //----
                break;
            case 4:
                printf("\n-- Tamanho da arvore eh: %d", size(tree));
                break;
            case 5:
                inOrder(tree);
                break;
            case 6:
                preOrder(tree);
                break;
            case 7:
                posOrder(tree);
                break;
            case 0: break;


            case 10:
                printf("Digite o PATH absoluto para o arquivo txt:\n");
                char *filePath;
                filePath = scanString(filePath);
                fm = readFileFromPath(filePath);
                printFileManagerLines(fm);
                break;
            case 11:
                if (fm == NULL || fileSuccess(fm) != 1){
                    printf("Nao existe nenhum arquivo carregado para insercao\n");
                }
                else{
                    int i;
                    char **words = fileRecords(fm);
                    for (i = 0; i < fileRecordLen(fm); i++)
                        insert(tree, NewNode(words[i]));
                }
                break;
            case 12:
                printf("DIREITA\n");
                printTree(tree->root, 0);
                printf("ESQUERDA\n");
            
                break;
            default :
                printf("\n-- Opcao invalida....");
        }

    }while(action != 0);
}