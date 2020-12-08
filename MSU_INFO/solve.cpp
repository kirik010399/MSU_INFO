#include "solve.hpp"
#include "matrix.hpp"
#include <math.h>

using namespace std;

void solve(double *a, double *b, double *x, int n, int thread_num, int threads_count, int *continue_flag, int *return_flag)
{
    int i, j, k;
    double value;
    double x_, y_, r;
    double cos_phi, sin_phi;
    double a_ik, a_jk;
    double b_i, b_j;
    double eps = 1e-30;
    int begin_row, last_row, thread_row;

    for (i = 0; i < n-1; ++i)
    {
        synchronize(threads_count);

        begin_row = (n - i) * thread_num;
        begin_row = begin_row/threads_count + i;
        last_row = (n - i) * (thread_num + 1);
        last_row = last_row/threads_count + i;
        
        for (j = begin_row+1; j < last_row; ++j)
        {
            x_ = a[begin_row*n+i];
            y_ = a[j*n+i];

            r = sqrt(x_*x_+y_*y_);
            
            if (r < eps)
                continue;
            
            cos_phi = x_/r;
            sin_phi = -y_/r;
            
            for (k = i; k < n; ++k)
            {
                a_ik = a[begin_row*n+k];
                a_jk = a[j*n+k];
                
                a[begin_row*n+k] = a_ik * cos_phi - a_jk * sin_phi;
                a[j*n+k] = a_ik * sin_phi + a_jk * cos_phi;
            }
            
            b_i = b[begin_row];
            b_j = b[j];
            
            b[begin_row] = b_i * cos_phi - b_j * sin_phi;
            b[j] = b_i * sin_phi + b_j * cos_phi;
        }
        
        synchronize(threads_count);

        if (!*return_flag)
            return;

        if (thread_num == 0)
        {
            for (thread_row = 1; thread_row < threads_count; ++thread_row)
            {
                j = (n - i) * thread_row;
                j = j/threads_count + i;
                
                if (i == j)
                    continue;
                
                x_ = a[i*n+i];
                y_ = a[j*n+i];

                r = sqrt(x_*x_+y_*y_);
                
                if (r < eps)
                {
                    *return_flag = 0;
                }
                else
                {
                    cos_phi = x_/r;
                    sin_phi = -y_/r;
                    
                    for (k = i; k < n; ++k)
                    {
                        a_ik = a[i*n+k];
                        a_jk = a[j*n+k];
                        
                        a[i*n+k] = a_ik * cos_phi - a_jk * sin_phi;
                        a[j*n+k] = a_ik * sin_phi + a_jk * cos_phi;
                    }
                    
                    b_i = b[i];
                    b_j = b[j];
                    
                    b[i] = b_i * cos_phi - b_j * sin_phi;
                    b[j] = b_i * sin_phi + b_j * cos_phi;
                }
            }
        }
        
        synchronize(threads_count);
        
        if (!*return_flag)
            return;
    }
    
    synchronize(threads_count);
    
    if (thread_num == 0)
    {
        for (i = n-1; i >= 0; --i)
        {
            value = b[i];
            
            for (j = i+1; j < n; ++j)
                value -= a[i*n+j] * x[j];
            
            if (fabs(a[i*n+i]) < eps)
                *return_flag = 0;
            else
                x[i] = value/a[i*n+i];
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
