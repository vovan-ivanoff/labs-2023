#ifndef __LIST__
#define __LIST__
#include <stdbool.h>

typedef double T;

typedef struct Item {
    T value;
    struct Item *prev;
    struct Item *next;
} Item;

typedef struct Iterator {
    Item *node;
} Iterator;

typedef struct List {
    Item *first;
    Item *last;
} List;

Item *CreateItem(T value, Iterator prev, Iterator next);
void ListInit(List **l);
Iterator Last(List **l);
Iterator First(List **l);
Iterator Next(Iterator iter);
Iterator Previous(Iterator iter);
Iterator InsertAfter(List **l, T value, Iterator iter);
Iterator InsertBefore(List **l, T value, Iterator iter);
bool IsEqual(Iterator iter1, Iterator iter2);
bool IsTerminator(Iterator iter);
bool IsEmpty(List **l);
T Delete(List **l, Iterator iter);
void DeleteNum(List *l, T value);
T GetValue(Iterator iter);
void SetValue(Iterator iter, T value);
void Swp(T *a, T *b);
void Swap(List **l);
int Count(List **l);
void Print(List **l);
void Destroy(List *l);
int IsSorted(List **l);
#endif