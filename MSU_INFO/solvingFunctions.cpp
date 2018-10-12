#include "solvingFunctions.hpp"
#include <math.h>
#include <iostream>
#include "matrixFunctions.hpp"

using namespace std; 

int solveSystem(double* matrix, double* vector, double* result, int n)
{
    int i, j, k;
    double a;
    int *var;
    
    var = new int[n];
    
    int maxStrInd, maxColInd;

    double eps = fmax(pow(10, -n*3), 1e-100);
    
    for (i = 0; i < n; ++i)
        var[i] = i;
    
    for (i = 0; i < n; ++i)
    {
        a = fabs(matrix[i*n+i]);
        maxStrInd = i;
        maxColInd = i;
        
        for (j = i; j < n; ++j)
        {
            for (k = i; k < n; ++k)
            {
                if (fabs(matrix[j*n+k]) > a)// Search for max in matrix
                {
                    a = matrix[j*n+k];
                    maxStrInd = j;
                    maxColInd = k;
                }
            }
        }
        
//        cout<<endl<<maxStrInd<<" "<<maxColInd<<endl;
//        
//        for (int p = 0; p < n; ++p)
//        {
//            for (int q = 0; q < n; ++q)
//                cout<<matrix[p*n+q]<<' ';
//            cout<<' '<<vector[p];
//            cout<<endl;
//        }
        
        if (fabs(a) < eps)
        {
            delete []var;
            return -1;
        }
        
        if (maxStrInd != i) // Swap strings (j <-> max)
        {
            for (j = 0; j < n; ++j)
                swap(matrix[maxStrInd*n+j], matrix[i*n+j]);
            
            swap(vector[maxStrInd], vector[i]);
        }
//
//        cout<<endl;
//        for (int p = 0; p < n; ++p)
//        {
//            for (int q = 0; q < n; ++q)
//                cout<<matrix[p*n+q]<<' ';
//            cout<<' '<<vector[p];
//            cout<<endl;
//        }
        
        swap(var[i], var[maxColInd]);//swap variables

        if (maxColInd != j) // Swap columns (j <-> max)
        {
            for (j = 0; j < n; ++j)
                swap(matrix[j*n+maxColInd], matrix[j*n+i]);
        }
        
//        cout<<endl;
//        for (int p = 0; p < n; ++p)
//        {
//            for (int q = 0; q < n; ++q)
//                cout<<matrix[p*n+q]<<' ';
//            cout<<' '<<vector[p];
//            cout<<endl;
//        }
        
        for(j = 0; j < n; ++j) // Subtraction from all lines
        {
            if (j != i)
            {
                a = matrix[j*n+i]/matrix[i*n+i];
                
                for(k = i; k < n; ++k)
                    matrix[j*n+k] -= a*matrix[i*n+k];
                
                vector[j] -= a*vector[i];
            }
        }
    }
    
    for (i = 0; i < n; ++i)
        result[var[i]] = vector[i]/matrix[i*n+i];
    
    delete []var;
    return 0;
}
