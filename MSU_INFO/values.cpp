#include <math.h>
#include "values.hpp"
#include "matrix.hpp"

int calculate_values(double* a, double* x, double eps, int n)
{
    int i, j, k;
    
    rotate(a, n);
//    print_matrix(a, n, n, 10);
    
    double norm_ = norm(a, n);
    double exit_eps = eps;
    
    if (norm_ < 1e-16)
        return -1;
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            a[i*n+j] /= norm_;
        }
    }
    
    for (k = n-1; k > 1; --k)
    {
//        printf("K: %d\n", k);
        while (fabs(a[k*n+k-1]) > exit_eps)
        {
//            printf("%.16lf\n", a[k*n+k-1]);

            double shift = a[k*n + k];
            
            for (i = 0; i <= k; ++i)
                a[i*n+i] -= shift;
            
            int flag = LR(a, k, n);

            while (flag == -1)
            {
                for (i = 0; i <= k; ++i)
                    a[i*n+i] += shift;
                
                shift -= 1e-5;
                
                for (i = 0; i <= k; ++i)
                    a[i*n+i] -= shift;
                
                flag = LR(a, k, n);
            }
            
            RL(a, k, n);

            for (i = 0; i <= k; ++i)
                a[i*n+i] += shift;
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
        x[i] = a[i*n+i] * norm_;
    
    return 0;
}

int LR(double *a, int k, int n)
{
    int i, j;
    
    for (i = 1; i <= k; ++i)
    {
        if(fabs(a[(i-1)*n+i-1]) < 1e-16)
            return -1;
        
        a[i*n+i-1] = a[i*n+i-1] / a[(i-1)*n+i-1];

        for (j = i; j <= k; ++j)
            a[i*n+j] -= a[i*n+i-1] * a[(i-1)*n+j];//(4)
    }
    
    return 0; 
}

void RL(double *a, int k, int n)
{
    int i, j;

    for (i = 0; i <= k; ++i)
    {
        if (i != 0)
            a[i*n+i-1] *= a[i*n+i];

        for (j = i; j <= k-1; ++j)
            a[i*n+j] += a[i*n+j+1] * a[(j+1)*n+j];//(8)
    }
}

void rotate(double* a, int n)
{
    int i, j, k;
    double x_, y_, r, a_ik, a_jk, cos_phi, sin_phi;
    double a_ki, a_kj;
    
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
            }//*Tij
            
            for (k = 0; k < n; ++k)
            {
                a_ki = a[k*n+i+1];
                a_kj = a[k*n+j];
                
                a[k*n+i+1] = a_ki * cos_phi - a_kj * sin_phi;
                a[k*n+j] = a_ki * sin_phi + a_kj * cos_phi;
            }//*Tij^t
        }
    }
}
