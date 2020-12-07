#include "solve.hpp"
#include <math.h>

using namespace std;

int solve(double* a, double* b, double* x, int n)
{
    int i, j, k;
    double value;
    double x_, y_, r;
    double cos_phi, sin_phi;
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

            cos_phi = x_/r;
            sin_phi = -y_/r;
            
            for (k = i; k < n; ++k)
            {
                a_ik = a[i*n+k];
                a_jk = a[j*n+k];
                
                a[i*n+k] = a_ik * cos_phi - a_jk * sin_phi;
                a[j*n+k] = a_ik * sin_phi + a_jk * cos_phi;
            }
            
            b_i = b[i];
            b_j = b[j];
            
            b[i] = b_i * cos_phi - b_j * sin_phi;
            b[j] = b_i * sin_phi + b_j * cos_phi;
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

