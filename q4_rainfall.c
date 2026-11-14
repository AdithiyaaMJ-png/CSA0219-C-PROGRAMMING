#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 2000

static double mat[SIZE][SIZE];

int main(void) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            mat[i][j] = (i + j) * 0.1;
        }
    }

    volatile double sum = 0.0;
    clock_t start, end;

    start = clock();
    for (int r = 0; r < 20; r++) {
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                sum += mat[i][j];
            }
        }
    }
    end = clock();
    double row_time = (double)(end - start) / CLOCKS_PER_SEC;

    start = clock();
    for (int r = 0; r < 20; r++) {
        for (int j = 0; j < SIZE; j++) {
            for (int i = 0; i < SIZE; i++) {
                sum += mat[i][j];
            }
        }
    }
    end = clock();
    double col_time = (double)(end - start) / CLOCKS_PER_SEC;

    printf("Row-wise traversal (2000x2000) : %.4f seconds (Sequential cache hits)\n", row_time);
    printf("Column-wise traversal (2000x2000): %.4f seconds (%.1fx slower due to cache misses!)\n",
           col_time, row_time > 0 ? col_time / row_time : 0.0);

    return 0;
}
