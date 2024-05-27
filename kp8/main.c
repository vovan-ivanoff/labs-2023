#include <stdio.h>
#include <string.h>
#include "list.h"

void PrintHelp(){
    printf("--------------------------------\n");
    printf("$ a <value> - add value\n");
    printf("$ p - print list\n");
    printf("$ f - check if list is sorted\n");
    printf("$ c - show length of list\n");
    printf("$ d <value> - delete value\n");
    printf("$ q - quit\n");
    printf("$ h - print this help\n");
    printf("--------------------------------\n");

}
// функция проверки списка на упорядоченность
void Menu(List *nums) {
    char command;
    T num;
    Iterator iter;
    do {
      scanf("%c", &command);
      switch(command){
        case 'p':
            Print(&nums);
        break;
        case 'h':
        PrintHelp();
        break;
        case 'f':
            if (IsSorted(&nums)){
                    printf("spisok uporyadochen\n");
                }
                else {
                    printf("spisok NEuporyadochen\n");
                }
        break;
        case 'a':
            scanf("%lf", &num);
            InsertAfter(&nums, num, Last(&nums));
        break;
        case 'c':
            printf("%d\n", Count(&nums));
        break;
        case 'd':
           scanf("%lf", &num);
           DeleteNum(nums, num);
        break; 
      }

    } while (command != 'q');
    Destroy(nums);
}

int main() {
    List *nums;
    ListInit(&nums);
    Menu(nums);
    Destroy(nums);
    return 0;   
}