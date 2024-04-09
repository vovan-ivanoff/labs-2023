#include <stdlib.h>
#include "tree.h"
#include "stack.h"
char oper = 42; // заебёт
int IsOperation(char c) {
    return (c == '+') || (c == '-') || (c == '*') || (c == '/') || (c == '^') ;
}

void StackToTree(Stack* stk, Node* curNode) {
    while (stk->top != NULL && (curNode->left == NULL || curNode->right == NULL)) {
        if (curNode->right == NULL) {
            if (stk->top->type == SYMB) {
                curNode->right = AddNode(StackPop(stk), stk->top->type);
                StackToTree(stk, curNode->right);
            } else {
                curNode->right = AddNode(StackPop(stk), stk->top->type);
            }
        } else {
            if (stk->top->type == SYMB) {
                curNode->left = AddNode(StackPop(stk), stk->top->type);
                StackToTree(stk, curNode->left);
            } else {
                curNode->left = AddNode(StackPop(stk), stk->top->type);
            }
        }
    }
}

void ReplaceMultSum(Node** initialTree) {
    /* общий алгоритм:
    1. проверяем, если данный узел оператор умножения
    2. да - проверяем с одной стороны переменную, с другой плюс,
    запускаем рекурси по плюсам, составляя новый кусок дерева, который вставим вместо ноды с умножением
    3. нет- если у узла в потомках оператор, идем рекурсивно на него, иначе завершаем
    =======
    итого нужно проверить * и +
    */
   union data data;
   data.symb=&oper;
   Node* tree = *initialTree;
   if (tree->type == SYMB && *(tree->value.symb) == '*'){ //первый пункт
    if (tree->left->type == VAR && tree->right->type == SYMB && *(tree->right->value.symb) == '+') { // если слева переменная, а справа символ и он плюс
        bool flag = false;
        Node* variable = tree->left;
        Node* ptr = tree->right; // указатель, который мы можем портить для цикла
        //*(tree->value.symb) = '+';
        Node* ptrBack = tree->right;
        while((ptr->left->type == SYMB && *(ptr->left->value.symb) == '+') || 
              (ptr->right->type == SYMB && *(ptr->right->value.symb) == '+')){
                flag = true;
                Node* tmp = CreateNode(data, SYMB);
                tmp->type = SYMB;
                tmp->left = variable; // сохр изнач переменную
                if(ptr->left->type == SYMB){
                    tmp->right = ptr->right;
                    ptr->right = tmp;
                    ptr = ptr->left;
                } 
                else if(ptr->right->type == SYMB) {
                    tmp->right = ptr->left;
                    ptr->left = tmp;
                    ptr = ptr->right;
                }
              } // пока есть операторы и они плюсы
            if(flag){
                Node* tmp1 = CreateNode(data, SYMB);
                tmp1->type = SYMB;
                tmp1->left = tree->left;
                tmp1->right = ptr->left;
                Node* tmp2 = CreateNode(data, SYMB);
                tmp2->type = SYMB;
                tmp2->left = tree->left;
                tmp2->right = ptr->right;
                ptr->left = tmp1;
                ptr->right = tmp2;
            } //если прошли до момента где + и 2 цифры
        *initialTree = tree->right;
    } else if (tree->right->type == VAR && tree->left->type == SYMB && *(tree->left->value.symb) == '+') { // если справа переменная, а справа символ и он плюс
        bool flag = false;
        Node* variable = tree->right;
        Node* ptr = tree->left; // указатель, который мы можем портить для цикла
        //*(tree->value.symb) = '+';
        Node* ptrBack = tree->right;
        while((ptr->left->type == SYMB && *(ptr->left->value.symb) == '+') || 
              (ptr->right->type == SYMB && *(ptr->right->value.symb) == '+')){
                flag = true;
                Node* tmp = CreateNode(data, SYMB);
                tmp->type = SYMB;
                tmp->left = variable; // сохр изнач переменную
                if(ptr->left->type == SYMB){
                    tmp->right = ptr->right;
                    ptr->right = tmp;
                    ptr = ptr->left;
                } 
                else if(ptr->right->type == SYMB) {
                    tmp->right = ptr->left;
                    ptr->left = tmp;
                    ptr = ptr->right;
                }
              } // пока есть операторы и они плюсы
            if(flag){
                Node* tmp1 = CreateNode(data, SYMB);
                tmp1->type = SYMB;
                tmp1->left = tree->left;
                tmp1->right = ptr->left;
                Node* tmp2 = CreateNode(data, SYMB);
                tmp2->type = SYMB;
                tmp2->left = tree->left;
                tmp2->right = ptr->right;
                ptr->left = tmp1;
                ptr->right = tmp2;
            } //если прошли до момента где + и 2 цифры
        *initialTree = tree->left;
    } //иначе хорош
   } else { // последний пункт
    if (tree->right != NULL && tree->right->type == SYMB){ //если слева сын символ
        ReplaceMultSum(&(tree->right)); //вызываем для него
    }
    if (tree->left != NULL && tree->left->type == SYMB){ //если справа сын символ
        ReplaceMultSum(&(tree->left)); //вызываем для него
    }
   }

}

void PrintResult(Node* tree) {
    if (tree->left == NULL && tree->right == NULL) {
        if (tree->type == SYMB) {
            printf("%c", *tree->value.symb);
        } else if (tree->type == VAR) {
            printf("%s", tree->value.symb);
        } else {
            printf("%d", tree->value.num);
        }
        return;
    } 
    if (tree->left != NULL) {
        printf("(");
        PrintResult(tree->left);
    }
    if (tree->type == SYMB) {
        printf("%c", *tree->value.symb);
    } else if (tree->type == VAR) {
        printf("%s", tree->value.symb);
    } else {
        printf("%d", tree->value.num);
    }
    if (tree->right != NULL) {
        PrintResult(tree->right);       
        printf(")");
    }
}

void ReadFormula() {
    Stack operations = StackInit();
    Stack values = StackInit();
    char symbol = ' ';
    int prevSymbol = 1;
    int ind = 0;
    while (symbol != EOF && symbol != '\n') {   
        if (symbol != ' ') {
            if (IsOperation(symbol) && prevSymbol != 1) {
                prevSymbol = 1;
                switch (symbol)
                {
                case '+':
                    if (StackIsEmpty(&operations) != true) {
                        while (*operations.top->value.symb != '(') {
                            StackPush(&values, *operations.top->value.symb, operations.top->type);
                            StackPop(&operations);
                            if (operations.top == NULL) {
                                break;
                            }
                        }
                        StackPush(&operations, '+', SYMB);
                    } else {
                        StackPush(&operations, '+', SYMB);
                    }
                    break;
                case '-':
                    if (StackIsEmpty(&operations) != true) {
                        while (*operations.top->value.symb != '(') {
                            StackPush(&values, *operations.top->value.symb, operations.top->type);
                            StackPop(&operations);
                            if (operations.top == NULL) {
                                break;
                            }
                        }
                        StackPush(&operations, '-', SYMB);

                    } else {
                        StackPush(&operations, '-', SYMB);
                    }
                    break;
                case '*':
                    if (StackIsEmpty(&operations) != true) {
                        while (*operations.top->value.symb == '*' || *operations.top->value.symb == '/' || *operations.top->value.symb == '^') {
                            StackPush(&values, *operations.top->value.symb, operations.top->type);
                            StackPop(&operations);
                            if (operations.top == NULL) {
                                break;
                            }
                        }
                        StackPush(&operations, '*', SYMB);

                    } else {
                        StackPush(&operations, '*', SYMB);
                    }
                    break;
                case '/':
                    if (StackIsEmpty(&operations) != true) {
                        while (*operations.top->value.symb == '*' || *operations.top->value.symb == '/' || *operations.top->value.symb == '^') {
                            StackPush(&values, *operations.top->value.symb, operations.top->type);
                            StackPop(&operations);
                            if (operations.top == NULL) {
                                break;
                            }
                        }
                        StackPush(&operations, '/', SYMB);
                    } else {
                        StackPush(&operations, '/', SYMB);
                    }
                    break;
                case '^':
                    if (StackIsEmpty(&operations) != true) {
                        while (*operations.top->value.symb == '^') {
                            StackPush(&values, *operations.top->value.symb, operations.top->type);
                            StackPop(&operations);
                            if (operations.top == NULL) {
                                break;
                            }
                        }
                        StackPush(&operations, '^', SYMB);
                    } else {
                        StackPush(&operations, '^', SYMB);
                    }
                    break;

                default:
                    break;
                }
            } else if (symbol == '(') {
                StackPush(&operations, symbol, SYMB);
            } else if (symbol == ')') {
                while (*operations.top->value.symb != '(')
                {
                    StackPush(&values, *operations.top->value.symb, operations.top->type);
                    StackPop(&operations);
                }
                StackPop(&operations);
            } else {// если число
               if (prevSymbol == 0 && symbol <= '9' && symbol >= '1') {
                    if (symbol != '0') {
                        values.top->value.num = values.top->value.num * 10 + (symbol - '0');
                        prevSymbol = 0;
                    } else {
                        values.top->value.num = values.top->value.num * 10;
                        prevSymbol = 0;
                    }
                } else if (prevSymbol == -1) {
                    char *buff;
                    values.top->value.symb = realloc(values.top->value.symb, sizeof(values.top->value.symb) + sizeof(char));
                    ind++;
                    values.top->value.symb[ind] = symbol;
                } else {
                    if (symbol <= '9' && symbol >= '1') {
                        StackPush(&values, (symbol - '0'), NUM);
                        prevSymbol = 0;
                    } else {
                        StackPush(&values, symbol, VAR);
                        prevSymbol = -1;
                        ind = 0;
                    }
                }

            }
        }
    symbol = getchar();
    }
    while (StackIsEmpty(&operations) != true) {
        StackPush(&values, *operations.top->value.symb, operations.top->type);
        StackPop(&operations);
    }
    //крутой вывод закоменчен((

    //printf("-----------------------STACK-----------------------\n");
    //StackPrint(&values);
    Node* tree = CreateNode(values.top->value, values.top->type);
    StackPop(&values);
    StackToTree(&values, tree);
    //printf("-----------------------TREE------------------------\n");
    PrintTree(tree);
    ReplaceMultSum(&tree);
    ReplaceMultSum(&tree);
    ReplaceMultSum(&tree);
    ReplaceMultSum(&tree);
    //printf("-------------------MODIFIED_TREE-------------------\n");
    //PrintTree(tree);
    //printf("----------------------RESULT-----------------------\n");
    PrintResult(tree);
    printf("\n");
    StackFree(&values);
    TreeFree(tree);
}

int main() {
    ReadFormula();
}