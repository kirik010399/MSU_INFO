#include <math.h>
#include "values.hpp"
#include "matrix.hpp"

void calculate_values(double* a, double* x, double *x_, double eps, int n)
{
    int i, j, k;
    reflection(a, x_, n);
    
    double norm_ = norm(a, n);
    double exit_eps = eps;
    
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
