#include <stdio.h>

int Min(int a, int b) {
    return a < b ? a : b;
}

int Max(int a, int b, int c) {
    if (a > b && a > c){
        return a;
    } else {
        return b > c ? b : c;
    }
}

int Mod(int x, int div) {
    int m = x % div;
    if(m < 0) {
        m = (div < 0) ? m - div: m + div;
    }
    return m;
}

int Sign(int a) {
    if (a > 0) return 1;
    else if (a < 0) return -1;
    else return 0;
}

int CheckDestination(int i, int j) {
    return (i - 10) * (i - 10) + (j - 10) * (j - 10) <= 100 && (i - 10) * (i - 10) + (j - 10) * (j - 10) >= 25;
}

int main(int argc, char *argv[]) {
    int i = 26;
    int j = 8;
    int l = -3;
    int flag = 0;
    // printf("%d", checkDestination(i,j));
    for (short k = 0; k < 50; k++) {
        int nextI = Mod(Min(i + j,i + l) * (k+1),30);
        int nextJ = j + Mod(l * Sign(j), 20) + Mod(k * Sign(i), 10);
        int nextL = Mod(Max(i * j,i * l,j * l), 30);
        if (CheckDestination(nextI, nextJ) == 1) {
            flag = 1;
            printf("YES %d\n",k);
            break;
        }
        i = nextI;
        j = nextJ;
        l = nextL;
    }
    if (flag == 0) {
        printf("NO\n");
    }
    return 0; 
}
