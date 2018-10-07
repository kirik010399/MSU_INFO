#include "solvingFunctions.hpp"
#include <math.h>
#include <iostream>

using namespace std; 

int solveSystem(double* matrix, double* vector, double* result, int n)
{
    int i, j, k, b;
    double a;

    double eps = fmax(pow(10, -n*3), 1e-100);
    
    for (j = 0; j < n; ++j)
    {
        a = matrix[j*n+j];
        b = j;
        
        for (i = j+1; i < n; ++i)
        {
            if (fabs(matrix[i*n+j]) > fabs(a))// Search for max in column
            {
                a = matrix[i*n+j];
                b = i;
            }
        }
        
        if (fabs(a) < eps) 
            return -1;
        
        if (b != j) // Swap strings (j <-> max)
        {
            for (i = j; i < n; ++i)
                swap(matrix[b*n+i], matrix[j*n+i]);
            
            swap(vector[b], vector[j]);
        }
    }//main through column
    
    for (i = 0; i < n; ++i)
    {
        a = matrix[i*n+i];
        b = i;
        
        for (j = i+1; j < n; ++j) // Search for max in line
        {
            if (fabs(matrix[i*n+j]) > fabs(a))
            {
                a = matrix[i*n+j];
                b = j;
            }
        }
        
        if (fabs(a) < eps) // det = 0
            return -1;
        
        if (b != i) // Swap columns (i <-> max)
        {
            for (j = 0; j < n; ++j)
                swap(matrix[j*n+b], matrix[j*n+i]);
            
            swap(vector[b], vector[i]);
        }
    }//main through string
    
    for (j = 0; j < n; ++j)
    {
        for(i = 0; i < n; ++i)
        {
            if (i != j && fabs(matrix[i*n+j]) > eps)
            {
                a = matrix[i*n+j]/matrix[j*n+j];
                
                for(k = j; k < n; ++k)
                    matrix[i*n+k] -= a*matrix[j*n+k];
                
                vector[i] -= a*vector[j];
            }
        }
    }
    
    for (i = 0; i < n; ++i)
        result[i] = vector[i]/matrix[i*n+i];
    
    return 0;
}
