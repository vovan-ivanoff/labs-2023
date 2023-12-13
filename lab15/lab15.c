#include <stdio.h>
#define MAX_M 8

void PrintMatrix(int *m, int width, int height){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) { 
            printf("%d ", m[i * height + j]);
        }
        putchar('\n');
    }
}

int GetMatrix(int *m) {
    int width = 0;
    for (int i = 0; i < 7; i ++){
        //printf("a");
        if (scanf("%d", &m[i]) == 0) continue;
        if (getchar() == '\n'){
            width = i + 1;
            break;
        }
    }
    //printf("width: %d", width);
    for(int i = 1; i < width; i ++){
        for (int j = 0; j < width; j ++){
            scanf("%d", &m[i * width + j]);
        }
    }
    return width;
}

void DoStuff(int *mIn, int *mOut, int width){
    int min = mIn[0];
    int max = mIn[0];
    int counter = 0;
    for (int i = 0; i < (width * width); i ++) {
        int elem = mIn[i];
        if (elem < min) min = elem;
        if (elem > max) max = elem;
    }
    for (int j = 0; j < width; j++){
        for (int i = 0; i < width; i++){
            int elem = mIn[i * width + j];
            if (elem == min) {
                counter++;
                break;
            }
        }
    }
    for (int i = 0; i < (width * width); i ++) {
        int elem = mIn[i];
        if (elem == max) mOut[i] = counter;
        else mOut[i] = elem;
    }

}

int main() {
    int matrix[MAX_M][MAX_M];
    int oMx[MAX_M][MAX_M];
    int w = GetMatrix(*matrix);
    DoStuff(*matrix, *oMx, w);
    PrintMatrix(*oMx, w, w);
    return 0;
}