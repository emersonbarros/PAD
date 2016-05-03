#include <pthread.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#define num_threads 8

struct MATRIX {
    int rows;
    int cols;
    int* t;
};
#define M(m, x, y) m.t[x + y * m.cols]

struct MATRIX new_matrix(int cols, int rows)
{
    struct MATRIX t;
    t.rows = rows;
    t.cols = cols;
    t.t = (int*)malloc(sizeof(int) * cols * rows);
    return t;
}

void print_matrix(struct MATRIX t)
{
    int i, j;
    for(i = 0; i < t.rows; i++) {
        printf("| ");
        for(j = 0; j < t.cols; j++)
            printf("%d ", M(t, j, i));
        printf("|\n");
    }
    printf("\n");
}

struct thread_struct {
    struct MATRIX a;
    struct MATRIX b;
    struct MATRIX result;
    int id;
    int tamanho;
};

struct thread_struct threads_struct[num_threads];

void* matrix_mult(void* arguments)
{
    int c, d, k, sum = 0, inicio, fim;
    struct thread_struct* args = arguments;

    struct MATRIX a = args->a;
    struct MATRIX b = args->b;

    int x, y, z;
    struct MATRIX r;
    r = new_matrix(a.cols, a.rows);

    int s = args->id;
    int from = (s * args->tamanho) / num_threads;
    int to = ((s + 1) * args->tamanho) / num_threads;

    for(c = from; c < to; c++) {
        for(d = 0; d < b.rows; d++) {
            for(k = 0; k < a.cols; k++) {
                sum = sum + M(a, c, k) * M(b, k, d);
            }
            M(r, c, d) = sum;
            sum = 0;
        }
    }

    args->result = r;
}

int main(int argc, char* argv[])
{
    clock_t begin, end;
    double time_spent;

    pthread_t threads[num_threads];

    FILE* fp;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;
    int i, j, tamanho, c, d, k, sum = 0, numLinha = 0;

    int size = atoi(argv[1]);
    struct MATRIX primeiraMatriz, segundaMatriz, resultado;
    primeiraMatriz = new_matrix(size, size);
    segundaMatriz = new_matrix(size, size);
    resultado = new_matrix(size, size);

    printf("Entre com o numero de linhas e colunas\n");
    scanf("%d", &tamanho);

    int* arrayNum = malloc((tamanho * tamanho * 2) * sizeof(int));

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
    for(i = 0; i < tamanho; i++) {
        for(j = 0; j < tamanho; j++) {
            M(primeiraMatriz, i, j) = arrayNum[numLinha++];
        }
    }

    for(i = 0; i < tamanho; i++) {
        for(j = 0; j < tamanho; j++) {
            M(segundaMatriz, i, j) = arrayNum[numLinha++];
        }
    }

    print_matrix(primeiraMatriz);
    print_matrix(segundaMatriz);

    begin = clock();
    int rc;
    long t;
    for(t = 0; t < num_threads; t++) {
        threads_struct[t].a = primeiraMatriz;
        threads_struct[t].b = segundaMatriz;
        threads_struct[t].id = t;
        threads_struct[t].tamanho = tamanho;
        
        rc = pthread_create(&threads[t], NULL, matrix_mult, (void*)&threads_struct[t]);
        if(rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }

    void* status;
    for(t = 0; t < num_threads; t++) {
        rc = pthread_join(threads[t], &status);
        if(rc) {
            printf("Erro join e %d\n", rc);
            exit(-1);
        }
        int from = (t * tamanho) / num_threads;     // note that this 'slicing' works fine
        int to = ((t + 1) * tamanho) / num_threads; // even if SIZE is not divisible by num_thrd
        for(c = from; c < to; c++) {
            for(d = 0; d < tamanho; d++) {
                M(resultado, c, d) = M(threads_struct[t].result, c, d);
            }
        }
    }
    end = clock();
    time_spent = (double)(end - begin) * 1000 / CLOCKS_PER_SEC;

    printf("Resultado:\n");
    print_matrix(resultado);

    printf("%ld\n", begin);
    printf("%ld\n", end);

    printf("Tempo gasto: %f milisegundos\n", time_spent);

    return 0;
}