#include "matrix.hpp"
#include <stdio.h>
#include <math.h>

double f(int i, int j)
{
    return i+j;
}

int enter_matrix(double* a, int n, FILE* fin)
{
    int i, j;
    
    if (fin)
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                if (fscanf(fin, "%lf", &a[i*n+j]) != 1)
                    return -1;
            }
        }
    }
    else
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                a[i*n+j] = f(i, j);
            }
        }
    }
    
    return 0;
}

void print_matrix(double* a, int n, int m)
{
    int i, j;
    int min_ = fmin(n,m);
    
    for (i = 0; i < min_; ++i)
    {
        for (j = 0; j < min_; ++j)
        {
            printf("%f ", a[i*n+j]);
        }
        printf("\n");
    }
}

double norm(double* a, double* a_inv, int n)
{
    int i, j, k;
    double temp, sum = 0.0, max = 0.0;
        
    for (i = 0; i < n; ++i)
    {
        sum = 0.0;
        
        for (j = 0; j < n; ++j)
        {
            temp = 0.0;
            
            for (k = 0; k < n; ++k)
                temp += a[i*n+k] * a_inv[k*n+j];
            
            if (i == j)
                temp -= 1.0;
            
            sum += fabs(temp);
        }
        
        if (sum > max)
            max = sum;
    }
    
    return max;
}
