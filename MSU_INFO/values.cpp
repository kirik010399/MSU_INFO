#include <math.h>
#include "values.hpp"
#include "matrix.hpp"

void calculate_values(double* a, double* x, double *cos_phi, double *sin_phi, double *x_, double eps, int n)
{
    int i, k;
    reflection(a, x_, n);
    
    double exit_eps = eps * norm(a, n);
    
    for (k = n-1; k > 1; --k)
    {
        while (fabs(a[k*n+k-1]) > exit_eps)
        {
            double prev_value = fabs(a[k*n+k-1]);
            
            double shift = a[k*n + k];
            
            for (i = 0; i <= k; ++i)
                a[i*n+i] -= shift;
            
            QR(a, cos_phi, sin_phi, k, n);
            RQ(a, cos_phi, sin_phi, k, n);

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

void QR(double *a, double *cos_phi, double *sin_phi, int k, int n)
{
    int i, j;
    double x_, y_, r;
    double a_ij, a_i1j;

    for (i = 0; i < k; ++i)
    {
        x_ = a[i*n+i];
        y_ = a[(i+1)*n+i];

        r = sqrt(x_*x_+y_*y_);

        if (r < 1e-16)
        {
            if (a[i*n+i] > 0.0)
                cos_phi[i] = 1.0;
            else
                cos_phi[i] = -1.0;
            
            sin_phi[i] = 0.0;
        }
        else
        {
            cos_phi[i] = x_/r;
            sin_phi[i] = -y_/r;
        }

        for (j = i; j <= k; ++j)
        {
            a_ij = a[i*n+j];
            a_i1j = a[(i+1)*n+j];

            a[i*n+j] = a_ij * cos_phi[i] - a_i1j * sin_phi[i];
            a[(i+1)*n+j] = a_ij * sin_phi[i] + a_i1j * cos_phi[i];
        }
    }
}

void RQ(double *a, double *cos_phi, double *sin_phi, int k, int n)
{
    int i;
    int j;
    double a_ji;
    double a_ji1;

    for (i = 0; i < k; ++i)
    {
        for (j = 0; j < i+2; ++j)
        {
            a_ji = a[j*n+i];
            a_ji1 = a[j*n+i+1];

            a[j*n+i] = a_ji * cos_phi[i] - a_ji1 * sin_phi[i];
            a[j*n+i+1] = a_ji * sin_phi[i] + a_ji1 * cos_phi[i];
        }
    }
}

void reflection(double* a, double *x_, int n)
{
    int i, j, k;

    for (i = 0; i < n-2; ++i)
    {
        double s = 0.0;
        for (j = i+2; j < n; ++j)
            s += a[j*n+i] * a[j*n+i];//(12)

        double norm_a1 = sqrt(a[(i+1)*n+i]*a[(i+1)*n+i] + s);//(13)
        
        if (norm_a1 < 1e-16)
            continue;

        if (s < 1e-16)
            continue;
        
        x_[i+1] = a[(i+1)*n+i] - norm_a1;
        
        for (j = i+2; j < n; ++j)
            x_[j] = a[j*n+i]; //(14)
        
        double norm_x = sqrt(x_[i+1]*x_[i+1] + s);//(15)
        
        if (norm_x < 1e-16)
            continue;
        
        for (j = i+1; j < n; ++j)
            x_[j] /= norm_x; //(16)

        for (k = i; k < n; ++k) //лемма 10-11
        {
            double sum = 0.0;
            for (j = i+1; j < n; ++j)
                sum += x_[j] * a[j*n+k];

            sum *= 2.0;
            for (j = i+1; j < n; ++j)
                a[j*n+k] -= sum * x_[j];
        }
        
        for (k = 0; k < n; ++k) //лемма 10-11
        {
            double sum = 0.0;
            for (j = i+1; j < n; ++j)
                sum += a[k*n+j] * x_[j];

            sum *= 2.0;
            for (j = i+1; j < n; ++j)
                a[k*n+j] -= sum * x_[j];
        }
    }
}
