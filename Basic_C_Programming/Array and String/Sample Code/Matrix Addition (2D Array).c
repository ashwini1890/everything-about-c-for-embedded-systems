//Matrix Addition (2D Array)

#include<stdio.h>

int main(){ 
    int a[3][2] = {{1,2},{3,4},{9,10}};
    int b[3][2] = {{5,6},{7,8},{11,12}};
    int c[3][2];

    printf("Result of matrix addition:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 2; j++) {
            c[i][j] = a[i][j] + b[i][j];
            printf("%d ", c[i][j]);
        }
        printf("\n");
    }

    return 0;
}