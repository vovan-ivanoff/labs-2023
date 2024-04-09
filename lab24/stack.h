#ifndef __STACK__
#define __STACK__
#include <stdbool.h>


typedef enum type {
    VAR, NUM, SYMB
} type;

union data
{
    char* symb;
    int num;
};

typedef struct Cell {
    type type;
    union data value;
    struct Cell *next;
} Cell;

typedef struct Stack {
    int len;
    Cell *top;
} Stack;

Stack StackInit();
void StackPush(Stack *stk, int value, type type);
union data StackPop(Stack *stk);
union data StackTop(Stack *stk);
bool StackIsEmpty(Stack *stk);
void StackPrint(Stack *stk);
void StackFree(Stack *stk); 

#endif