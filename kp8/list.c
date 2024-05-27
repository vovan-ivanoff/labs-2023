#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

Item *CreateItem(T value, Iterator prev, Iterator next) {
    Item *i = (Item *)malloc(sizeof(Item));
    i->next = next.node;
    i->prev = prev.node;
    i->value = value;
    return i;
}

void ListInit(List **l) {
    *l = (List *)malloc(sizeof(List));
    (*l)->first = (*l)->last = NULL;
}

Iterator Last(List **l) {
    return (Iterator){(*l)->last};
}

Iterator First(List **l)  {
    return (Iterator){(*l)->first};
}

Iterator Next(Iterator iter)  {
    return (Iterator){iter.node->next};
}

Iterator Previous(Iterator iter)  {
    return (Iterator){iter.node->prev};
}

Iterator InsertAfter(List **l, T value, Iterator iter) {

    if (IsEmpty(l)) {
        (*l)->first = (*l)->last = CreateItem(value, First(l), Last(l));
        return First(l);
    } else if (IsEqual(iter, Last(l))) {
        (*l)->last = CreateItem(value, Last(l), Next(Last(l)));
        (*l)->last->prev->next = (*l)->last;
    } else {
        iter.node->next = CreateItem(value, iter, Next(iter));
        iter.node->next->next->prev = iter.node->next;
    }

    return Next(iter);

}

Iterator InsertBefore(List **l, T value, Iterator iter) {
    if (IsEmpty(l)) {
        (*l)->first = (*l)->last = CreateItem(value, First(l), Last(l));
        return First(l);
    } else if (IsEqual(iter, First(l))) {
        (*l)->first = CreateItem(value, Previous(First(l)), First(l));
        First(l).node->next->prev = First(l).node;
    } else {
        iter.node->next = CreateItem(value, Previous(iter), iter);
        iter.node->prev->prev->next = iter.node->prev;
    }

    return Previous(iter);
}

bool IsEqual(Iterator iter1, Iterator iter2) {
    return iter1.node == iter2.node;
}

bool IsTerminator(Iterator iter) {
    return iter.node == NULL;
}

bool IsEmpty(List **l) {
    return (*l)->first == NULL;
}

void DeleteNum(List *l, T value) {
    Iterator prev;
    for (Iterator i = First(&l); !IsTerminator(i); i = Next(i)) {
        if (i.node->value == value) {
            if (IsEqual(i, First(&l))) {
                free(l->first);
                *l->first = *Next(i).node;
                break;
            }
            if (IsEqual(i, Last(&l))) {
                free(l->last);
                prev.node->next = NULL;
                *l->last = *prev.node;
                break;
            }
            prev.node->next = Next(i).node;
            prev.node->next->prev = prev.node;
            free(i.node);
        }
        prev = i;
    }
}

T Delete(List **l, Iterator iter) {
    if (IsEmpty(l) || IsTerminator(iter)) {
        return -1;
    } 

    T result = GetValue(iter);

    if (IsEqual(iter, First(l))) {
        (*l)->first = Next(iter).node;
        (*l)->first->prev = NULL;
    } else if (IsEqual(iter, Last(l))) {
        (*l)->last = Previous(iter).node;;
        (*l)->last->next = NULL;
    }  else {
        iter.node->next->prev = iter.node->prev;
        iter.node->prev->next = iter.node->next;
    }
    free(iter.node);
    return result;
}

T GetValue(Iterator iter) {
    return iter.node->value;
}

void SetValue(Iterator iter, T value) {
    iter.node->value = value;
}

void Swp(T *a, T *b) {
    T c = *a;
    *a = *b;
    *b = c;
}

int Count(List **l) {
    int k = 0;
    if (IsEmpty(l)) {
        return 0;
    }
    for (Iterator i = First(l); !IsTerminator(i); i = Next(i)) {
        k++;
    }
    return k;
}

void Swap(List **l) {
    if (!IsEmpty(l)) {
        if (Count(l) >= 2) {
            Swp(&(Next(First(l))).node->value, &Last(l).node->value);
        }
    }
}

void Print(List **l) {
    for (Iterator i = First(l); !IsTerminator(i); i = Next(i)) {
        printf("%lf ", GetValue(i));
    }
    printf("\n");
}

void Destroy(List *l) {
    Iterator next = First(&l);
    for (Iterator i = First(&l); !IsTerminator(i); i = Next(next)) {
        next = i;
        free(i.node);
    }
    l->first = l->last = NULL;
}

int IsSorted(List **l) {
    Iterator i = First(l);
    T prevVal = i.node->value;
    for (i; !IsTerminator(i); i = Next(i)) {
        if((i.node)->value < prevVal) {
            return 0;
        }
        prevVal = i.node->value;
    }
    return 1;
}