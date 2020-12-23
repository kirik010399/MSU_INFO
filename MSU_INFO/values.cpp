#include <math.h>
#include "values.hpp"
#include "matrix.hpp"

void calculate_values(double* a, double* x, double eps, int n)
{
    int i, j, i1, j1;
    double x_, y_;
    double cos_phi, sin_phi;
    
    for (i = 0; i < n; ++i)
        x[i] = 0.0;
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if (i != j)
                x[i] += a[i*n+j] * a[i*n+j];
        }
    }//x = b, sum of squares not diag elements
    
    i1 = 0;
    j1 = 1;
    
    while (vector_norm(x, n) > eps)//limit->0
    {
        x_ = -2.0 * a[i1*n+j1];//p.89, up
        y_ = a[i1*n+i1] - a[j1*n+j1];//p.89, up
        
        if (fabs(y_) < 1e-100)
        {
            cos_phi = sqrt(2)/2;
            sin_phi = sqrt(2)/2;
        }
        else
        {
            cos_phi = 1/sqrt(2) * sqrt(1.0 + fabs(y_) / sqrt(x_*x_+y_*y_));
            sin_phi = 0.5 * (x_*y_ > 0 ? 1.0: -1.0) * fabs(x_) / (cos_phi * sqrt(x_*x_+y_*y_));
        }//p.89, (8)
        
        for (j = 0; j < n; ++j)
        {
            x_ = a[i1*n+j];
            y_ = a[j1*n+j];

            a[i1*n+j] = x_ * cos_phi - y_ * sin_phi;
            a[j1*n+j] = x_ * sin_phi + y_ * cos_phi;

            if (j != i1 && j != j1)
            {
                a[j*n+i1] = a[i1*n+j];
                a[j*n+j1] = a[j1*n+j];
            }//from simmetrical, don't want to change i1 and j1 columns
        }//*Tij, p.87, only i1 and j1 strings changes

        x_ = a[i1*(n+1)];
        y_ = a[i1*n+j1];

        a[i1*n+i1] = x_ * cos_phi - y_ * sin_phi;//*Tij^t

        y_ = a[j1*n+i1];
        x_ = a[j1*(n+1)];

        a[j1*n+j1] = y_ * sin_phi + x_ * cos_phi;//*Tij^t

        a[i1*n+j1] = 0;//*Tij^t
        a[j1*n+i1] = 0;//*Tij^t
        
        x[i1] = 0;
        
        for (i = 0; i < n; ++i)
        {
            if (i != i1)
                x[i1] += a[i*n+i1] * a[i*n+i1];
        }//recalculating x. p.92 (12)-(13)
        
        x[j1] = 0.0;
        
        for (j = 0; j < n; ++j)
        {
            if (j != j1)
                x[j1] += a[j*n+j1] * a[j*n+j1];
        }//recalculating x. p.92 (12)-(13)
        
        ++j1;
        if (j1 == n)
        {
            ++i1;
            j1 = i1 + 1;
            if (i1 == n - 1)
            {
                i1 = 0;
                j1 = 1;
            }
        }
    }
    
    //now x is result
    for (i = 0; i < n; ++i)
        x[i] = a[i*n+i];
}
