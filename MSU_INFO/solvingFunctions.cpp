#include "solvingFunctions.hpp"
#include <math.h>
#include <iostream>

using namespace std; 

int solveSystem(double* matrix, double* vector, double* result, int n)
{
    int i, j, k, maxStrIndex, maxColIndex;
    double a, maxElem;
    int *var;
    
    var = new int[n];
    
    double eps = fmax(pow(10, -n*3), 1e-100);
    
    for (i = 0; i < n; ++i)
        var[i] = i;
    
    for (i = 0; i < n; ++i)
    {
        maxElem = fabs(matrix[i*n+i]);
        maxStrIndex = i;
        maxColIndex = i;
        
        for (j = i; j < n; ++j)
        {
            for (k = i; k < n; ++k)
            {
                if (fabs(matrix[j*n+k]) > maxElem)// Search for max in matrix
                {
                    maxElem = fabs(matrix[j*n+k]);
                    maxStrIndex = j;
                    maxColIndex = k;
                }
            }
        }
        
        if (fabs(maxElem) < eps)
        {
            delete []var;
            return -1;
        }
        
        if (maxStrIndex != i) // Swap strings (i <-> max)
        {
            for (j = 0; j < n; ++j)
                swap(matrix[maxStrIndex*n+j], matrix[i*n+j]);
            
            swap(vector[maxStrIndex], vector[i]);
        }
        
        swap(var[i], var[maxColIndex]);//swap variables
        
        if (maxColIndex != i) // Swap columns (i <-> max)
        {
            for (j = 0; j < n; ++j)
                swap(matrix[j*n+maxColIndex], matrix[j*n+i]);
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
    
    delete []var;
    return 0;
}
