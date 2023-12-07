#include <stdio.h>
                       // яюэьыъщшчцхфутсрпонмлкйизжедгвба
#define SHIP 58720320  // 00000011100000000000000001000000
#define SOGL 66567390  // 00000011111101111011110011011110

typedef long long Set;
typedef long long Uchar;

Uchar GetUnicode() {
    int c = getchar();
    if (c >> 7 == 0) {
        return c;
    }
    if (c >> 5 == 6) { //110
        int c2 = getchar(); // 110xxxxxx 10yyyyyyy
        return ((c & 31) << 6) | (c2 & 63); //c & 00011111
    }
    if (c >> 4 == 14) { // 00001110 
        int c2 = getchar();
        int c3 = getchar();
        return ((c & 15) << 12) | ((c2 & 63) << 6) | (c3 & 63);
    }
    if (c >> 3 == 30) { // 00011110
        int c2 = getchar();
        int c3 = getchar();
        int c4 = getchar();
        return ((c & 7) << 18) | ((c2 & 63) << 12) | ((c3 & 63) << 6) |
               (c4 & 63);
    }
    return -1;
}

Uchar GetNumUnicode(char *c) {
    int ch =  c[0] & 0xFF; //костыль без него не работает
    if (ch >> 7 == 0) {
        return ch;
    }
    if (ch >> 5 == 6) { //110
        return ((ch & 31) << 6) | (c[1] & 63); //c & 00011111
    }
    if (ch >> 4 == 14) { // 00001110 
        return ((ch & 15) << 12) | ((c[1] & 63) << 6) | (c[2] & 63);
    }
    if (ch >> 3 == 30) { // 000111s10
        return ((ch & 7) << 18) | ((c[1] & 63) << 12) | ((c[2] & 63) << 6) |
               (c[3] & 63);         
    }
}
    
int IsSeparator(Uchar c){
    return (c == ' ') || (c == ',') || (c == '\n') || (c == EOF) || (c == '\t');
}

void Add(Set *a, Uchar c) { //сразу с туловер
    if (c >= GetNumUnicode("а") && c <= GetNumUnicode("я")){
        *a = *a | 1llu << (c - GetNumUnicode("а"));
    } else if (c >= GetNumUnicode("А") && c <= GetNumUnicode("Я")){
        *a = *a | 1llu << (c - GetNumUnicode("А"));
    }
}

int IsSubSet(Set a, Set b){
    Set res = a & b; // 0111 ^ 0000 => 0000
    return res == b;
}

int main() {
    int flag = 0;
    int isWodStarted = 0;
    Set word = 0;
    while (1) {
        Uchar c = GetUnicode();
        if (!IsSeparator(c)) {
            isWodStarted = 1;
            Add(&word, c);
        } else {
            if (isWodStarted) {
                flag = IsSubSet(SHIP, word & SOGL) && ((word & SOGL) != 0llu);
            }
            word = 0;
            if (flag){
                printf("YES\n");
                break;
            }
            isWodStarted = 0;
        }

        if (c == EOF) {
            printf("NO\n");
            break;
        }
    }
    return 0;
}
