#include <iostream>
#include <time.h>
#include <math.h>
#include "matrixUtils.hpp"
#include "invertingManager.hpp"
#include <sys/time.h>

using namespace std;

#define INPUT_FILE "data.dat"

long int get_time(void);
long int get_full_time(void);

typedef struct
{
    int n;
    double *matrix;
    double *inverseMatrix;
    int rank;
    int threadsCount;
} ARGS;

long int thread_time = 0;

pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;

void *Inversion(void *p_arg)
{
    ARGS *arg = (ARGS*)p_arg;
    long int t1;
    
    t1 = get_time();
    invertMatrix(arg->matrix, arg->inverseMatrix, arg->n, arg->rank, arg->threadsCount);
    t1 = get_time() - t1;
    
    pthread_mutex_lock(&myMutex);
    thread_time += t1;
    pthread_mutex_unlock(&myMutex);
    
    return NULL;
}

int main(int argc, char **argv)
{
    int i;
    int n;
    double *matrix;
    double *inverseMatrix;
    int mode;
    FILE *input;
    long int t_full;
    int total_threads;
    pthread_t *threads;
    ARGS *args;
    
    if (argc > 1)
        total_threads = atoi(argv[1]);
    else
    {
        printf("Incorrect usage!\n");
        return -1;
    }
    
    mode = 2; /* Change this for inputing from file */
    
    switch (mode)
    {
        case 1:
            if ((input = fopen(INPUT_FILE, "r")) == NULL)
            {
                printf("Can't open file \"%s\"!\n", INPUT_FILE);
                return -2;
            }
            else fscanf(input, "%d", &n);
            break;
        case 2:
            input = NULL;
            /*
             printf("Matrix size: ");
             scanf("%d", &n);
             */
            if (argc == 3)
                n = atoi(argv[2]);
            else
            {
                printf("Incorrect usage!\n");
                return -3;
            }
            
            if (n <= 0)
            {
                printf("Incorrect n!\n");
                return -4;
            }
            break;
        default:
            printf("Unknown mode.\n");
            return -5;
    }
    
    matrix = (double*)malloc(n * n * sizeof(double));
    inverseMatrix = (double*)malloc(n * n * sizeof(double));
    threads = (pthread_t*)malloc(total_threads * sizeof(pthread_t));
    args = (ARGS*)malloc(total_threads * sizeof(ARGS));
    
    if (!(matrix && inverseMatrix && threads && args))
    {
        printf("Not enough memory!\n");
        
        if (matrix) free(matrix);
        if (inverseMatrix) free(inverseMatrix);
        if (threads) free(threads);
        if (args) free(args);
        
        return -4;
    }
    
    enterMatrix(matrix, n, input);
    
    for (i = 0; i < total_threads; i++)
    {
        args[i].n = n;
        args[i].matrix = matrix;
        args[i].inverseMatrix = inverseMatrix;
        args[i].rank = i;
        args[i].threadsCount = total_threads;
    }
    
    t_full = get_full_time();
    
    for (i = 0; i < total_threads; i++)
        if (pthread_create(threads + i, 0, Inversion, args + i))
        {
            printf("Cannot create thread %d!\n", i);
            
            if (matrix) free(matrix);
            if (inverseMatrix) free(inverseMatrix);
            if (threads) free(threads);
            if (args) free(args);
            
            return -7;
        }
    
    for (i = 0; i < total_threads; i++)
        if (pthread_join(threads[i], 0))
        {
            printf("Cannot wait thread %d!\n", i);
            
            if (matrix) free(matrix);
            if (inverseMatrix) free(inverseMatrix);
            if (threads) free(threads);
            if (args) free(args);
            
            return -8;
        }
    
    t_full = get_full_time() - t_full;
    
    if (t_full == 0)
        t_full = 1;
    
    printf("\nMatrix A^{-1}:\n");
    printMatrix(inverseMatrix, n, 10);//TODO
    
    printf("\n\nInversion time = %ld\nTotal threads time = %ld"\
           " (%ld%%)\nPer thread = %ld\n",
           t_full, thread_time, thread_time * 100/t_full,
           thread_time/total_threads);
    
    if (mode == 1)
    {
        input = fopen(INPUT_FILE, "r");
        fscanf(input, "%d", &n);
    }
    
    enterMatrix(matrix, n, input);

    printf("\n||A*A^{-1} - E|| = %e\n", residualNorm(matrix, inverseMatrix, n));
    
    free(matrix);
    free(inverseMatrix);
    free(threads);
    free(args);
    
    return 0;
}

long int get_time(void)
{
    struct rusage buf;
    
    getrusage(RUSAGE_SELF, &buf);
    
    return buf.ru_utime.tv_sec * 100 + buf.ru_utime.tv_usec/10000;
}

long int get_full_time(void)
{
    struct timeval buf;
    
    gettimeofday(&buf, 0);
    
    return buf.tv_sec * 100 + buf.tv_usec/10000;
}
