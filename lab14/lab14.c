#include <stdio.h>
#define MAX_M 11
void PrintMatrix(int *m, int width, int height){
    for (int i = 0; i < height; i++){
        for (int j = 0; j < width; j++) { 
            printf("%d ", m[i * height + j]);
        }
        //putchar('');
    }
}

int GetMatrix(int *m) {
    int width = 0;
    for (int i = 0; i < MAX_M; i ++){
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
    int x = 0;
    int y = 0;
    int flag = 1;
    //printf("%d %d\n", x, y);
    for(int i = 0; i < width; i++){
        for (int j = 0; j < width; j ++) {
            mOut[i * width + j] = mIn[y * width + x];
            if (flag) {
                x += 1;
                y += 1;
                if (x > width - 1){
                    x = width - 1;
                    y -=2;
                    flag = 0;
                } else if (y > width - 1) {
                    y = 0;
                    x = width - x;
                }
            } else {
                y -= 1;
                x -= 1;
                if (x < 0){
                    x = 0;
                    y += 2;
                    flag = 1;
                } else if (y < 0) {
                    y = width - 1;
                    x = width - x - 2;
                }
            }
        }
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