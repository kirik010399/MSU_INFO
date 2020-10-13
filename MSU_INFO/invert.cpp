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
            a_inv[get_elem(i, j)] = double(i == j);
    
    for (i = 0; i < n; ++i)
    {
        tmp = a[get_elem(i, i)];
        for (k = 0; k < i; ++k)
            tmp -= a[get_elem(k, i)] * a[get_elem(k, i)] * d[k];
        
        d[i] = tmp > 0 ? 1.0 : -1.0;

        if (fabs(tmp) < eps)
            return -1;

        a[get_elem(i, i)] = sqrt(fabs(tmp));

        for (j = i+1; j < n; ++j)
        {
            tmp = a[get_elem(i, j)];
            for (k = 0; k < i; ++k)
                tmp -= a[get_elem(k, i)] * d[k] * a[get_elem(k, j)];
            a[get_elem(i, j)] = tmp/(a[get_elem(i, i)] * d[i]);
        }
    }
    
    for (int k = 0; k < n; ++k)
    {
        for (i = 0; i < n; ++i)
        {
            tmp = double(k == i);
            
            for (j = 0; j < i; ++j)
                tmp -= a[get_elem(j, i)] * a_inv[get_elem(j, k)];
            
            a_inv[get_elem(i, k)] = tmp/a[get_elem(i, i)];
        }

        for (i = n-1; i >= 0; --i)
        {
            tmp = a_inv[get_elem(i, k)];
            for (j = i+1; j < n; ++j)
                tmp -= a[get_elem(i, j)] * a_inv[get_elem(j, k)];
            a_inv[get_elem(i, k)] = tmp/(a[get_elem(i, i)] * d[i]);
        }
    }

    return 0;
}
