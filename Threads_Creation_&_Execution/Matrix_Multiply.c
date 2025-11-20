#include <stdio.h>
#include <pthread.h>

int A[4][4] = {
    {1,2,3,4},
    {5,6,7,8},
    {9,10,11,12},
    {13,14,15,16}
};

int B[4][4] = {
    {1,0,1,0},
    {0,1,0,1},
    {1,0,1,0},
    {0,1,0,1}
};

int C[4][4];

void* multiply_row(void* arg) {
    int r = *(int*)arg;
    for (int c = 0; c < 4; c++) {
        C[r][c] = 0;
        for (int k = 0; k < 4; k++) C[r][c] += A[r][k] * B[k][c];
    }
    return NULL;
}

int main() {
    pthread_t t[4];
    int rows[4] = {0,1,2,3};

    for (int i = 0; i < 4; i++) pthread_create(&t[i], NULL, multiply_row, &rows[i]);
    for (int i = 0; i < 4; i++) pthread_join(t[i], NULL);

    printf("Matrix A:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) printf("%d ", A[i][j]);
        printf("\n");
    }

    printf("Matrix B:\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) printf("%d ", B[i][j]);
        printf("\n");
    }

    printf("Matrix C (Result):\n");
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) printf("%d ", C[i][j]);
        printf("\n");
    }

    printf("Sequential Verification:\n");
    int seq[4][4];
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++) {
            seq[i][j] = 0;
            for (int k = 0; k < 4; k++) seq[i][j] += A[i][k] * B[k][j];
            printf("%d ", seq[i][j]);
            if (j == 3) printf("\n");
        }

    return 0;
}
