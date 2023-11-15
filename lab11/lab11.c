#include <stdio.h>

int IsSeparator(char c) {
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF);
}

int IsDigit(char c) {
    return c >= '0' && c <= '9';
}

// вывод числа в необычных СС

void PBaseR(long long input, int base){
    if(input > 0){
        PBaseR(input / base, base);
        if (input % base > 9){
            putchar((input % base) % 10 + 'A');
        } else {
            putchar(input % base + '0');
        }
    }
}

void PrintBase(long long input, int base){
    if (input < 0){
        putchar('-');
        input *= -1;
    }
    if (input == 0) putchar('0');
    PBaseR(input, base);
    putchar('\n');
}

int main() {
    long long wordCounter = 0;
    int isWodStarted = 0;
    int isWordIsNumber = 1;
    int isWasDigits = 0;
    long long buffer = 0;
    long long lastNum = 0;
    long long preLastNum = 0;
    int sign = 1;
    while (1) {
        int c = getchar();
        if (!IsSeparator(c)) {
            isWasDigits = isWasDigits || IsDigit(c);
            isWordIsNumber = isWordIsNumber && (IsDigit(c) || (!isWodStarted && c == '-'));
            isWodStarted = 1;

            if (c == '-') {
                sign = -1;
            }

            if (IsDigit(c)) {
                buffer = buffer * 10 + (c - '0');
            }
        } else {
            if (isWodStarted && isWordIsNumber && isWasDigits) {
                preLastNum = lastNum;
                lastNum = buffer * sign;
                wordCounter += 1;
            }

            isWodStarted = 0;
            isWordIsNumber = 1;
            isWasDigits = 0;
            buffer = 0;
            sign = 1;

        }

        if (c == EOF) {
            break;
        }
    }

    if (wordCounter < 2) {
        printf("NO\n");
        return 0;
        
    }
    PrintBase(preLastNum, 3);
    PrintBase(preLastNum, 7);
    PrintBase(preLastNum, 11);
    return 0;
}
