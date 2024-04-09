#include "tree.h"

#include <stdio.h>

#include <stdlib.h>




//Добавление нового узла

Node* CreateNode(union data value, type type){

    Node *ptrNode = malloc(sizeof(Node));

    if (ptrNode != NULL) {

        ptrNode->left = NULL;

        ptrNode->right = NULL;

        ptrNode->value = value;

        ptrNode->type = type;

        return ptrNode;

    } else {

        exit(-1);

    }

}

Node* AddNode(union data value, type type) {

    Node *ptrNode = malloc(sizeof(Node));

    if (ptrNode != NULL) {

        ptrNode->left = NULL;

        ptrNode->right = NULL;

        ptrNode->value = value;

        ptrNode->type = type;

        return ptrNode;

    } else {

        exit(-1);

    }

}




//Вывод дерева

void PrintNode(Node *root, int indent) {

    if (root == NULL) {

        return;     

    }

    indent += 1;

    PrintNode(root->right, indent);     

    for (int i = 0; i < indent; ++i){

        printf("  ");

    }

    if (root->type == NUM) {

        printf("%d\n", root->value.num);  

    } else if (root->type == VAR) {

        printf("%s\n", root->value.symb);

    } else {

        printf("%c\n", *(root->value.symb));

    }

    PrintNode(root->left, indent); 




}




void PrintTree(Node* tree){

    PrintNode(tree, 0);

}




void TreeFree(Node* tree) {

    if (tree == NULL) {

        return;

    }

    TreeFree(tree->left);

    TreeFree(tree->right);

    //free(tree);

}