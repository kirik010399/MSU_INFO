#include "calculatingManager.h"
#include <math.h>
#include <stdlib.h>

void calculateValues(double* matrix, double* vector, double left, double right, int n)
{
    Otr(matrix, n);
    values(matrix, n, vector, left, right);
}

void values(double *matrix, int n, double *vector, double left, double right)
{
    static int k = 0;
    int c, j;
    
    c = n_(matrix, n, right) - n_(matrix, n, left);
        
    if (right - left > 1e-10 && c != 0)
    {
        values(matrix, n, vector, left, (left+right)/2);
        values(matrix, n, vector, (left+right)/2, right);
    }
    else if (c != 0)
    {
        for (j = 0; j < c; ++j)
            vector[k + j] = (left+right)/2;
        
        k += c;
    }//95
}

void Otr(double *matrix, int n)
{
    double sk, akk, xk, xy;
    double *x, *y, *z;
    
    x = (double*)malloc(n * sizeof(double));
    y = (double*)malloc(n * sizeof(double));
    z = (double*)malloc(n * sizeof(double));
    
    for (int k = 0; k < n-2; k++)
    {
        sk = 0;
        
        for (int j = k+2; j < n; j++)
            sk += matrix[j*n+k] * matrix[j*n+k];
        
        akk = sqrt(matrix[(k+1)*n+k] * matrix[(k+1)*n+k] + sk);
        
        x[0] = matrix[(k+1)*n+k] - akk;
        
        for (int j = 1; j < n-k-1; j++)
            x[j] = matrix[(j+k+1)*n+k];
        
        xk = sqrt(x[0] * x[0] + sk);
        
        if (xk < 1e-100)
            continue;
        
        xk = 1.0/xk;
        
        for (int j = 0; j < n-k-1; j++)
            x[j] *= xk;
        
        for (int i = 0; i < n-k-1; i++)
        {
            y[i] = 0;
            
            for (int j = 0; j < n-k-1; j++)
                y[i] += matrix[n*(k+1+i)+(k+1+j)] * x[j];
        }
        
        xy = 0.0;
        for (int i = 0; i < n-k-1; i++)
            xy += x[i] * y[i];
        
        xy *= 2;
        for (int i = 0; i < n-k-1; i++)
            z[i] = 2 * y[i] - xy * x[i];
        
        for (int i = 0; i < n-k-1; i++)
        {
            for (int j = 0; j < n-k-1; j++)
            {
                matrix[n*(k+1+i)+(k+1+j)] = matrix[n*(k+1+i)+(k+1+j)] - z[j] * x[i] - x[j] * z[i];
            }
        }
        
        for (int i = k+2; i < n; i++)
        {
            matrix[n*i+k] = 0.0;
            matrix[n*(k+1)-(n-i)] = 0.0;
        }
        
        matrix[n*(k+1)+k] = matrix[n*k+(k+1)] = akk;
    }
    
    free(x);
    free(y);
    free(z);
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
