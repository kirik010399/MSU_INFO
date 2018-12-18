#include "invertingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std;

int returnFlag = 1;

int invertMatrix(double* matrix, double* inverseMatrix, int n, int rank, int threadsCount)
{
    int i, j, k;
    double x, y;
    double r = 0, matrix_ik, matrix_jk;
    double a;
    
    int beginCol, lastCol;
    int beginRow, lastRow;
    
    double eps = fmax(pow(10, -n*3), 1e-100);
    
    double cosPhi = 1, sinPhi = 0;
    
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
        synchronize(threadsCount);
        
        beginRow = (n - i - 1) * rank;
        beginRow = beginRow/threadsCount + i + 1;
        lastRow = (n - i - 1) * (rank + 1);
        lastRow = lastRow/threadsCount + i + 1;
        
        for (j = beginRow + 1; j < lastRow; ++j)
        {
            x = matrix[beginRow*n+i];
            y = matrix[j*n+i];
            
            r = sqrt(x*x+y*y);
        
            cosPhi = x/r;
            sinPhi = -y/r;
            
            for (k = i; k < n; ++k)
            {
                matrix_ik = matrix[beginRow*n+k];
                matrix_jk = matrix[j*n+k];
                
                matrix[beginRow*n+k] = matrix_ik * cosPhi - matrix_jk * sinPhi;
                matrix[j*n+k] = matrix_ik * sinPhi + matrix_jk * cosPhi;
            }
            
            for (k = 0; k < n; ++k)
            {
                matrix_ik = inverseMatrix[beginRow*n+k];
                matrix_jk = inverseMatrix[j*n+k];
                
                inverseMatrix[beginRow*n+k] = matrix_ik * cosPhi - matrix_jk * sinPhi;
                inverseMatrix[j*n+k] = matrix_ik * sinPhi + matrix_jk * cosPhi;//*Tij
            }
        }
        
        synchronize(threadsCount);

        if (rank == 0)
        {
            for (j = 0; j < threadsCount; ++j)
            {
                beginRow = (n - i - 1) * rank;
                beginRow = beginRow/threadsCount + i + 1;
            
                x = matrix[i*n+i];
                y = matrix[beginRow*n+i];
                
                r = sqrt(x*x+y*y);
                
                cosPhi = x/r;
                sinPhi = -y/r;
                
                for (k = i; k < n; ++k)
                {
                    matrix_ik = matrix[i*n+k];
                    matrix_jk = matrix[beginRow*n+k];
                    
                    matrix[i*n+k] = matrix_ik * cosPhi - matrix_jk * sinPhi;
                    matrix[beginRow*n+k] = matrix_ik * sinPhi + matrix_jk * cosPhi;
                }
                
                for (k = 0; k < n; ++k)
                {
                    matrix_ik = inverseMatrix[i*n+k];
                    matrix_jk = inverseMatrix[beginRow*n+k];
                    
                    inverseMatrix[i*n+k] = matrix_ik * cosPhi - matrix_jk * sinPhi;
                    inverseMatrix[beginRow*n+k] = matrix_ik * sinPhi + matrix_jk * cosPhi;//*Tij
                }
            }
        }
    }
    
    synchronize(threadsCount);
   
    beginCol = n * rank/threadsCount;
    lastCol = n * (rank + 1)/threadsCount;
    
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
