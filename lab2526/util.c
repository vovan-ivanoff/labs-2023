#include "util.h"
#include "queue.h"

void swapNearElem(Queue* que){ // перестановка элементов в очереди, ели первый больше второго 
    Queue buf = QueueInit();
    int prev = QueuePop(que); // попа первого элемента
    while (!QueueIsEmpty(que)){
            int val = QueuePop(que); // попаем элемент
            if (val > prev){
                QueuePush(&buf, val);
            } else {
                QueuePush(&buf, prev);
                prev = val;
            }
        }
    QueuePush(&buf, prev);
    while (!QueueIsEmpty(&buf)){
        QueuePush(que, QueuePop(&buf));
    }
}
void bubbleSort(Queue* que){
    for (int i = 0; i < que->count; i++) {
        swapNearElem(que);
    }
}
