// Реализация колцебуферной очереди на статическом массиве
#ifndef __STACK__
#define __STACK__
#include <stdbool.h>

typedef int T;
#define GROWTH 100 // прирост буффера

typedef struct Queue {
    T *buff; // указатель на массив в буфере очереди
    int count; // колличество элементов
    int size; // размер буффера
    int headIndex; // индекс начала очереди
} Queue; 

Queue QueueInit();
void Shift(T *arr, int size, int step);
bool QueuePush(Queue *q, T value);
T QueuePop(Queue *q);
T QueueLast(Queue *q);
bool QueueIsEmpty(Queue *q);
void QueuePrint(Queue *q);
void QueueFree(Queue *q);

#endif
