#include "calculatingManager.h"
#include <math.h>
#include <stdlib.h>

//int k = 0;

int calculateValues(double* matrix, double* vector, double left, double right, double eps, int n, double *x, double *y, double *z)
{
    int i, j;
    double maxA, maxB;
    double alp;
    int k;
    
    for (i = 0; i < n; ++i)
        vector[i] = 0;
    
    Refl(matrix, n, x, y ,z);
    
    maxA = matrix[0];
    maxB = matrix[1];
    
    for (i = 1; i < n; ++i)
    {
        if (fabs(matrix[i*n+i]) > maxA)
            maxA = fabs(matrix[i*n+i]);
        
        if (i < n-1)
        {
            if (fabs(matrix[i*n + i+1]) > maxB)
                maxB = fabs(matrix[i*n + i+1]);
        }
    }
    
    alp = 4 * fmax(maxA, maxB);
    
    if(fabs(alp) > 1e-18)
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                matrix[i*n+j] /= alp;
                
                if (i!=j && matrix[i*n+j] < 1e-18)
                    matrix[i*n+j] = 0;
            }
        }//97
        
        left /= alp;
        right /= alp;
        eps /= alp; 
    }
    
    k = values(matrix, n, vector, left, right, eps);
    
    if(fabs(alp) > 1e-18)
    {
        for (i = 0; i < n; ++i)
            vector[i] *= alp;
    }

    return k;
}

int values(double *matrix, int n, double *vector, double left, double right, double eps)
{
    double c;
    double a, b;
    int k;
    int k1, k2;
    
    k1 = n_(matrix, n, left-eps);
    k2 = n_(matrix, n, right+eps);
    
    for (k = k1+1; k <= k2; ++k)
    {
        if (k == k1+1)
            a = left;
        else
            a =  vector[k-k1-2];
        
        b = right;
        
        a -= eps;
        b += eps;
        
        while(b - a > eps)
        {
            c = (a+b)/2;

            if (n_(matrix, n, c) < k)
                a = c;
            else
                b = c;
        }
        
        vector[k-k1-1] = (a+b)/2;
    }
    
    return k2-k1;
}

void Refl(double *matrix, int n, double *x, double *y, double *z)
{
    double sk, akk, xk, xy;
    
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
}

int n_(double* matrix, int n, double lam)
{
    int k, m;
    double x, y, u, v, A, maxx, B, gam;
    
    x = matrix[0] - lam;
    y = 1.0;
    
    if (x*y < 0)
        m = 1;
    else
        m = 0;
    
    for (k = 1; k < n; ++k)
    {
        A = matrix[k*n+k] - lam;
        B = matrix[k*n + k-1];
        
        maxx = fmax(fabs(x), fabs(B*B*y));
        
        if(maxx < 1e-18)
            maxx = 1e-15;
        
        gam = (1/1e-18)/maxx;
        
        u = gam * (A*x - B*B*y);
        v = gam * x;
        
        if (u*x < 0.0)
            ++m;
        x = u;
        y = v;    // 97
    }
    
    return m;
}
