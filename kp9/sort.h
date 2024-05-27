#ifndef __SORT__
#define __SORT__
#include "table.h"

void hSortR(Table *t);
void hSort(Table *t, int start, int end);
int Partition(Table *t, int start, int end);
#endif