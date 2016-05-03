#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int l = 0;
    int m, n;

    scanf("%d%d", &m, &n);
    
    int mat[m][n];
    for(l = 0; l < m; l++) {
        for(int c = 0; c < n; c++) {
            mat[l][c] = rand() % (9 + 1 - 0) + 0;
        }
    }

    for(l = 0; l < m; l++) {
        for(int c = 0; c < n; c++) {
            printf("%i ", mat[l][c]);
        }
        printf("\n");
    }
}
