#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define atoa(x)

int main(int argc, char* argv[])
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i, m, n, c, d, k, sum = 0, numLinha = 0;

    clock_t begin, end;
    double time_spent;

    printf("Entre com o numero de linhas e colunas\n");
    scanf("%d%d", &m, &n);

    // static int arrayNum[n * m * 2];

    int* arrayNum = malloc((n * m * 2) * sizeof(int));

    int(*primeiraMatriz)[m];
    primeiraMatriz = (int(*)[m])malloc(sizeof(*primeiraMatriz) * n);

    int(*segundaMatriz)[m];
    segundaMatriz = (int(*)[m])malloc(sizeof(*segundaMatriz) * n);

    int(*resultado)[m];
    resultado = (int(*)[m])malloc(sizeof(*resultado) * n);

    printf("%s\n\n", argv[1]);

    fp = fopen(argv[1], "r");
    if(fp == NULL) {
        printf("Erro ao abrir o arquivo!");
    } else {
        while((read = getline(&line, &len, fp)) != -1) {
            arrayNum[numLinha] = atoi(line);
            numLinha++;
        }
    }

    numLinha = 0;
    for(c = 0; c < m; c++)
        for(d = 0; d < n; d++) {
            primeiraMatriz[c][d] = arrayNum[numLinha];
            numLinha++;
        }

    for(c = 0; c < m; c++)
        for(d = 0; d < n; d++) {
            segundaMatriz[c][d] = arrayNum[numLinha];
            numLinha++;
        }

    printf("Primeira Matriz:\n");
    for(c = 0; c < m; c++) {
        for(d = 0; d < n; d++)
            printf("%d\t", primeiraMatriz[c][d]);

        printf("\n");
    }

    printf("Segunda Matriz:\n");
    for(c = 0; c < m; c++) {
        for(d = 0; d < n; d++)
            printf("%d\t", segundaMatriz[c][d]);

        printf("\n");
    }

    begin = clock();
    for(c = 0; c < m; c++) {
        for(d = 0; d < n; d++) {
            for(k = 0; k < m; k++) {
                sum = sum + primeiraMatriz[c][k] * segundaMatriz[k][d];
            }
            resultado[c][d] = sum;
            sum = 0;
        }
    }
    end = clock();
    time_spent = (double)(end - begin) * 1000 / CLOCKS_PER_SEC;

    printf("Resultado:\n");

    for(c = 0; c < m; c++) {
        for(d = 0; d < n; d++)
            printf("%3d\t", resultado[c][d]);

        printf("\n");
    }

    printf("Tempo gasto: %f milisegundos\n", time_spent);

    return 0;
}