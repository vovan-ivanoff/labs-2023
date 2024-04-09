#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "stack.h"

Stack StackInit() {
    Stack new;
    new.top = NULL;
    return new;
}

void StackPush(Stack *stk, int value, type type) {
    Cell *new = (Cell *)malloc(sizeof(Cell));
    if (new == NULL) {
        exit(-1);
    }
    new->next = stk->top;
    stk->top = new;
    if (type == VAR) {
        stk->top->value.symb = (char*)malloc(sizeof(char));
        if (stk->top->value.symb == NULL) {
            exit(-1);
        }
        *stk->top->value.symb = value;
        stk->top->type = VAR;
    } else if (type == NUM) {
        stk->top->value.num = value;
        stk->top->type = NUM;
    } else {
        stk->top->value.symb = (char*)malloc(sizeof(char));
        if (stk->top->value.symb == NULL) {
            exit(-1);
        }
        *stk->top->value.symb = value;
        stk->top->type = SYMB;
    }
    stk->len += 1;
}

union data StackPop(Stack *stk) {
    union data d = stk->top->value;
    Cell *buff = stk->top;
    stk->top = stk->top->next;
    stk->len -= 1;
    free(buff);
    return d;
}

union data StackTop(Stack *stk) {
    return stk->top->value;
}

bool StackIsEmpty(Stack *stk) {
    return stk->top == NULL;
}

void StackPrint(Stack *stk) {
    for (Cell *i = stk->top; i != NULL; i = i->next) {
        if (i->type == VAR) {
            printf("%s", i->value.symb);
        } else if (i->type == NUM) {
            printf("%d", i->value.num); 
        } else {
            printf("%c", *i->value.symb); 
        }
        if (i->next != NULL) {
            printf(" ");
        }
    }
    printf("\n");
}

void StackFree(Stack *stk) {
    Cell *next;
    for (Cell *i = stk->top; i != NULL; i = next) {
        next = i->next;
        free(i);
    }
}