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
    
    Rotation(matrix, n);
    
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

void Rotation(double* matrix, int n)
{
    int i, j, k;
    double x, y, r, matrix_ik, matrix_jk, cosPhi, sinPhi;
    double matrix_ii, matrix_ij, matrix_ji, matrix_jj;
    
    for (i = 0; i < n-2; ++i)
    {
       for (j = i+2; j < n; ++j)
        {
            x = matrix[(i+1)*n+i];
            y = matrix[j*n+i];
            
            if (fabs(y) < 1e-100)
                continue;
            
            r = sqrt(x*x+y*y);
            
            if (r < 1e-100)
                continue;
            
            cosPhi = x/r;
            sinPhi = -y/r;
            
            for (k = i; k < n; ++k)
            {
                matrix_ik = matrix[(i+1)*n+k];
                matrix_jk = matrix[j*n+k];
                
                matrix[(i+1)*n+k] = matrix_ik * cosPhi - matrix_jk * sinPhi;
                matrix[j*n+k] = matrix_ik * sinPhi + matrix_jk * cosPhi;
                
                if (k != i+1 && k != j)
                {
                    matrix[k*n+i+1] = matrix[(i+1)*n+k];
                    matrix[k*n+j] = matrix[j*n+k];
                }
            }//*Tij
            
            matrix_ii = matrix[(i+1)*n+i+1];
            matrix_ji = matrix[j*n+i+1];
            matrix_ij = matrix[(i+1)*n+j];
            matrix_jj = matrix[j*n+j];

            matrix[(i+1)*n+i+1] = matrix_ii * cosPhi - matrix_ij * sinPhi;
            matrix[j*n+i+1] = matrix_ji * cosPhi - matrix_jj * sinPhi;
            matrix[(i+1)*n+j] = matrix_ii * sinPhi + matrix_ij * cosPhi;
            matrix[j*n+j] = matrix_ji * sinPhi + matrix_jj * cosPhi;//Tij^t
        }//67
    }
}
