#include "invert.hpp"
#include <math.h>

using namespace std;

int solve(double* a, double* b, double* x, int *ind, int n)
{
    int i, j, k;
    double value;
    
    int maxStrInd, maxColInd;

    double eps = 1e-30;
    
    for (i = 0; i < n; ++i)
        ind[i] = i;
    
    for (i = 0; i < n; ++i)
    {
        value = fabs(a[i*n+i]);
        maxStrInd = i;
        maxColInd = i;
        
        for (j = i; j < n; ++j)
        {
            for (k = i; k < n; ++k)
            {
                if (fabs(a[j*n+k]) > value)// Search for max in matrix
                {
                    value = fabs(a[j*n+k]);
                    maxStrInd = j;
                    maxColInd = k;
                }
            }
        }
        
        if (fabs(value) < eps)
            return -1;
        
        if (maxStrInd != i) // Swap strings (i <-> max)
        {
            for (j = 0; j < n; ++j)
                swap(a[maxStrInd*n+j], a[i*n+j]);
            
            swap(b[maxStrInd], b[i]);
        }
        
        swap(ind[i], ind[maxColInd]);//swap variables

        if (maxColInd != i) // Swap columns (i <-> max)
        {
            for (j = 0; j < n; ++j)
                swap(a[j*n+maxColInd], a[j*n+i]);
        }
        
        for(j = 0; j < n; ++j) // Subtraction from all lines
        {
            if (j != i)
            {
                value = a[j*n+i]/a[i*n+i];
                
                for(k = i; k < n; ++k)
                    a[j*n+k] -= value*a[i*n+k];
                
                b[j] -= value*b[i];
            }
        }
    }
    
    for (i = 0; i < n; ++i)
        x[ind[i]] = b[i]/a[i*n+i];
    
    return 0;
}

