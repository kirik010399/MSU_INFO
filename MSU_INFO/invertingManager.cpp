#include "invertingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std;

int continueFlag = 1;
int returnFlag = 1;
double cosPhi = 0, sinPhi = 0;

int invertMatrix(double* matrix, double* inverseMatrix, int n, int rank, int threadsCount)
{
    int i, j, k;
    double x, y;
    double r = 0, matrix_ik, matrix_jk;
    double a;

    int beginCol, lastCol;
    
    double eps = fmax(pow(10, -n*3), 1e-100);
    
    if (rank == 0)
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                if (i == j)
                    inverseMatrix[i*n+j] = 1;
                else
                    inverseMatrix[i*n+j] = 0;
            }
        }
    }
    
    for (i = 0; i < n-1; ++i)
    {
        for (j = i + 1; j < n; ++j)
        {
            synchronize(threadsCount);

            if (rank == 0)
            {
                x = matrix[i*n+i];
                y = matrix[j*n+i];
                
                if (fabs(y) < eps)
                    continueFlag = 0;
                else
                    continueFlag = 1;

                if (continueFlag)
                {
                    r = sqrt(x*x+y*y);
                    
                    if (r < eps)
                        returnFlag = 0;
                    else
                        returnFlag = 1;
                    
                    if (returnFlag)
                    {
                        cosPhi = x/r;
                        sinPhi = -y/r;
                    }
                }
            }
            
            synchronize(threadsCount);
            
            if(!continueFlag)
            {
                if (!returnFlag)
                    return -1;
                else
                    continue;
            }
            
            beginCol = (n - i) * rank;
            beginCol = beginCol/threadsCount + i;
            lastCol = (n - i) * (rank + 1);
            lastCol = lastCol/threadsCount + i;//равномерное распределение междлу i до n
            
            for (k = beginCol; k < lastCol; ++k)
            {
                matrix_ik = matrix[i*n+k];
                matrix_jk = matrix[j*n+k];
                
                matrix[i*n+k] = matrix_ik * cosPhi - matrix_jk * sinPhi;
                matrix[j*n+k] = matrix_ik * sinPhi + matrix_jk * cosPhi;
            }
            
            synchronize(threadsCount);

            beginCol = n * rank/threadsCount;
            lastCol = n * (rank + 1)/threadsCount;//равномерное распределение междлу 0 до n
            
            for (k = beginCol; k < lastCol; ++k)
            {
                matrix_ik = inverseMatrix[i*n+k];
                matrix_jk = inverseMatrix[j*n+k];
                
                inverseMatrix[i*n+k] = matrix_ik * cosPhi - matrix_jk * sinPhi;
                inverseMatrix[j*n+k] = matrix_ik * sinPhi + matrix_jk * cosPhi;//*Tij
            }
        }
    }
    
    synchronize(threadsCount);
   
    beginCol = n * rank/threadsCount;
    lastCol = n * (rank + 1)/threadsCount;//равномерное распределение междлу 0 до n
    
    for (k = beginCol; k < lastCol; ++k)
    {
        for (i = n-1; i >= 0; --i)
        {
            if (fabs(matrix[i*n+i]) < eps)
                return -1;
            
            a = inverseMatrix[i*n+k];
            
            for (j = i + 1; j < n; ++j)
                a -= matrix[i*n+j] * inverseMatrix[j*n+k];
            
            inverseMatrix[i*n+k] = a / matrix[i*n+i];
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
