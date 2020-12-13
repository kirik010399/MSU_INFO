#include "matrix.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

double f(int k, int n, int i, int j)
{
    switch (k)
    {
        case 1:
            return n-fmax(i, j)+1;
            
        case 2:
            if (i == j)
                return 2;
            if (fabs(i-j) == 1)
                return -1;
            return 0;
            
        case 3:
            if (i == j && i < n-1)
                return 1;
            if (j == n-1)
                return i;
            if (i == n-1)
                return j;
            return 0;
            
        case 4:
            return 1.0/(i+j+1);
            
        default:
            return -1;
    }
}

int enter_matrix(double* a, int n, int k, FILE* fin)
{
    int i, j;
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if (k == 0)
            {
                if (fscanf(fin, "%lf", &a[i*n+j]) != 1)
                    return -1;
            }
            else
            {
                a[i*n+j] = f(k, n, i, j);
            }
        }
    }
    
    return 0;
}

void print_matrix(double* a, int l, int n, int m)
{
    int i, j;
        
    for (i = 0; i < fmin(l, m); ++i)
    {
        for (j = 0; j < m; ++j)
        {
            printf("%10.3e ", a[i*n+j]);
        }
        printf("\n");
    }
}

void residual(double* a, double* x, double *norm1, double *norm2, int n)
{
    int i, j;
    
    *norm1 = 0.0;
    *norm2 = 0.0;
    
    for (i = 0; i < n; ++i)
    {
        *norm1 += a[i*n+i] - x[i];
        *norm2 -= x[i] * x[i];
        
        for (j = 0; j < n; ++j)
            *norm2  += a[i*n+j] * a[i*n+j];
    }
}
