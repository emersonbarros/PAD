#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    int l = 0;
    int m, n;

    scanf("%d%d", &m, &n);
    
    //int mat[m][n];
    for(l = 0; l < (m*n*3); l++) {
        printf("%i",rand() % (9 + 1 - 0) + 0);
        printf("\n");
    }
}
