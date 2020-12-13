#include <math.h>
#include "values.hpp"
#include "matrix.hpp"

void calculate_values(double* a, double* x, double *x1, double *x2, double *x_, double *y_, double *z_, double eps, int n)
{
    int i, k;
    reflection(a, x_, y_, z_, n);
    
    double exit_eps = eps * norm(a, n);
    
    for (k = n-1; k > 1; --k)
    {
        while (fabs(a[k*n+k-1]) > exit_eps)
        {
            double prev_value = fabs(a[k*n+k-1]);
            
            double shift = a[k*n + k];
            
            for (i = 0; i <= k; ++i)
                a[i*n+i] -= shift;
            
            QR(a, x1, x2, k, n);
            RQ(a, x1, x2, k, n);

            for (i = 0; i <= k; ++i)
                a[i*n+i] += shift;
            
            double cur_value = fabs(a[k*n+k-1]);

            if (fabs(cur_value - prev_value) < 1e-10)
                break;
        }
    }
    
    if (n > 1)
    {
        double tr = a[0*n+0] + a[1*n+1];
        double det = a[0*n+0] * a[1*n+1] - a[0*n+1] * a[1*n+0];
        double d = sqrt(tr*tr - 4.0*det);

        a[0*n+0] = 0.5 * (tr+d);
        a[1*n+1] = 0.5 * (tr-d);
    }
    
    for (i = 0; i < n; ++i)
        x[i] = a[i*n+i];
}

void QR(double *a, double *x1, double *x2, int k, int n)
{
    int i, j;

    for (i = 0; i < k; ++i)
    {
        double s = a[(i+1)*n+i] * a[(i+1)*n+i];
        
        if (s < 1e-16)
        {
            x1[i] = (a[i*n+i] > 0.0 ? 1.0 : -1.0);
            x2[i] = 0.0;
        }
        else
        {
            double norm_a1 = sqrt(a[i*n+i] * a[i*n+i] + s);

            double x_i = (a[i*n+i] - norm_a1);
            double norm_x = sqrt(x_i * x_i + s);

            x1[i] = x_i / norm_x;
            x2[i] = a[(i+1)*n+i] / norm_x;
        }

        for (j = i; j <= k; ++j)
        {
            double sum = 2.0 * (x1[i]*a[i*n+j] + x2[i]*a[(i+1)*n+j]);

            a[i*n+j] -= sum * x1[i];
            a[(i+1)*n+j] -= sum * x2[i];
        }
    }
}

void RQ(double *a, double *x1, double *x2, int k, int n)
{
    int i, j;
    
    for (i = 0; i < k; ++i)
    {
        for (j = 0; j < i+2; ++j)
        {
            double sum = 2 * (a[j*n+i] * x1[i] + a[j*n+i+1] * x2[i]);
            
            a[j*n+i] -= sum * x1[i];
            a[j*n+i+1] -= sum * x2[i];
        }
    }
}

void reflection(double* a, double *x_, double *y_, double *z_, int n)
{
    double sk, akk, xk, xy;

    for (int k = 0; k < n-2; k++)
    {
        sk = 0;
        
        for (int j = k+2; j < n; j++)
            sk += a[j*n+k] * a[j*n+k];
        
        akk = sqrt(a[(k+1)*n+k] * a[(k+1)*n+k] + sk);
        
        x_[0] = a[(k+1)*n+k] - akk;
        
        for (int j = 1; j < n-k-1; j++)
            x_[j] = a[(j+k+1)*n+k];
        
        xk = sqrt(x_[0] * x_[0] + sk);
        
        if (xk < 1e-16)
            continue;
        
        xk = 1.0/xk;
        
        for (int j = 0; j < n-k-1; ++j)
            x_[j] *= xk;
        
        for (int i = 0; i < n-k-1; ++i)
        {
            y_[i] = 0;
            
            for (int j = 0; j < n-k-1; ++j)
                y_[i] += a[n*(k+1+i)+(k+1+j)] * x_[j];
        }
        
        xy = 0.0;
        for (int i = 0; i < n-k-1; ++i)
            xy += x_[i] * y_[i];
        
        xy *= 2;
        for (int i = 0; i < n-k-1; ++i)
            z_[i] = 2 * y_[i] - xy * x_[i];
        
        for (int i = 0; i < n-k-1; ++i)
        {
            for (int j = 0; j < n-k-1; ++j)
            {
                a[n*(k+1+i)+(k+1+j)] = a[n*(k+1+i)+(k+1+j)] - z_[j] * x_[i] - x_[j] * z_[i];
            }
        }
        
        for (int i = k+2; i < n; ++i)
        {
            a[n*i+k] = 0.0;
            a[n*(k+1)-(n-i)] = 0.0;
        }

        a[n*(k+1)+k] = a[n*k+(k+1)] = akk;
    }
}
