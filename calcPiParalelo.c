#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdint.h>

#define num_threads 4

pthread_t callThd[num_threads];

static long num_steps = 1000000;
double sum = 0.0;
double step;

void* calpi(void* arg)
{

    int i;
    double x, s = 0.0;
    int offset = (intptr_t)arg;
    int len = (int)num_steps / (int)num_threads;
    int start = len * (int)offset;
    int end = (start + len) - 1;

    for(i = start; i <= end; i++) {
        x = (i + 0.5) * step;
        s = s + 4.0 / (1.0 + x * x);
    }

    sum = s + sum;
    pthread_exit((void*)0);
}

int main()
{

    double pi;
    int i;
    void* status;

    clock_t begin, end;
    double time_spent;

    begin = clock();

    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    step = 1.0 / (double)num_steps;

    for(i = 0; i < num_threads; i++) {
        pthread_create(&callThd[i], &attr, calpi, (void*)(intptr_t)i);
    }

    pthread_attr_destroy(&attr);

    for(i = 0; i < num_threads; i++) {
        pthread_join(callThd[i], &status);
    }

    printf("sum %lf e step %lf\n", sum, step);

    pi = step * sum;

    end = clock();
    time_spent = (double)(end - begin) * 1000 / CLOCKS_PER_SEC;

    printf("Valor de pi: %.30f\n", pi);
    printf("Tempo gasto: %f milisegundos\n", time_spent);

    pthread_exit(NULL);

    return 0;
}
