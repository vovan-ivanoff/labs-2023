#include <stdio.h>
#include <stdbool.h>
#include "queue.h"
#include <stdlib.h>

void PrintT(T a) {
    printf("%d", a);
}

Queue QueueInit() {
    Queue q;
    q.count = 0;
    q.size = GROWTH;
    q.buff = (T *)malloc(sizeof(T) * q.size);
    return q;
}

void Shift(T *arr, int size, int step) {
    step %= size;
    for (int j = 0; j < step; j++) {
        T first = arr[0];
    
        for (int i = 1; i < size; i++)
            arr[i - 1] = arr[i];
        
        arr[size - 1] = first;
    }
}

bool QueuePush(Queue *q, T value) {
    if (q->count >= q->size) {
        Shift(q->buff, q->size, q->headIndex);
        q->headIndex = 0;
        q->size += GROWTH;
        q->buff = (T *)realloc(q->buff, sizeof(T) * q->size);
        if (q->buff == NULL) {
            return false;
        }
    }

    if (q->count == 0) {
        q->headIndex = 0;
    } else {
        q->headIndex = (q->headIndex - 1) % q->size;
        if (q->headIndex < 0) {
            q->headIndex += q->size;
        }
    }

    q->buff[q->headIndex] = value;
    q->count++;
    return true;
}

T QueuePop(Queue *q) {
    if (q->count <= 0) {
        return -1;
    }

    T result = q->buff[(q->headIndex + --q->count) % q->size];

    if (q->size - q->count >= GROWTH) {
        Shift(q->buff, q->size, q->headIndex);
        q->headIndex = 0;
        q->size -= GROWTH / 2;
        q->buff = (T *)realloc(q->buff, sizeof(T) * q->size);
        if (q->buff == NULL) {
            return -1;
        }
    }

    return result;
}

T QueueLast(Queue *q) {
    if (q->count <= 0) {
        return -1;
    }

    return q->buff[(q->headIndex + q->count - 1) % q->size];
}

bool QueueIsEmpty(Queue *q) {
    return q->count <= 0;
}

void QueuePrint(Queue *q) {
    if (QueueIsEmpty(q)) {
        printf("\nQueue is empty");
    }

    for (int i = 0; i < q->count; i++) {
        PrintT(q->buff[(i + q->headIndex) % q->size]);
        if (i < q->count - 1) {
            printf(" -> ");
        }
    }

    printf("\n");
}

void QueueFree(Queue *q) {
    q->count = 0;
}
