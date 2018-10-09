#include "solvingFunctions.hpp"
#include <math.h>
#include <iostream>

using namespace std; 

int solveSystem(double* matrix, double* vector, double* result, int n)
{
    int i, j, k, maxElemIndex;
    double a, maxElem;
    
    double eps = fmax(pow(10, -n*3), 1e-100);
    
    for (i = 0; i < n; ++i)
    {
        maxElem = fabs(matrix[i*n+i]);
        maxElemIndex = i;
        
        for (j = i + 1; j < n; ++j)
        {
            if (maxElem < fabs(matrix[j*n+i]))
            {
                maxElem = fabs(matrix[j*n+i]);
                maxElemIndex = j;
            }
        }
        
        if (maxElemIndex != i)
        {
            for (j = i; j < n; ++j)
                swap (matrix[i*n+j], matrix[maxElemIndex*n+j]);
        
            swap (vector[i], vector[maxElemIndex]);
        }
        
        if (maxElem < eps)
            return -1;
        
        a = 1.0/matrix[i*n+i];
        
        for (j = i; j < n; ++j)
            matrix[i*n+j] *= a;
        
        vector[i] *= a;
        
        for (j = i+1; j < n; ++j)
        {
            a = matrix[j*n+i];
            
            for (k = i; k < n; ++k)
                matrix[j*n+k] -= matrix[i*n+k] * a;
            
            vector[j] -= vector[i] * a;
        }
    }
    
    for (i = n-1; i >= 0; --i)
    {
        a = vector[i];
        
        for (j = i+1; j < n; ++j)
            a -= matrix[i * n + j] * result[j];
        
        result[i] = a;
    }
    
    return 0;
}
