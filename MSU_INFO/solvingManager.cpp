#include "solvingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std;

int returnFlag = 1;

int solveSystem(double* matrix, double* vector, double* result, int n, int rank, int threadsCount)
{
    int i, j, k, maxElemIndex;
    double a, maxElem;

    int beginRow, lastRow;
    
    double eps = fmax(pow(10, -n*3), 1e-100);
    
    for (i = 0; i < n; i++)
    {
        synchronize(threadsCount);

        if (rank == 0)
        {
            maxElem = fabs(matrix[i*n+i]);
            maxElemIndex = i;
            
            for (j = i + 1; j < n; ++j)
            {
                if (maxElem < fabs(matrix[j*n+i]))
                {
                    maxElem = fabs(matrix[j*n+i]);
                    maxElemIndex = j;
                }
            }
            
            if (maxElemIndex != i)
            {
                for (j = i; j < n; ++j)
                    swap (matrix[i*n+j], matrix[maxElemIndex*n+j]);
                
                swap (vector[i], vector[maxElemIndex]);
            }
            
            if (maxElem < eps)
                returnFlag = 0; //det = 0;
            else
                returnFlag = 1;
            
            if (returnFlag)
            {
                a = 1.0/matrix[i*n+i];
                
                for (j = i; j < n; ++j)
                    matrix[i*n+j] *= a;
                
                vector[i] *= a;
            }
        }
        
        synchronize(threadsCount);
        
        if (!returnFlag)
            return -1;
        
        beginRow = (n - i - 1) * rank;
        beginRow = beginRow/threadsCount + i + 1;
        lastRow = (n - i - 1) * (rank + 1);
        lastRow = lastRow/threadsCount + i + 1;//равномерное распределение междлу i+1 до n
        
        for (j = beginRow; j < lastRow; ++j)
        {
            a = matrix[j*n+i];
            
            for (k = i; k < n; ++k)
                matrix[j*n+k] -= matrix[i*n+k] * a;
            
            vector[j] -= vector[i] * a;
        }
    }
    
    synchronize(threadsCount);
    
    for (i = n-1; i >= 0; --i)
    {
        a = vector[i];
        
        for (j = i+1; j < n; ++j)
            a -= matrix[i * n + j] * result[j];
        
        result[i] = a;
    }
    
    return 0;
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
