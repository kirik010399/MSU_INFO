#include "solvingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std;

int solve(double* a, double* b, double* x, int* index, int* funcFlag, int n, int number, int count)
{
    int i, j, k;
    double value;
    int maxstr, maxcol;
    int begin, last;
    
    double eps = fmax(pow(10, -n*3), 1e-100);
    
    if (number == 0)
    {
        for (i = 0; i < n; ++i)
            index[i] = i;
    }
    
    for (i = 0; i < n; i++)
    {
        synchronize(count);

        if (number == 0)
        {
            value = fabs(a[i*n+i]); maxstr = i; maxcol = i;
            
            for (j = i; j < n; ++j)
            {
                for (k = i; k < n; ++k)
                {
                    if (fabs(a[j*n+k]) > value)
                    {
                        value = fabs(a[j*n+k]); maxstr = j; maxcol = k;
                    }
                }
            }
            
            if (fabs(value) < eps)
                *funcFlag = 0;
            else
                *funcFlag = 1;
            
            if (*funcFlag)
            {
                if (maxstr != i)
                {
                    for (j = 0; j < n; ++j)
                        swap(a[maxstr*n+j], a[i*n+j]);
                    
                    swap(b[maxstr], b[i]);
                }
                
                swap(index[i], index[maxcol]);
                
                if (maxcol != i)
                {
                    for (j = 0; j < n; ++j)
                        swap(a[j*n+maxcol], a[j*n+i]);
                }
            }
        }
        
        synchronize(count);
        
        if (!(*funcFlag))
            return -1;
        
        begin = n * number/count ;
        last = n * (number + 1)/count;
        
        for (j = begin; j < last; ++j)
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
    
    synchronize(count);
    
    if(number == 0)
    {
        for (i = 0; i < n; ++i)
            x[index[i]] = b[i]/a[i*n+i];
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
