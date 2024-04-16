// структура - очередь
// процедура - поиск двух элементов, идущих подряд, в которых первый больше второго,если есть, то их перестановка
// метод - сортировка пизирьком
#include <stdio.h>
#include "queue.h"
#include "util.h"
void PrintHelp(){
    printf("a - push elem to queue(init)\n");
    printf("d - pop from queue\n");
    printf("c - do 1 operation(procedure)\n");
    printf("s - do the bubble sort\n");
    printf("p - print queue\n");
    printf("h - show this help\n");
    printf("q - quit the program\n");
    printf("f - free the queue\n");
}

int main(){
    char command;
    Queue q = QueueInit();
    int arg1;
    do {
        scanf("%c", &command);
        switch (command)
        {
        case 'a':
            scanf("%d", &arg1);
            QueuePush(&q, arg1);
        break;
        case 'd':
            printf("popnut element %d\n", QueuePop(&q));
        break;
        case 'c':
            swapNearElem(&q);
        break;
        case 'p':
            QueuePrint(&q);
        break;
        case 's':
            bubbleSort(&q);
        break;
        case 'h':
            PrintHelp();
        case 'f':
            QueueFree(&q);
        break;
        }
    } while (command != 'q');
    QueueFree(&q); // чистим вилкой
    return 0;
}