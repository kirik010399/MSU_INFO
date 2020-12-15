#include "solve.hpp"
#include <math.h>

using namespace std;

int solve(double* a, double* b, double* x, int *ind, int n)
{
    int i, j, k, max_str_index, max_col_index;
    double value, max_elem;
    double t;

    double eps = 1e-30;
    
    for (i = 0; i < n; ++i)
        ind[i] = i;
    
    for (i = 0; i < n; ++i)
    {
        max_elem = fabs(a[i*n+i]);
        max_str_index = i;
        max_col_index = i;
        
        for (j = i; j < n; ++j)
        {
            for (k = i; k < n; ++k)
            {
                if (fabs(a[j*n+k]) > max_elem)
                {
                    max_elem = fabs(a[j*n+k]);
                    max_str_index = j;
                    max_col_index = k;
                }
            }
        }

        if (fabs(max_elem) < eps)
            return -1;
        
        if (max_str_index != i) // Swap strings (i <-> max)
        {
            for (j = 0; j < n; ++j)
            {
                t = a[max_str_index*n+j];
                a[max_str_index*n+j] = a[i*n+j];
                a[i*n+j] = t;
            }
            
            t = b[max_str_index];
            b[max_str_index] = b[i];
            b[i] = t;
        }
        
        t = ind[i];
        ind[i] = ind[max_col_index];
        ind[max_col_index] = t;
        
        if (max_col_index != i) // Swap columns (i <-> max)
        {
            for (j = 0; j < n; ++j)
            {
                t = a[j*n+max_col_index];
                a[j*n+max_col_index] = a[j*n+i];
                a[j*n+i] = t;
            }
        }
        
        value = 1.0/a[i*n+i];
        
        for (j = i; j < n; ++j)
            a[i*n+j] *= value;
        
        b[i] *= value;
        
        for (j = i+1; j < n; ++j)
        {
            value = a[j*n+i];
            
            for (k = i; k < n; ++k)
                a[j*n+k] -= a[i*n+k] * value;
            
            b[j] -= b[i] * value;
        }
    }

    for (i = n-1; i >= 0; --i)
    {
        value = b[i];
        
        for (j = i+1; j < n; ++j)
            value -= a[i*n+j] * x[ind[j]];
        
        x[ind[i]] = value;
    }
    
    return 0;
}

