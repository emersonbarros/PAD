#include <omp.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i, m, n, c, d, k, sum = 0, numLinha = 0;

    int nthreads, tid;

    printf("Entre com o numero de linhas e colunas\n");
    scanf("%d%d", &m, &n);

    int* arrayNum = malloc((n * m * 3) * sizeof(int));

    int(*matrizA)[m];
    int(*matrizB)[m];
    int(*matrizC)[m];
    int(*resultado)[m];

    matrizA = (int(*)[m])malloc(sizeof(*matrizA) * n);
    matrizB = (int(*)[m])malloc(sizeof(*matrizB) * n);
    matrizC = (int(*)[m])malloc(sizeof(*matrizC) * n);

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
            matrizA[c][d] = arrayNum[numLinha];
            numLinha++;
        }

    printf("%s\n\n", argv[2]);

    fp = fopen(argv[2], "r");
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
            matrizB[c][d] = arrayNum[numLinha];
            numLinha++;
        }

    printf("%s\n\n", argv[3]);

    fp = fopen(argv[3], "r");
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
            matrizC[c][d] = arrayNum[numLinha];
            numLinha++;
        }

    printf("Matriz A:\n");
    for(c = 0; c < m; c++) {
        for(d = 0; d < n; d++)
            printf("%d\t", matrizA[c][d]);

        printf("\n");
    }

    printf("Matriz B:\n");
    for(c = 0; c < m; c++) {
        for(d = 0; d < n; d++)
            printf("%d\t", matrizB[c][d]);

        printf("\n");
    }

    printf("Matriz C:\n");
    for(c = 0; c < m; c++) {
        for(d = 0; d < n; d++)
            printf("%d\t", matrizB[c][d]);

        printf("\n");
    }

#pragma omp parallel private(nthreads, tid)
    {
#pragma omp for
        for(c = 0; c < m; c++) {
            for(d = 0; d < n; d++) {
                for(k = 0; k < m; k++) {
                    sum = sum + matrizA[c][k] * matrizB[k][d];
                }
                resultado[c][d] = sum;
                sum = 0;
            }
        }

        tid = omp_get_thread_num();
        printf("thread = %d\n", tid);

        printf("Resultado Multiplicacao:\n");

        for(c = 0; c < m; c++) {
            for(d = 0; d < n; d++)
                printf("%3d\t", resultado[c][d]);

            printf("\n");
        }

#pragma omp for

        for(c = 0; c < m; c++) {
            for(d = 0; d < n; d++)
                resultado[c][d] = resultado[c][d] + matrizC[c][d];
        }

        printf("Resultado Final:\n");

        for(c = 0; c < m; c++) {
            for(d = 0; d < n; d++)
                printf("%3d\t", resultado[c][d]);

            printf("\n");
        }

        tid = omp_get_thread_num();
        printf("thread = %d\n", tid);
    }
    return 0;
}