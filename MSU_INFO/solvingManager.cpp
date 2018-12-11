#include "solvingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std;

int returnFlag = 1;

int solveSystem(double* matrix, double* vector, double* result, int* var, maxElem *max_, int n, int rank, int threadsCount)
{
    int i, j, k, maxStrIndex, maxColIndex;
    double a, maxElem;
    int beginRow, lastRow;
    
    double eps = fmax(pow(10, -n*3), 1e-100);
    
    if (rank == 0)
    {
        for (i = 0; i < n; ++i)
            var[i] = i;
    }
    
    for (i = 0; i < n; ++i)
    {
        synchronize(threadsCount);
        
        beginRow = (n - i) * rank;
        beginRow = beginRow/threadsCount + i;
        lastRow = (n - i) * (rank + 1);
        lastRow = lastRow/threadsCount + i;
        
        max_[rank].elem = fabs(matrix[beginRow*n+i]);
        max_[rank].rowIndex = beginRow;
        max_[rank].colIndex = i;
        
        for (j = beginRow; j < lastRow; ++j)
        {
            for (k = i; k < n; ++k)
            {
                if (fabs(matrix[j*n+k]) > max_[rank].elem)
                {
                    max_[rank].elem = fabs(matrix[j*n+k]);
                    max_[rank].rowIndex = j;
                    max_[rank].colIndex = k;
                }
            }
        }

        synchronize(threadsCount);

        if (rank == 0)
        {
            maxElem = max_[0].elem;
            maxStrIndex = max_[0].rowIndex;
            maxColIndex = max_[0].colIndex;
            
            for (k = 1; k < threadsCount; ++k)
            {
                if (maxElem < max_[k].elem)
                {
                    maxElem = max_[k].elem;
                    maxStrIndex = max_[k].rowIndex;
                    maxColIndex = max_[k].colIndex;
                }
            }
            
            if (fabs(maxElem) < eps)
                returnFlag = 0; //det = 0;
            else
                returnFlag = 1;
            
            if (returnFlag)
            {
                if (maxStrIndex != i) // Swap strings (i <-> max)
                {
                    for (j = 0; j < n; ++j)
                        swap(matrix[maxStrIndex*n+j], matrix[i*n+j]);
                    
                    swap(vector[maxStrIndex], vector[i]);
                }
                
                swap(var[i], var[maxColIndex]);//swap variables
                
                if (maxColIndex != i) // Swap columns (i <-> max)
                {
                    for (j = 0; j < n; ++j)
                        swap(matrix[j*n+maxColIndex], matrix[j*n+i]);
                }
                
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
        lastRow = lastRow/threadsCount + i + 1;
        
        for (j = beginRow; j < lastRow; ++j)
        {
            a = matrix[j*n+i];
            
            for (k = i; k < n; ++k)
                matrix[j*n+k] -= matrix[i*n+k] * a;
            
            vector[j] -= vector[i] * a;
        }
    }
    
    synchronize(threadsCount);
    
    if(rank == 0)
    {
        for (i = n-1; i >= 0; --i)
        {
            a = vector[i];
            
            for (j = i+1; j < n; ++j)
                a -= matrix[i * n + j] * result[var[j]];
            
            result[var[i]] = a;
        }
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
