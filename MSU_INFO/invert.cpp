#include "invert.hpp"
#include "matrix.hpp"
#include <math.h>

int invert(double* a, double* a_inv, double* d, int n)
{
    int i, j, k;
    double tmp;

    double eps = 1e-20;

    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            a_inv[get_elem(i, j, n)] = double(i == j);
    
    for (i = 0; i < n; ++i)
    {
        tmp = a[get_elem(i, i, n)];
        for (k = 0; k < i; ++k)
            tmp -= a[get_elem(k, i, n)] * a[get_elem(k, i, n)] * d[k];
        
        if (tmp > 0)
            d[i] = 1.0;
        else
            d[i] = -1.0;
        
        if (fabs(tmp) < eps)
            return -1;

        a[get_elem(i, i, n)] = sqrt(fabs(tmp));

        for (j = i+1; j < n; ++j)
        {
            tmp = a[get_elem(i, j, n)];
            for (k = 0; k < i; ++k)
                tmp -= a[get_elem(k, i, n)] * d[k] * a[get_elem(k, j, n)];
            a[get_elem(i, j, n)] = tmp/(a[get_elem(i, i, n)] * d[i]);
        }
    }
    
    for (int k = 0; k < n; ++k)
    {
        for (i = 0; i < n; ++i)
        {
            tmp = double(k == i);
            
            for (j = 0; j < i; ++j)
                tmp -= a[get_elem(j, i, n)] * a_inv[get_elem(j, k, n)];
            
            a_inv[get_elem(i, k, n)] = tmp/a[get_elem(i, i, n)];
        }

        for (i = n-1; i >= 0; --i)
        {
            tmp = a_inv[get_elem(i, k, n)];
            for (j = i+1; j < n; ++j)
                tmp -= a[get_elem(i, j, n)] * a_inv[get_elem(j, k, n)];
            a_inv[get_elem(i, k, n)] = tmp/(a[get_elem(i, i, n)] * d[i]);
        }
    }

    return 0;
}
