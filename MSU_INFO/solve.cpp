#include "solve.hpp"
#include <math.h>

using namespace std;

int solve(double* a, double* b, double* x, int n)
{
    int i, j, k;
    double value;
    double x_, y_, r;
    double cosPhi, sinPhi;
    double a_ik, a_jk;
    double b_i, b_j;
    double eps = 1e-30;
    
    for (i = 0; i < n-1; ++i)
    {
        for (j = i+1; j < n; ++j)
        {
            x_ = a[i*n+i];
            y_ = a[j*n+i];
            
            if (fabs(y_) < eps)
                continue;

            r = sqrt(x_*x_+y_*y_);
            
            if (r < eps)
                return -1;

            cosPhi = x_/r;
            sinPhi = -y_/r;
            
            for (k = i; k < n; ++k)
            {
                a_ik = a[i*n+k];
                a_jk = a[j*n+k];
                
                a[i*n+k] = a_ik * cosPhi - a_jk * sinPhi;
                a[j*n+k] = a_ik * sinPhi + a_jk * cosPhi;
            }
            
            b_i = b[i];
            b_j = b[j];
            
            b[i] = b_i * cosPhi - b_j * sinPhi;
            b[j] = b_i * sinPhi + b_j * cosPhi;
        }
    }

    for (i = n-1; i >= 0; --i)
    {
        value = b[i];
        
        for (j = i+1; j < n; ++j)
            value -= a[i*n+j] * x[j];
        
        x[i] = value/a[i*n+i];
    }
    
    return 0;
}

