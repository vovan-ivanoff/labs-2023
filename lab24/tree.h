#ifndef __TREE__
#define __TREE__
#include <stdio.h>
#include "stack.h"
#include <stdlib.h>
typedef struct Node Node;

struct Node {
    type type;
    union data value;
    struct Node *left;
    struct Node *right;
};

Node* CreateNode(union data value, type type);
Node* AddNode(union data value, type type); 
void PrintNode(Node *root, int indent); 
void PrintTree(Node* tree);
void TreeFree(Node* tree);
#endif 