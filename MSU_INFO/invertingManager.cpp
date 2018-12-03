//
//  invertingManager.cpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 20.09.2018.
//  Copyright © 2018 Кирилл Мащенко. All rights reserved.
//

#include "invertingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std;

int continueFlag = 1;
int returnFlag = 1;

int invertMatrix(double* matrix, double* inverseMatrix, double *d, int n, int rank, int threadsCount)
{
    int i, j, k;
    int beginCol;
    int lastCol;
    double a, b = 0;
    
    double eps = fmax(pow(10, -n*3), 1e-100);
    
    if (rank == 0)
    {
        for (i = 0; i < n; ++i)
        {
            d[i] = 0;
            
            for (j = 0; j < n; ++j)
            {
                if (i == j)
                    inverseMatrix[i*n+j] = 1;
                else
                    inverseMatrix[i*n+j] = 0;
            }
        }
    }
    
    for (i = 0; i < n; i++)
    {
        synchronize(threadsCount);

        if (rank == 0)
        {
            a = 0.0;
            for (j = i + 1; j < n; j++)
                a += matrix[j*n+i] * matrix[j*n+i];//(12)
            
            b = sqrt(a + matrix[i*n+i] * matrix[i*n+i]);//(13)
            
            if (b < eps)
                returnFlag = 0; //det = 0;
            else
                returnFlag = 1;
            
            if (returnFlag)
            {
                d[i] = matrix[i*n+i] - b;
                
                for (j = i+1; j < n; ++j)
                    d[j] = matrix[j*n+i]; //(14)
                
                a = sqrt(d[i] * d[i] + a);//(15)
                
                if (a < eps)
                {
                    continueFlag = 0;
                }
                else
                {
                    continueFlag = 1;
                    
                    for (j = i; j < n; ++j)
                        d[j] /= a; //(16)
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
        
        if (returnFlag && continueFlag)
        {
            beginCol = (n - i - 1) * rank;
            beginCol = beginCol/threadsCount + i + 1;
            lastCol = (n - i - 1) * (rank + 1);
            lastCol = lastCol/threadsCount + i + 1;
            
            for (k = beginCol; k < lastCol; k++)
            {
                a = 0.0;
                for (j = i; j < n; ++j)
                    a += d[j] * matrix[j*n+k];
                
                a *= 2.0;//from formula
                for (j = i; j < n; ++j)
                    matrix[j*n+k] -= a * d[j];
            }
        }
        
        synchronize(threadsCount);
        
        if (returnFlag && continueFlag)
        {
            beginCol = n * rank/threadsCount;
            lastCol = n * (rank + 1)/threadsCount;
            
            for (k = beginCol; k < lastCol; k++)
            {
                a = 0.0;
                for (j = i; j < n; ++j)
                    a += d[j] * inverseMatrix[j*n+k];
                
                a *= 2.0;//from formula
                for (j = i; j < n; ++j)
                    inverseMatrix[j*n+k] -= a * d[j];
                
            }
        }
        
        synchronize(threadsCount);
        
        if (rank == 0 && returnFlag && continueFlag)
            matrix[i*n+i] = b;//on diag R
    }
    
    synchronize(threadsCount);
    
    //R in up triangle, Q in down triangle and in d
    
    beginCol = n * rank/threadsCount;
    lastCol = n * (rank + 1)/threadsCount;
    
    for (k = beginCol; k < lastCol; k++)
    {
        for (i = n - 1; i >= 0; --i)
        {
            a = inverseMatrix[i*n+k];
            
            for (j = i + 1; j < n; ++j)
                a -= matrix[i*n+j] * inverseMatrix[j*n+k];
            
            inverseMatrix[i*n+k] = a/matrix[i*n+i];
        }
    }//Reverse Gauss
    
    if (!returnFlag)
    {
        return -1;
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
