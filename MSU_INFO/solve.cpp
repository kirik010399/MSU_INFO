#include "solve.hpp"
#include "matrix.hpp"
#include <math.h>

using namespace std;

void solve(double *a, double *b, double *x, int *ind, int n, int thread_num, int threads_count, int *return_flag)
{
    int i, j, k, max_index;
    double value, max_elem;
    int begin_row, last_row;
    
    double eps = 1e-30;
    
    if (thread_num == 0)
    {
        for (i = 0; i < n; ++i)
            ind[i] = i;
    }
    
    for (i = 0; i < n; ++i)
    {
        synchronize(threads_count);

        if (thread_num == 0)
        {
            max_elem = fabs(a[i*n+i]);
            max_index = i;
            
            for (j = i+1; j < n; ++j)
            {
                if (max_elem < fabs(a[i*n+j]))
                {
                    max_elem = fabs(a[i*n+j]);
                    max_index = j;
                }
            }
            
            if (fabs(max_elem) < eps)
                *return_flag = 0; //det = 0;
            else
                *return_flag = 1;
            
            if (*return_flag)
            {
                if (max_index != i)
                {
                    for (j = 0; j < n; ++j)
                        swap(a[j*n+max_index], a[j*n+i]);
                    
                    swap(ind[i], ind[max_index]);
                }
                
                value = 1.0/a[i*n+i];
                
                for (j = i; j < n; ++j)
                    a[i*n+j] *= value;
                
                b[i] *= value;
            }
        }
        
        synchronize(threads_count);
        
        if (!*return_flag)
            return;
        
        begin_row = (n - i - 1) * thread_num;
        begin_row = begin_row/threads_count + i + 1;
        last_row = (n - i - 1) * (thread_num + 1);
        last_row = last_row/threads_count + i + 1;
        
        for (j = begin_row; j < last_row; ++j)
        {
            value = a[j*n+i];
            
            for (k = i; k < n; ++k)
                a[j*n+k] -= a[i*n+k] * value;
            
            b[j] -= b[i] * value;
        }
    }
    
    synchronize(threads_count);
    
    if(thread_num == 0)
    {
        for (i = n-1; i >= 0; --i)
        {
            value = b[i];
            
            for (j = i+1; j < n; ++j)
                value -= a[i*n+j] * x[ind[j]];
            
            x[ind[i]] = value;
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
