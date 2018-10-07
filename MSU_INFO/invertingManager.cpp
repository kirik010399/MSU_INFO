#include "invertingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std; 

int invertMatrix(double* matrix, double* inverseMatrix, int n)
{
    int i, j, k, maxElemIndex;
    double a, maxElem;
    
    double eps = fmax(pow(10, -n*3), 1e-100);
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if (i == j)
                inverseMatrix[i*n+j] = 1;
            else
                inverseMatrix[i*n+j] = 0;
        }
    }

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
        
        for (j = 0; j < n; ++j)
            swap (matrix[i*n+j], matrix[maxElemIndex*n+j]);
        
        for (j = 0; j < n; ++j)
            swap (inverseMatrix[i*n+j], inverseMatrix[maxElemIndex*n+j]);
        
        if (fabs(matrix[i*n+i]) < eps)
            return 0;
        
        a = 1.0/matrix[i*n+i];
        
        for (j = i; j < n; ++j)
            matrix[i*n+j] *= a;
        
        for (j = 0; j < n; ++j)
            inverseMatrix[i*n+j] *= a;
        
        for (j = i+1; j < n; ++j)
        {
            a = matrix[j*n+i];
            
            for (k = i; k < n; ++k)
                matrix[j*n+k] -= matrix[i*n+k] * a;
            
            for (k = 0; k < n; ++k)
                inverseMatrix[j*n+k] -= inverseMatrix[i*n+k] * a;
        }
    }
    
    for (k = 0; k < n; ++k)
    {
        for (i = n - 1; i >= 0; --i)
        {
            a = inverseMatrix[i*n+k];
            
            for (j = i+1; j < n; ++j)
                a -= matrix[i*n+j] * inverseMatrix[j*n+k];
            
            inverseMatrix[i*n+k] = a;
        }
    }
    
    return 1;
}
