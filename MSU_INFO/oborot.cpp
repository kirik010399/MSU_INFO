#include "oborot.hpp"
#include "matr.hpp"
#include <math.h>

int oborot(double* a, double* a_obr, double* d, int n)
{
    int i,j,k;
    double val;

    for (i=0; i<n; i++)
        for (j=0; j<n; j++)
            a_obr[element(i,j,n)] = double(i == j);
    
    for (i=0; i<n; i++)
    {
        val = a[element(i,i,n)];
        for (k=0; k < i; k++)
            val -= a[element(k,i,n)] * a[element(k,i,n)] * d[k];
        
        if (val > 0)
            d[i] = 1.0;
        else
            d[i] = -1.0;
        
        if (fabs(val) < 1e-20)
            return -1;

        a[element(i,i,n)] = sqrt(fabs(val));

        for (j = i+1; j<n; j++)
        {
            val = a[element(i,j,n)];
            for (k=0; k < i; k++)
                val -= a[element(k,i,n)] * d[k] * a[element(k,j,n)];
            a[element(i,j,n)] = val/(a[element(i,i,n)] * d[i]);
        }
    }
    
    for (int k=0; k<n; k++)
    {
        for (i=0; i<n; i++)
        {
            val = double(k == i);
            for (j=0; j < i; j++)
                val -= a[element(j,i,n)] * a_obr[element(j,k,n)];
            a_obr[element(i,k,n)] = val/a[element(i,i,n)];
        }

        for (i = n-1; i >= 0; --i)
        {
            val = a_obr[element(i,k,n)];
            for (j = i+1; j<n; j++)
                val -= a[element(i,j,n)] * a_obr[element(j,k,n)];
            a_obr[element(i,k,n)] = val/(a[element(i,i,n)] * d[i]);
        }
    }

    return 0;
}
