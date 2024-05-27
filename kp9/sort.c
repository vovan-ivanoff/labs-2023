#include "sort.h"

void hSortR(Table *t) {
    hSort(t, 0, (t->size)-1);
}
void hSort(Table *t, int start, int end) {
    int pivot = Partition(t, start, end);
    if(start < end) {
        hSort(t, start, pivot);
        hSort(t, pivot + 1, end);
    }
}
int Partition(Table *t, int start, int end){
    item p = t->rows[(start + end) / 2];
    int j = end;
    int i = start;
    while(1){
        while(KeyCmp(t->rows[i].key, p.key) < 0) i++;
        while(KeyCmp(t->rows[j].key, p.key) > 0) j--;
        if(i >= j) return j;
        int k = i++;
        int l = j--;
        item tmp = t->rows[k];
        t->rows[k] = t->rows[l];
        t->rows[l] = tmp;
    }
}
