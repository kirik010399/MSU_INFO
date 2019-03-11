#include "solvingFunctions.h"
#include <math.h>


void solveSystem(double* matrix, double* vector, double* result, int *var, int n, int *flag, float eps, int debug, int rank, int threadsCount){
    int i, j, k, maxColIndex, ii, jj;
    double a, maxElem;
    int tempVar;
    double temp;
    
    int beginRow, lastRow;
    
    if (rank == 0){
        for (i = 0; i < n; ++i)
            var[i] = i;
    }
    
    for (i = 0; i < n; ++i)
    {
        synchronize(threadsCount);

        if (rank == 0){
            if (debug == 1){
                printf("\n");
                printf("%d\n", i);

                for (ii = 0; ii < n; ++ii){
                    for (jj = 0; jj < n; ++jj){
                        printf("%f ", matrix[ii*n+jj]);
                    }
                    printf("\n");
                }
            }
            
            maxElem = fabs(matrix[i*n+i]);
            maxColIndex = i;
            
            for (j = i; j < n; ++j){
                if (fabs(matrix[i*n+j]) > maxElem){// Search for max in string
                    maxElem = fabs(matrix[i*n+j]);
                    maxColIndex = j;
                }
            }
            
            if (fabs(maxElem) < eps)
                *flag = -1;
            else
                *flag = 0;
            
            if (*flag != -1){
                if (maxColIndex != i){ // Swap columns (i <-> max)
                    tempVar = var[i];
                    var[i] = var[maxColIndex];
                    var[maxColIndex] = tempVar;
                    
                    for (j = 0; j < n; ++j){
                        temp = matrix[j*n+i];
                        matrix[j*n+i] = matrix[j*n+maxColIndex];
                        matrix[j*n+maxColIndex] = temp;
                    }
                }
                
                a = 1.0/matrix[i*n+i];
                
                for (j = i; j < n; ++j)
                    matrix[i*n+j] *= a;
                
                vector[i] *= a;
            }
        }
        
        synchronize(threadsCount);

        if (*flag == -1)
            return;
        
        beginRow = (n - i - 1) * rank;
        beginRow = beginRow/threadsCount + i + 1;
        lastRow = (n - i - 1) * (rank + 1);
        lastRow = lastRow/threadsCount + i + 1;
        
        for (j = beginRow; j < lastRow; ++j){
            a = matrix[j*n+i];
            
            for (k = i; k < n; ++k)
                matrix[j*n+k] -= matrix[i*n+k] * a;
            
            vector[j] -= vector[i] * a;
        }
    }
    
    synchronize(threadsCount);

    if(rank == 0)
    {
        for (i = n-1; i >= 0; --i){
            a = vector[i];
            
            for (j = i+1; j < n; ++j)
                a -= matrix[i * n + j] * result[var[j]];
            
            result[var[i]] = a;
        }
    }
}

void synchronize(int total_threads)
{
    static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
    static pthread_cond_t condvar_in = PTHREAD_COND_INITIALIZER;
    static pthread_cond_t condvar_out = PTHREAD_COND_INITIALIZER;
    static int threads_in = 0;
    static int threads_out = 0;
    
    pthread_mutex_lock(&mutex);
    
    threads_in++;
    if (threads_in >= total_threads)
    {
        threads_out = 0;
        pthread_cond_broadcast(&condvar_in);
    } else
        while (threads_in < total_threads)
            pthread_cond_wait(&condvar_in,&mutex);
    
    threads_out++;
    if (threads_out >= total_threads)
    {
        threads_in = 0;
        pthread_cond_broadcast(&condvar_out);
    } else
        while (threads_out < total_threads)
            pthread_cond_wait(&condvar_out,&mutex);
    
    pthread_mutex_unlock(&mutex);
}
