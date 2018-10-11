#include "solvingFunctions.hpp"
#include <math.h>
#include <iostream>
#include "matrixFunctions.hpp"

using namespace std; 

int solveSystem(double* matrix, double* vector, double* result, int n)
{
    int i, j, k;
    double a;
    
    int maxStrInd, maxColInd;

    double eps = fmax(pow(10, -n*3), 1e-100);
    
    for (j = 0; j < n; ++j)
    {
        a = fabs(matrix[j*n+j]);
        maxStrInd = j;
        maxColInd = j;
        
        for (i = j; i < n; ++i)
        {
            for (k = j; k < n; ++k)
            {
                if (fabs(matrix[i*n+k]) > a)// Search for max in column
                {
                    a = matrix[i*n+j];
                    maxStrInd = i;
                    maxColInd = j;
                }
            }
        }
        
        cout<<maxStrInd<<" "<<maxColInd<<endl;
        
        for (int p = 0; p < n; ++p)
        {
            for (int q = 0; q < n ++q)
                cout<<matrix[p*n+q]<<' ';
            cout<<endl;
        }
        
        if (fabs(a) < eps) 
            return -1;
        
        if (maxStrInd != j) // Swap strings (j <-> max)
        {
            for (i = j; i < n; ++i)
                swap(matrix[maxStrInd*n+i], matrix[maxStrInd*n+i]);
            
            swap(vector[maxStrInd], vector[j]);
        }
        
        if (maxColInd != j) // Swap columns (j <-> max)
        {
            for (i = j; i < n; ++i)
                swap(matrix[i*n+maxColInd], matrix[i*n+j]);
        }
    }
    
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
