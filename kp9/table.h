#ifndef __TABLE__
#define __TABLE__
#define KEY_SIZE 32
#define MAX_LEN 256
#define MIN_CAPACITY 18

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct Key {
    char str[KEY_SIZE-sizeof(int)];
    int num;
} Key;

typedef struct item {
    Key key;
    char val[MAX_LEN];
} item;



typedef struct Table {
    item* rows;
    int size;
    int capacity;
} Table;

Table* CreateTable();
bool Add(Table* t, item r);
bool Buffer(Table* t);
void Print(Table* t);
void Destroy(Table* t);
int Search(Table* t, Key k);
int KeyCmp(Key k1, Key k2);

#endif