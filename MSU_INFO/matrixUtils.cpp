#include "matrixUtils.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

double func(int i, int j, int n)
{
    double h = 1.0/(n+1);
    
    if (i == j)
        return 2.0/(h*h);
    else if (i == j+1 || i == j-1)
        return -1.0/(h*h);
    else
        return 0;
}

void enterData(double* matrix, double *vector, int n, FILE* fin)
{
    for (int i = 0; i < n; ++i)
    {
        vector[i] = 0;
        
        for (int j = 0; j < n; ++j)
        {
            matrix[i*n+j] = func(i, j, n);
            
            if (j % 2 == 0)
                vector[i] += matrix[i*n+j];
        }
    }
}

void printResult(double* result, int n, int m)
{
    int i;
    int min_ = min(n,m);
    
    for (i = 0; i < min_; ++i)
        cout<<result[i]<<' ';
    
    cout<<endl;
}

double residualNorm(double* matrix, double* vector, double* result, int n)
{
    int i, j;
    double res = 0;
    double a;
    
    for (i = 0; i < n; ++i)
    {
        a = 0.0;
        
        for (j = 0; j < n; ++j)
            a += matrix[i*n+j] * result[j];
        
        a -= vector[i];
        
        res += a*a;
    }
    
    return sqrt(res);
}

double errorFunction(double *result, int n)
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
