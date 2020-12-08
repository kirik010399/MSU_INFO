#include "solve.hpp"
#include "matrix.hpp"
#include <math.h>

using namespace std;

void solve(double *a, double *b, double *x, int *ind, max_elem *max_, int n, int thread_num, int threads_count, int *return_flag)
{
    int i, j, k, max_str_index, max_col_index;
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
        
        begin_row = (n - i) * thread_num;
        begin_row = begin_row/threads_count + i;
        last_row = (n - i) * (thread_num + 1);
        last_row = last_row/threads_count + i;
        
        max_[thread_num].elem = fabs(a[begin_row*n+i]);
        max_[thread_num].row_index = begin_row;
        max_[thread_num].col_index = i;
        
        for (j = begin_row; j < last_row; ++j)
        {
            for (k = i; k < n; ++k)
            {
                if (fabs(a[j*n+k]) > max_[thread_num].elem)
                {
                    max_[thread_num].elem = fabs(a[j*n+k]);
                    max_[thread_num].row_index = j;
                    max_[thread_num].col_index = k;
                }
            }
        }

        synchronize(threads_count);

        if (thread_num == 0)
        {
            max_elem = max_[0].elem;
            max_str_index = max_[0].row_index;
            max_col_index = max_[0].col_index;
            
            for (k = 1; k < threads_count; ++k)
            {
                if (max_elem < max_[k].elem)
                {
                    max_elem = max_[k].elem;
                    max_str_index = max_[k].row_index;
                    max_col_index = max_[k].col_index;
                }
            }
            
            if (fabs(max_elem) < eps)
                *return_flag = 0; //det = 0;
            else
                *return_flag = 1;
            
            if (*return_flag)
            {
                if (max_str_index != i) // Swap strings (i <-> max)
                {
                    for (j = 0; j < n; ++j)
                        swap(a[max_str_index*n+j], a[i*n+j]);
                    
                    swap(b[max_str_index], b[i]);
                }
                
                swap(ind[i], ind[max_col_index]);//swap variables
                
                if (max_col_index != i) // Swap columns (i <-> max)
                {
                    for (j = 0; j < n; ++j)
                        swap(a[j*n+max_col_index], a[j*n+i]);
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
        
        begin_row = n * thread_num /threads_count;
        last_row = n * (thread_num + 1) /threads_count;
        
        for(j = begin_row; j < last_row; ++j)
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
    
    synchronize(threads_count);
    
    if(thread_num == 0)
    {
        for (i = 0; i < n; ++i)
            x[ind[i]] = b[i]/a[i*n+i];
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
