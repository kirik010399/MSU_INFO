#include "solvingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std;

#define eps 1e-18

int solve(double* a, double* b, double* x, int* index, maxelem* max_, int* retflag, int n, int number, int count)
{
    int i, j, k, maxstr, maxcol, begin, last;
    double value;
    
    if (number == 0)
    {
        for (i = 0; i < n; ++i)
            index[i] = i;
    }
    
    for (i = 0; i < n; i++)
    {
        synchronize(count);
       
        begin = (n - i) * number;
        begin = begin/count + i;
        last = (n - i) * (number + 1);
        last = last/count + i;
        
        max_[number].value = fabs(a[begin*n+i]);
        max_[number].x = begin;
        max_[number].y = i;
        
        for (j = begin; j < last; ++j)
        {
            for (k = i; k < n; ++k)
            {
                if (fabs(a[j*n+k]) > max_[number].value)
                {
                    max_[number].value = fabs(a[j*n+k]);
                    max_[number].x = j;
                    max_[number].y = k;
                }
            }
        }
        
        synchronize(count);
        
        if (number == 0)
        {
            value = max_[0].value;
            maxstr = max_[0].x;
            maxcol = max_[0].y;
            
            for (k = 1; k < count; ++k)
            {
                if (value < max_[k].value)
                {
                    value = max_[k].value;
                    maxstr = max_[k].x;
                    maxcol = max_[k].y;
                }
            }
            
            if (fabs(value) < eps)
                *retflag = 0;
            else
                *retflag = 1;
            
            if (*retflag)
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
        
        if (!(*retflag))
            return -1;
        
        begin = n * number/count;
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
