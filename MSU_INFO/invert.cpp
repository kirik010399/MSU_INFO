#include "invert.hpp"
#include <math.h>

int invert(double* a, double* a_inv, double *x, int n)
{
    int i, j, k;

    double eps;
    if (n < 10)
        eps = 1e-12;
    else
        eps = 1e-20; 
        
    for (i = 0; i < n; ++i)
    {
        x[i] = 0;
        
        for (j = 0; j < n; ++j)
        {
            if (i == j)
                a_inv[i*n+j] = 1;
            else
                a_inv[i*n+j] = 0;
        }
    }
    
    for (i = 0; i < n; ++i)
    {
        double s = 0.0;
        for (j = i+1; j < n; ++j)
            s += a[j*n+i] * a[j*n+i];//(12)

        double norm_a1 = sqrt(a[i*n+i]*a[i*n+i] + s);//(13)

        if (norm_a1 < eps)
            return -1; //det = 0;

        x[i] = a[i*n+i] - norm_a1;
        
        for (j = i+1; j < n; ++j)
            x[j] = a[j*n+i]; //(14)
        
        double norm_x = sqrt(x[i]*x[i] + s);//(15)

        if (norm_x < eps)
            continue;

        for (j = i; j < n; ++j)
            x[j] /= norm_x; //(16)

        for (k = i; k < n; ++k) //лемма 10-11
        {
            double sum = 0.0;
            for (j = i; j < n; ++j)
                sum += x[j] * a[j*n+k];

            sum *= 2.0;
            for (j = i; j < n; ++j)
                a[j*n+k] -= sum * x[j];
        }

        for (k = 0; k < n; ++k)//лемма 10-11
        {
            double sum = 0.0;
            for (j = i; j < n; ++j)
                sum += x[j] * a_inv[j*n+k];

            sum *= 2.0;
            for (j = i; j < n; ++j)
                a_inv[j*n+k] -= sum * x[j];
        }
    }

    for (k = 0; k < n; ++k)
    {
        for (i = n-1; i >= 0; --i)
        {
            double temp = a_inv[i*n+k];

            for (j = i+1; j < n; ++j)
                temp -= a[i*n+j] * a_inv[j*n+k];

            a_inv[i*n+k] = temp/a[i*n+i];
        }
    }//Обратный Гаусс
    
    return 0;

}

