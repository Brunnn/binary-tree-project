#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// typedef struct NodeElement NodeElement;
// typedef struct Node Node;
// typedef struct Tree Tree;


#include "./NodeElement.h"
#include "./Tree.h"
#include "./helpers/StringHelper.h"
#include "./helpers/FileManager.h"



void main()
{
    Tree *tree;
    int action;
    NodeElement input;
    Node *exist;

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
        printf("\n----: 8 - Inserir a partir de um arquivo");
        printf("\n----: 0 - SAIR");
        printf("\n----: 10 - Ler String");
        printf("\n----: 11 - Ler Arquivo de Texo");
        printf("\n----> Digite uma opcao: ");
        scanf("%d",&action);

        switch(action){
            case 1:
                printf("\n-- Digite um numero: ");
                scanf("%d",&input);
                NodeElement* node = readNewNode();
                insert(tree, *node);
                break;
            case 2:
                printf("\n-- Digite o Elemento: ");
                scanf("%d", &input);
                exist = search(tree, input);
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
                printf("Digite uma string qualquer\n");
                char *newString;
                newString = scanString(newString);
                printf("typed string: %s\n", newString);
                break;

            case 11:
                printf("Digite o PATH absoluto para o arquivo txt:\n");
                char *filePath;
                filePath = scanString(filePath);
                printf("typed string: %s\n", filePath);
                FileManager* fm = readFileFromPath(filePath);
                printFileManagerLines(fm);
                break;
            default :
                printf("\n-- Opcao invalida....");
        }

    }while(action != 0);
}