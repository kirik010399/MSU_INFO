#include "invertingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std;

int returnFlag = 1;

int invertMatrix(double* a, double* x, int n, int rank, int threadsCount)
{
    int i, j, k;
    double tmp1, tmp2;
    double r;
    double cosPhi = 0, sinPhi = 0;

    int beginCol, lastCol;
    
    double eps = fmax(pow(10, -n*3), 1e-100);
    
    if (rank == 0)
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                if (i == j)
                    x[i*n+j] = 1;
                else
                    x[i*n+j] = 0;
            }
        }
    }
    
    for (i = 0; i < n-1; i++)
    {
        for (j = i + 1; j < n; ++j)
        {
            synchronize(threadsCount);

            if (rank == 0)
            {
                tmp1 = a[i*n+i];
                tmp2 = a[j*n+i];
                
                r = sqrt(tmp1*tmp1+tmp2*tmp2);
                
                cout<<r<<endl;
                
                if (r < eps)
                    returnFlag = 0; //det = 0;
                else
                    returnFlag = 1;
                
                if (returnFlag)
                {
                    cosPhi = tmp1 / r;
                    sinPhi = -tmp2 / r;
                    
                    a[i * n + i] = r;
                    a[j * n + i] = 0.0;
                }
            }
            
            synchronize(threadsCount);
            
            if (!returnFlag)
                return -1;
            
            beginCol = (n - i - 1) * rank;
            beginCol = beginCol/threadsCount + i + 1;
            lastCol = (n - i - 1) * (rank + 1);
            lastCol = lastCol/threadsCount + i + 1;//равномерное распределение междлу i+1 до n
            
            for (k = beginCol; k < lastCol; ++k)
            {
                tmp1 = a[i * n + k];
                tmp2 = a[j * n + k];
                
                a[i * n + k] = tmp1 * cosPhi - tmp2 * sinPhi;
                a[j * n + k] = tmp1 * sinPhi + tmp2 * cosPhi;
            }
            
            synchronize(threadsCount);

            beginCol = n * rank/threadsCount;
            lastCol = n * (rank + 1)/threadsCount;//равномерное распределение междлу 0 до n
            
            for (k = beginCol; k < lastCol; ++k)
            {
                tmp1 = x[i * n + k];
                tmp2 = x[j * n + k];
                
                x[i * n + k] = tmp1 * cosPhi - tmp2 * sinPhi;
                x[j * n + k] = tmp1 * sinPhi + tmp2 * cosPhi;
            }
        }
    }
    
    synchronize(threadsCount);
   
    beginCol = n * rank/threadsCount;
    lastCol = n * (rank + 1)/threadsCount;//равномерное распределение междлу 0 до n
    
    for (k = beginCol; k < lastCol; ++k)
    {
        for (i = n - 1; i >= 0; --i)
        {
            tmp1 = x[i * n + k];
            
            for (j = i + 1; j < n; ++j)
                tmp1 -= a[i * n + j] * x[j * n + k];
            
            x[i * n + k] = tmp1 / a[i * n + i];
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
