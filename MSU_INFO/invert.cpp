#include "invert.hpp"
#include <math.h>

int invert(double* a, double* a_inv, int n)
{
    int i, j, k;
    double temp1, temp2;

    double eps = 1e-16;
    double *d = new double [n]; 
//    double eps = fmax(pow(10, -n*3), 1e-100);//strange thing for strange a
        
    for (i = 0; i < n; ++i)
    {
        d[i] = 0;
        
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
        temp1 = 0.0;
        for (j = i + 1; j < n; j++)
            temp1 += a[j*n+i] * a[j*n+i];//(12)

        temp2 = sqrt(temp1 + a[i*n+i] * a[i*n+i]);//(13)

        if (temp2 < eps)
            return -1; //det = 0;

        d[i] = a[i*n+i] - temp2;
        
        for (j = i+1; j < n; ++j)
            d[j] = a[j*n+i]; //(14)
        
        temp1 = sqrt(d[i] * d[i] + temp1);//(15)

        if (temp1 < eps)
            continue;

        for (j = i; j < n; ++j)
            d[j] /= temp1; //(16)

        for (k = i + 1; k < n; ++k)
        {
            temp1 = 0.0;
            for (j = i; j < n; ++j)
                temp1 += d[j] * a[j*n+k];

            temp1 *= 2.0;//from formula
            for (j = i; j < n; ++j)
                a[j*n+k] -= temp1 * d[j];
        }

        for (k = 0; k < n; ++k)
        {
            temp1 = 0.0;
            for (j = i; j < n; ++j)
                temp1 += d[j] * a_inv[j*n+k];

            temp1 *= 2.0;//from formula
            for (j = i; j < n; ++j)
                a_inv[j*n+k] -= temp1 * d[j];
        }

        a[i*n+i] = temp2;
    }

    for (k = 0; k < n; ++k)
    {
        for (i = n - 1; i >= 0; --i)
        {
            temp1 = a_inv[i*n+k];

            for (j = i + 1; j < n; ++j)
                temp1 -= a[i*n+j] * a_inv[j*n+k];

            a_inv[i*n+k] = temp1/a[i*n+i];
        }
    }//Reverse Gauss
    
    return 0;

}

