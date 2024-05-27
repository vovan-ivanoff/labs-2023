#include "table.h"
#include "sort.h"



Table* CreateTable() {
    Table* tb = (Table*)malloc(sizeof(Table));
    if(!tb) {
        return NULL;
    } 
    item* data = (item*)malloc(MIN_CAPACITY * sizeof(item));
    if(!data) {
        free(tb);
        return NULL;
    }
    tb->capacity = MIN_CAPACITY;
    tb->rows = data;
    tb->size = 0;
    return tb;
}

bool Buffer(Table* t) {
    if(t->size < t->capacity)
        return true;
    int new_cap = 2 * t->capacity;
    item* tmp = (item*)realloc(t->rows, sizeof(item) * new_cap);
    if(!tmp) {
        return false; 
    }
    t->capacity = new_cap;
    t->rows = tmp;
    return true;
}

bool Add(Table* t, item r) {
    if(!Buffer(t))
        return false; 
    t->rows[t->size] = r;
    t->size++;
    return true;
}

void Print(Table* t) {
    for(int i = 0; i < t->size; ++i)
        printf("%2d | %s%d | %s\n", i, t->rows[i].key.str, t->rows[i].key.num, t->rows[i].val);
}

void Destroy(Table* t) {
    free(t->rows);
    free(t);
}

int Search(Table* t, Key k) {
    int l = 0;
    int r = t->size - 1;
    int result = -1;
    while(l <= r) {
        int x = (l + r) >> 1;
        int c;
        if (KeyCmp(t->rows[x].key, k) == 0) {
            c = 0;
        } else if (KeyCmp(t->rows[x].key, k) > 0) {
            c = 1;
        } else {
            c = -1;
        }
        if(c == 0) {
            result = x;
            r = x - 1;
        } else if(c > 0)
            r = x - 1;
        else 
            l = x + 1;
    }
    return result;
}

int KeyCmp(Key k1, Key k2){ // возвр 1 если к1 > k2, 0 равны, -1 k1 < k2
    if(k1.num == k2.num && !(strcmp(k1.str, k2.str))){
        return 0;
    } else if (strcmp(k1.str, k2.str) > 0) {
        return 1;
    } else if (k1.num > k2.num && !(strcmp(k1.str, k2.str))){
        return 1;
    } else if (strcmp(k1.str, k2.str) < 0) {
        return -1;
    } else if (k1.num < k2.num) {
        return -1;
    }
}