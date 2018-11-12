#include "calculatingManager.hpp"
#include <math.h>
#include <iostream>
//#define eps 1e-100

using namespace std;

void calculateValues(double* matrix, double* vector, double left, double right, double eps, int n)
{
    Otr(matrix, n);
    
    values(matrix, n, vector, left, right, eps);
}

void values(double *matrix, int n, double *vector, double left, double right, double eps)
{
    static int k = 0;
    int c, j;
    
    c = n_(matrix, n, right) - n_(matrix, n, left);
        
    if (right - left > eps && c != 0)
    {
        values(matrix, n, vector, left, (left+right)/2, eps);
        values(matrix, n, vector, (left+right)/2, right, eps);
    }
    else if (c != 0)
    {
        for (j = 0; j < c; ++j)
            vector[k + j] = (left+right)/2;
        
        k += c;
    }//95
}


void Otr(double* matrix, int n)
{
    int i, j, k;
    double a, b;
    
    for (i = 0; i < n-2; ++i)
    {
        a = 0.0;
        
        for (j = i+2; j < n; ++j)
            a += matrix[j*n+i]*matrix[j*n+i];
        
        b = sqrt(matrix[(i+1)*n+i]*matrix[(i+1)*n+i] + a);
        
        if (b < 1e-100)
        {
            matrix[(i+1)*n+i] = 0.0;
            matrix[(i+2)*n+i] = 0.0;
            
            continue;
        }
        
        if (a < 1e-100)
        {
            matrix[(i+2)*n+i] = 0.0;
            continue;
        }
        
        matrix[(i+1)*n+i] -= b;
        
        a = 1.0/sqrt(matrix[(i+1)*n+i] * matrix[(i+1)*n+i] + a);
        
        for (j = i+1; j < n; ++j)
            matrix[j*n+i] *= a;
        
        for (j = i+1; j < n; ++j)
        {
            a = 0.0;
            
            for (k = i+1; k < n; k++)
                a += matrix[j*n+k] * matrix[k*n+i];
            
            matrix[i*n+j] = a;
        }
        
        a = 0.0;
        for (j = i+1; j < n; ++j)
            a += matrix[i*n+j] * matrix[j*n+i];
        
        a *= 2.0;
        for (j = i+1; j < n; ++j)
            matrix[i*n+j] = 2.0 * matrix[i*n+j] - a * matrix[j*n+i];
        
        for (j = i+1; j < n; ++j)
        {
            for (k = i+1; k < n; ++k)
            {
                matrix[j*n+k] -= matrix[i*n+j] * matrix[k*n+i] + matrix[i*n+k] * matrix[j*n+i];
            }
        }
        
        matrix[(i+1)*n+i] = b;
        matrix[i*n + i+1] = b;
        
        for (j = i + 2; j < n; ++j)
        {
            matrix[j*n+i] = 0.0;
            matrix[i*n+j] = 0.0;
        }
    }
}

int n_(double* matrix, int n, double lam)
{
    int i;
    int res;
    double elem;
    
    elem = matrix[0] - lam;
    
    if (elem < 0)
        res = 1;
    else
        res = 0;
    
    for (i = 1; i < n; ++i)
    {
        elem = matrix[i*n+i] - lam - matrix[i*n + i-1] * matrix[(i-1)*n+i]/elem;
        
        if (elem < 0)
            ++res;
    }
    
    return res;
}
