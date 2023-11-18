//проверить есть ли смжные цифры в разрядах
#include <stdio.h>

int IsRep(int a) {
    int prevD = 10;
    int isValid = 0;
    a *= a > 0 ? 1 : -1; // хехе, модуль в 1 строчку
    while (a > 0) {
        int digit = a % 10;
        if (prevD == digit) {
            isValid = 1;
            break;
        }
        a /= 10;
        prevD = digit;
    }
    return isValid;
}

int main() {
    int a = 0;
    while (scanf("%d", &a) == 1) {
        printf("%d\n", IsRep(a));
    }
    return 0;
}