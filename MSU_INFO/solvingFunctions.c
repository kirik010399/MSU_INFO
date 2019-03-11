#include "solvingFunctions.h"
#include <math.h>


int solveSystem(double* matrix, double* vector, double* result, int *var, int n, float eps)
{
    int i, j, k, maxColIndex;
    double a, maxElem;
    int tempVar;
    double temp;
    
    for (i = 0; i < n; ++i)
        var[i] = i;
    
    for (i = 0; i < n; ++i)
    {
        maxElem = fabs(matrix[i*n+i]);
        maxColIndex = i;
        
        for (j = i; j < n; ++j)
        {
            if (fabs(matrix[i*n+j]) > maxElem)// Search for max in string
            {
                maxElem = fabs(matrix[i*n+j]);
                maxColIndex = j;
            }
        }
        
        if (fabs(maxElem) < eps)
            return -1;
        
        if (maxColIndex != i) // Swap columns (i <-> max)
        {
            tempVar = var[i];
            var[i] = var[maxColIndex];
            var[maxColIndex] = tempVar;
            
            for (j = 0; j < n; ++j)
            {
                temp = matrix[j*n+i];
                matrix[j*n+i] = matrix[j*n+maxColIndex];
                matrix[j*n+maxColIndex] = temp;
            }
        }

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
            a -= matrix[i * n + j] * result[var[j]];
        
        result[var[i]] = a;
    }
    
    return 0;
}
