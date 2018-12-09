#include "solvingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std;

int returnFlag = 1;

int solveSystem(double* matrix, double* vector, double* result, int n, int rank, int threadsCount)
{
    int i, j, k, maxElemIndex;
    double maxElem;

    int beginRow, lastRow;
    
    double eps = fmax(pow(10, -n*3), 1e-100);
    
    for (j = 0; j < n; ++j)
    {
        synchronize(threadsCount);
        
        if (rank == 0)
        {
            maxElem = matrix[j*n+j];
            maxElemIndex = j;
            
            for (i = j+1; i < n; ++i)
            {
                if (fabs(matrix[i*n+j]) > fabs(maxElem))
                {
                    maxElem = matrix[i*n+j];
                    maxElemIndex = i;
                }
            }
            
            if (fabs(maxElem) < eps)
                returnFlag = 0; //det = 0;
            else
                returnFlag = 1;
            
            if (returnFlag)
            {
                if (maxElemIndex != j)
                {
                    for (i = j; i < n; ++i)
                        swap(matrix[maxElemIndex*n+i], matrix[j*n+i]);
                    
                    swap(vector[maxElemIndex], vector[j]);
                }
            }
        }
        
        synchronize(threadsCount);
        
        if (!returnFlag)
            return -1;
        
        beginRow = n * rank/threadsCount;
        lastRow = n * (rank + 1)/threadsCount;
        
        for(i = beginRow; i < lastRow; ++i)
        {
            if (i != j && fabs(matrix[i*n+j]) > eps)
            {
                maxElem = matrix[i*n+j]/matrix[j*n+j];
                
                for(k = j; k < n; ++k)
                    matrix[i*n+k] -= maxElem*matrix[j*n+k];
                
                vector[i] -= maxElem*vector[j];
            }
        }
    }
    
    synchronize(threadsCount);
    
    if(rank == 0)
    {
        for (i = 0; i < n; ++i)
            result[i] = vector[i]/matrix[i*n+i];
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
