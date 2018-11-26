#include "calculatingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std;

void calculateValues(double* matrix, double* vector, double eps, int n)
{
    int i, j, i1, j1;
    double x, y;
    double cosPhi, sinPhi;
    
    for (i = 0; i < n; ++i)
        vector[i] = 0.0;
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if (i != j)
                vector[i] += matrix[i*n+j] * matrix[i*n+j];
        }
    }//vector = b, sum of squares not diag elements
    
    while (VectorNorm(vector, n) > eps)
    {
        i1 = 0;
        
        for (i = 0; i < n; ++i)
        {
            if (fabs(vector[i1]) < fabs(vector[i]))
                i1 = i;
        }
        
        j1 = (i1 > 0 ? 0 : 1);
        
        for (j = 0; j < n; ++j)
        {
            if (j != i1 && fabs(matrix[i1*n+j1]) < fabs(matrix[i1*n+j]))
                j1 = j;
        }
        
        x = -2.0 * matrix[i1*n+j1];//p.89, up
        y = matrix[i1*n+i1] - matrix[j1*n+j1];//p.89, up
        
        if (fabs(y) < 1e-100)
        {
            cosPhi = sqrt(2)/2;
            sinPhi = sqrt(2)/2;
        }
        else
        {
            cosPhi = 1/sqrt(2) * sqrt(1.0 + fabs(y) / sqrt(x*x+y*y));
            sinPhi = 0.5 * (x*y > 0 ? 1.0: -1.0) * fabs(x) / (cosPhi * sqrt(x*x+y*y));
        }//p.89, (8)
        
        for (j = 0; j < n; ++j)
        {
            x = matrix[i1*n+j];
            matrix[i1*n+j] = x * cosPhi - matrix[j1*n+j] * sinPhi;
            matrix[j1*n+j] = x * sinPhi + matrix[j1*n+j] * cosPhi;
        }//*Tij, p.87, only i1 and j1 strings
        
        for (j = 0; j < n; ++j)
        {
            if (j != i1 && j != j1)
            {
                matrix[j*n+i1] = matrix[i1*n+j];
                matrix[j*n+j1] = matrix[j1*n+j];
            }
        }//from simmetrical, don't want to change i1 and j1 columns
        
        x = matrix[i1*(n+1)];
        matrix[i1*n+i1] = x * cosPhi - matrix[i1*n+j1] * sinPhi;
        
        y = matrix[j1*n+i1];
        matrix[j1*n+j1] = y * sinPhi + matrix[j1*(n+1)] * cosPhi;
        
        matrix[i1*n+j1] = 0;
        matrix[j1*n+i1] = 0;
        
        vector[i1] = 0;
        
        for (i = 0; i < n; ++i)
        {
            if (i != i1)
                vector[i1] += matrix[i*n+i1] * matrix[i*n+i1];
        }
        
        vector[j1] = 0.0;
        
        for (j = 0; j < n; ++j)
        {
            if (j != j1)
                vector[j1] += matrix[j*n+j1] * matrix[j*n+j1];
        }
    }
    
    //now vector is result
    for (i = 0; i < n; ++i)
        vector[i] = matrix[i*n+i];
}

double VectorNorm(double* vector, int n)
{
    int i;
    double res = 0;
    
    for (i = 0; i < n; ++i)
        res += vector[i] * vector[i];
    
    return sqrt(res);
}
