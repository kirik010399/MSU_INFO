#include "solvingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std;

int returnFlag = 1;

int solveSystem(double* a, double* b, double* x, int* var, int n, int rank, int threadsCount)
{
    int i, j, k;
    double value;
    int maxStrInd, maxColInd;

    int beginRow, lastRow;
    
    double eps = fmax(pow(10, -n*3), 1e-100);
    
    if (rank == 0)
    {
        for (i = 0; i < n; ++i)
            var[i] = i;
    }
    
    for (i = 0; i < n; i++)
    {
        synchronize(threadsCount);

        if (rank == 0)
        {
            value = fabs(a[i*n+i]);
            maxStrInd = i;
            maxColInd = i;
            
            for (j = i; j < n; ++j)
            {
                for (k = i; k < n; ++k)
                {
                    if (fabs(a[j*n+k]) > value)// Search for max in a
                    {
                        value = fabs(a[j*n+k]);
                        maxStrInd = j;
                        maxColInd = k;
                    }
                }
            }
            
            if (fabs(value) < eps)
                returnFlag = 0; //det = 0;
            else
                returnFlag = 1;
            
            if (returnFlag)
            {
                if (maxStrInd != i) // Swap strings (i <-> max)
                {
                    for (j = 0; j < n; ++j)
                        swap(a[maxStrInd*n+j], a[i*n+j]);
                    
                    swap(b[maxStrInd], b[i]);
                }
                
                swap(var[i], var[maxColInd]);//swap variables
                
                if (maxColInd != i) // Swap columns (i <-> max)
                {
                    for (j = 0; j < n; ++j)
                        swap(a[j*n+maxColInd], a[j*n+i]);
                }
            }
        }
        
        synchronize(threadsCount);
        
        if (!returnFlag)
            return -1;
        
        beginRow = n * rank/threadsCount ;
        lastRow = n * (rank + 1)/threadsCount;
        
        for (j = beginRow; j < lastRow; ++j)
        {
            if (j != i)
            {
                value = a[j*n+i]/a[i*n+i];
                
                for(k = i; k < n; ++k)
                    a[j*n+k] -= value*a[i*n+k];
                
                b[j] -= value*b[i];
            }
        }
    }
    
    synchronize(threadsCount);
    
    if(rank == 0)
    {
        for (i = 0; i < n; ++i)
            x[var[i]] = b[i]/a[i*n+i];
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
