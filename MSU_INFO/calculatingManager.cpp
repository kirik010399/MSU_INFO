#include "calculatingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std;

int k = 0;

int calculateValues(double* matrix, double* vector, double left, double right, double eps, int n)
{
    int i, j, alp;
    double maxA, maxB;
    
    eps = fmax(1e-10, eps);
    
    for (i = 0; i < n; ++i)
        vector[i] = 0; 
    
    Reflection(matrix, eps, n);
    
    maxA = matrix[0];
    maxB = matrix[1];
    
    for (i = 1; i < n; ++i)
    {
        if (fabs(matrix[i*n+i]) > maxA)
            maxA = fabs(matrix[i*n+i]);

        if (i<n-1)
        {
            if (fabs(matrix[i*n + i+1]) > maxB)
                maxB = fabs(matrix[i*n + i+1]);
        }
    }

    alp = 4 * fmax(maxA, maxB);
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            matrix[i*n+j]/=alp;
            
            if (i != j && matrix[i*n+j] < 1e-18)
                matrix[i*n+j] = 0;
        }
    }//97
    
    values(matrix, n, vector, left, right, eps);
    
    for (i = 0; i < n; ++i)
        vector[i]*=alp;
    
    return k;
}

void values(double *matrix, int n, double *vector, double left, double right, double eps)
{
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

int n_(double* matrix, int n, double lam)
{
    int i, res;
    double x, y, u, v, a, maxx, b, gam;
    
    x = matrix[0] - lam;
    y = 1.0;
    
    if (x*y < 0)
        res = 1;
    else
        res = 0;
    
    for (i = 1; i < n; ++i)
    {
        a = matrix[i*n+i] - lam;
        b = matrix[i*n + i-1];
        
        maxx = fabs(b*b*y);
        
        if (fabs(x) > maxx)
            maxx = fabs(x);
        
        gam = (1/1e-18)/maxx;
        
        u = gam * (a*x - b*b*y);
        v = gam * x;
        
        if (u*x < 0.0)
            ++res;
        
        x = u;
        y = v;//97
    }
    
    return res;
}

void Reflection(double *matrix, double eps, int n)
{
    double sk, akk, xk, xy;
    double *x, *y, *z;
    
    x = new double[n];
    y = new double[n];
    z = new double[n];
    
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
        
        if (xk < eps)
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
    
    delete []x;
    delete []y;
    delete []z;
}
