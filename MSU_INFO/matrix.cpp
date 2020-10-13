#include "matrix.hpp"
#include <stdio.h>
#include <math.h>

int get_elem(int i, int j)
{
    if (i < j)
        return j*(j+1)/2 + i;
    else
        return i*(i+1)/2 + j;
}

double f(int k, int n, int i, int j)
{
    switch (k)
    {
        case 1:
            return n-fmax(i, j)+1;
        case 2:
            return fmax(i, j);
        case 3:
            return fabs(i-j);
        case 4:
            return 1.0/(i+j+1);
        default:
            return -1;
    }
}

int enter_matrix(double* a, int n, int k, FILE* fin)
{
    int i, j;
    
    if (fin)
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                if (fscanf(fin, "%lf", &a[get_elem(i, j)]) != 1)
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
                a[get_elem(i, j)] = f(k, n, i, j);
            }
        }
    }
    
    return 0;
}

void print_matrix(double* a, int n, int m)
{
    int i, j;
    
    for (i = 0; i < m; ++i)
    {
        for (j = 0; j < m; ++j)
        {
            printf("%10.3e ", a[get_elem(i, j)]);
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
                temp += a[get_elem(i, k)] * a_inv[get_elem(k, j)];
            
            if (i == j)
                temp -= 1.0;
            
            sum += fabs(temp);
        }
        
        if (sum > max)
            max = sum;
    }
    
    return max;
}
