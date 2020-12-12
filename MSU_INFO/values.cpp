#include <math.h>
#include "values.hpp"

void calculate_values(double* a, double* x, int *values_count, double left, double right, double eps, int n)
{
    int i, j;
    double alp;
    double max_a, max_b;
        
    for (i = 0; i < n; ++i)
        x[i] = 0; 
    
    rotate(a, n);
    
    max_a = a[0];
    max_b = a[1];
    
    for (i = 1; i < n; ++i)
    {
        if (fabs(a[i*n+i]) > max_a)
            max_a = fabs(a[i*n+i]);

        if (i<n-1)
        {
            if (fabs(a[i*n + i+1]) > max_b)
                max_b = fabs(a[i*n + i+1]);
        }
    }

    alp = 4 * fmax(max_a, max_b);
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            a[i*n+j] /= alp;
            
            if (i != j && a[i*n+j] < 1e-16)
                a[i*n+j] = 0;
        }
    }//97
    
    right += eps;
    left -= eps;
    
    if (eps/alp > 1e-16)
        eps /= alp;
    
    right /= alp;
    left /= alp;
    
    values(a, x, values_count, left, right, n, eps);
    
    for (i = 0; i < n; ++i)
        x[i] *= alp;
}

void values(double *a, double *x, int *values_count, double left, double right, int n,  double eps)
{
    int c, j;
    
    c = n_(a, n, right) - n_(a, n, left);
        
    if (right - left > eps && c != 0)
    {
        values(a, x, values_count, left, (left+right)/2, n, eps);
        values(a, x, values_count, (left+right)/2, right, n, eps);
    }
    else if (c != 0)
    {
        for (j = 0; j < c; ++j)
            x[*values_count+j] = (left+right)/2;

        *values_count += c;
    }//95
}

int n_(double* a, int n, double lam)
{
    int i;
    int res;
    double elem;
    
    elem = a[0] - lam;
    
    if (elem < 0)
        res = 1;
    else
        res = 0;
    
    for (i = 1; i < n; ++i)
    {
        if (fabs(elem) < 1e-18)
            elem = 1e-10;
        
        elem = a[i*n+i] - lam - a[i*n + i-1] * a[(i-1)*n+i]/elem;
        
        if (elem < 0)
            ++res;
    }
    
    return res;
}

void rotate(double* a, int n)
{
    int i, j, k;
    double x_, y_, r, a_ik, a_jk, cos_phi, sin_phi;
    double a_ii, a_ij, a_ji, a_jj;
    
    for (i = 0; i < n-2; ++i)
    {
       for (j = i+2; j < n; ++j)
        {
            x_ = a[(i+1)*n+i];
            y_ = a[j*n+i];
            
            if (fabs(y_) < 1e-16)
                continue;
            
            r = sqrt(x_*x_+y_*y_);
            
            if (r < 1e-16)
                continue;
            
            cos_phi = x_/r;
            sin_phi = -y_/r;
            
            for (k = i; k < n; ++k)
            {
                a_ik = a[(i+1)*n+k];
                a_jk = a[j*n+k];
                
                a[(i+1)*n+k] = a_ik * cos_phi - a_jk * sin_phi;
                a[j*n+k] = a_ik * sin_phi + a_jk * cos_phi;
                
                if (k != i+1 && k != j)
                {
                    a[k*n+i+1] = a[(i+1)*n+k];
                    a[k*n+j] = a[j*n+k];
                }
            }//*Tij
            
            a_ii = a[(i+1)*n+i+1];
            a_ji = a[j*n+i+1];
            a_ij = a[(i+1)*n+j];
            a_jj = a[j*n+j];

            a[(i+1)*n+i+1] = a_ii * cos_phi - a_ij * sin_phi;
            a[j*n+i+1] = a_ji * cos_phi - a_jj * sin_phi;
            a[(i+1)*n+j] = a_ii * sin_phi + a_ij * cos_phi;
            a[j*n+j] = a_ji * sin_phi + a_jj * cos_phi;//Tij^t
        }//67
    }
}
