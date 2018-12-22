#include "matrixUtils.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

double func(int i, int j, int n)
{
    return n - fmax(i,j);
}

int enterData(double* matrix, double *vector, int n, FILE* fin)
{
    int i;
    int j;
    
    if (fin)
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                if (fscanf(fin, "%lf", &matrix[i*n+j]) != 1)
                    return -1;
            }
            
            if (fscanf(fin, "%lf", &vector[i]) != 1)
                return -1;
        }
    }
    else
    {
        for (i = 0; i < n; ++i)
        {
            vector[i] = 0;
            
            for (j = 0; j < n; ++j)
            {
                matrix[i*n+j] = func(i, j, n);
                
                if (j % 2 == 0)
                    vector[i] += matrix[i*n+j];
            }
        }
    }
    
    return 0;
}

void printResult(double* result, int n, int m)
{
    int i;
    int min_ = fmin(n,m);
    
    for (i = 0; i < min_; ++i)
        printf("%f ", result[i]);
    
    printf("\n");
}

double residualNorm(double* matrix, double* vector, double* result, int n, int rank, int threadsCount)
{
    int i, j;
    double res = 0;
    double val;
    int beginRow, lastRow;
    
    beginRow = n * rank;
    beginRow = beginRow/threadsCount; 
    lastRow = n * (rank + 1);
    lastRow = lastRow/threadsCount;
        
    for (i = beginRow; i < lastRow; ++i)
    {
        val = 0.0;
        
        for (j = 0; j < n; ++j)
            val += matrix[i*n+j] * result[j];
        
        val -= vector[i];
        res += val*val;
    }
    
    return res;
}

double errorNorm(double *result, int n)
{
    double error = 0;
    int i;
    
    for (i = 0; i < n; ++i)
    {
        if (i % 2)
            error += result[i]*result[i];
        else
            error += (result[i]-1)*(result[i]-1);
    }
    
    return sqrt(error);
}
