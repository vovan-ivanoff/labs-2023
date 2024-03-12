#include <stdio.h>
#include <stdlib.h>

#define UZEL 0
#define BATYA 1
#define BBRO 2

typedef struct Node Node;

struct Node
{
    int id;
    Node *son;
    Node *bro;
    int value;
};

void FindNodeR(int id, Node* root, Node** res) { // рекурсивная функция поиска узла по id
    if ((root->son != NULL) && (root->son->id == id)) { // если сын не ноль, и id сына равно искомому, то заебись
        res[UZEL] = root->son;
        res[BATYA] = root;
    } else if ((root->bro != NULL) && (root->bro->id == id)) { // если брат не ноль, и id брата равно искомому, то заебись
        res[UZEL] = root->bro;
        res[BBRO] = root;
    } else { // иначе рекурсируем для сына и брата, если они есть
        if (root->son != NULL) FindNodeR(id, root->son, res);
        if (root->bro != NULL) FindNodeR(id, root->bro, res);
    }
}

void FindNode(int id, Node* root, Node** res) { // враппер, устаавливаем 
    //0 - сам узел, 1 - отец если есть, 2 - старший брат если есть
    res[UZEL] = NULL;
    res[BATYA] = NULL;
    res[BBRO] = NULL; //выставляем массив ответов в нули
    if (root->id == id) { // если id у корня совпадает, ставим в ответ корень
        res[UZEL] = root;
    } else { // иначе рекурсия
        FindNodeR(id, root, res);
    }
}

void AddNode(int dadId, int value, int *idCounter, Node** rootPtr) {
    Node *res[3]; // 0 - сам узел, 1 - отец если есть, 2 - старший брат если есть
    Node *root = *rootPtr;
    if (dadId == -1) {
        root = (Node*)malloc(sizeof(Node));
        root->bro = NULL;
        root->son = NULL;
        root->id = 0;
        root->value = value;
        *idCounter += 1;
        *rootPtr = root;
    } else {
        FindNode(dadId, root, res);
        if (res[UZEL] != NULL) {
            Node *dad = res[UZEL];
            Node *newNode = (Node*)malloc(sizeof(Node));
            newNode->value = value;
            newNode->id = *idCounter;
            *idCounter = *idCounter + 1;
            newNode->bro = NULL;
            newNode->son = NULL;
            if (dad != NULL) {
                if (dad->son == NULL) {
                    dad->son = newNode;
                } else {
                    Node *oldBro = dad->son;
                    while (oldBro->bro != NULL) {
                        oldBro = oldBro->bro;
                    }
                    oldBro->bro = newNode;
                }
            }
        }
    }
}

void DelNodeR(Node *node) { // удаляем сыновей потом братьев рекурсивно
    if (node->son != NULL) {
        DelNodeR(node->son);
    }
    if (node->bro != NULL) {
        DelNodeR(node->bro);
    }
    free(node);
}

void DelNode(int id, Node **rootPtr) { // враппер для DelNodeR
    Node *root = *rootPtr;
    Node *res[3]; // 0 - сам узел, 1 - отец если есть, 2 - старший брат если есть
    FindNode(id, root, res); // ищем нужный узел, ответ получаем в res
    if (res[BATYA] != NULL) {
        res[BATYA]->son = res[UZEL]->bro; // если батя не ушел за хлебом, то ебашим сына, а в качестве нового сына берем его брата
    } else if (res[BBRO] != NULL) { // если батя ушел за хлебом, а есть старший брат, то вырезаем брата, а новый - это младший брат вырезанного брата
        res[BBRO]->bro = res[UZEL]->bro;
    }
    if (res[UZEL]->son != NULL) { // вырезаем всю родню удаляемого узла
        DelNodeR(res[UZEL]->son);
    }
    free(res[UZEL]); // и освобождаем его от мучений
    if (id == 0) root = NULL;
    *rootPtr = root;
}

void ChangeValue(int id, int value, Node *root) {
    Node *res[3];
    FindNode(id, root, res); // ищем по id
    res[UZEL]->value = value; // меняем
}

void PrintTree(Node *root, int depth) {
    for(int i = 0; i < depth; i++) {
        if (i == depth - 1)printf(" |--");
        else printf(" |  ");
    }
    printf("%d:%d\n", root->id, root->value);
    if (root->son != NULL) {
        PrintTree(root->son, depth + 1);
    }
    if (root->bro != NULL) {
        PrintTree(root->bro, depth);
    }
}

void PrintTreeD(Node *root) { // враппер
    if (root != NULL){
    printf("------------\n");
    PrintTree(root, 0);
    printf("------------\n");
    } else {
        printf("empty\n");
    }
}

void Width(Node* root, int depth, int** res, int* depthMax) {
    if (depth >= *depthMax) {  // если глубина большое чем максимальная
        *res = realloc(*res, 2 * sizeof(int) * *depthMax); //переделываем массив
        for (int i = *depthMax; i < 2 * *depthMax; i++) { //зануляем его
            (*res)[i] = -1;
        }
        *depthMax = 2 * *depthMax; //умножаем
    }
    (*res)[depth] = (*res)[depth] + 1; // прибавляем к числу узлов на уровне
    if (root->bro != NULL) {
        Width(root->bro, depth, res, depthMax); //идем по братьям
    }
    if (root->son != NULL) {
        Width(root->son, depth + 1, res, depthMax); //идем по сыновьям
    }
}

void CheckWidthMonot(int* res, int depthMax) {
    int m = 0;
    int curWidth = 0;
    int prevWidth = 0;
    for (int i = 0; i < depthMax; i++) {
        curWidth = res[i] + 1;
        if (curWidth != 0 && curWidth < prevWidth) {
            printf("Not Monotonno on layer: %d\n", i + 1);
            return;
        }
        prevWidth = curWidth;
    }
    printf("Monotonno. Vse zbs!\n");
}
void PrintHelp(){
    printf("a [dad id] [value] - add node\n");
    printf("d [id] - delete node\n");
    printf("c [id] [new value] - change value\n");
    printf("f - check width monotonnost\n");
    printf("p - print tree\n");
    printf("h - show this help\n");
    printf("q - quit the program\n");
    printf("node output id:value\n");
}
int main() {
    int idCounter = 0;
    char command;
    int arg1, arg2;
    Node* root = NULL;
    PrintTreeD(root);
    do {
        scanf("%c", &command);
        switch (command)
        {
        case 'a':
            scanf("%d %d", &arg1, &arg2);
            AddNode(arg1, arg2, &idCounter, &root);
            PrintTreeD(root);
        break;
        case 'd':
            scanf("%d", &arg1);
            DelNode(arg1, &root);
            PrintTreeD(root);
        break;
        case 'c':
            scanf("%d %d", &arg1, &arg2);
            ChangeValue(arg1, arg2, root);
            PrintTreeD(root);
        break;
        case 'p':
            PrintTreeD(root);
        break;
        case 'f':
            int depthMax = 2; // предположим максимальную глубину 2
            int *res = (int*)malloc(sizeof(int) * depthMax); // выделяем массив на динамике
            for (int i = 0; i < depthMax; i++) { // зануляем его
                res[i] = -1;
            }
            Width(root, 0, &res, &depthMax);
            CheckWidthMonot(res, depthMax);
        break;
        case 'h':
            PrintHelp();
        }
    } while (command != 'q');
    return 0;
}