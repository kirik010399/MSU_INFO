#include "calculatingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std;

void calculateValues(double* matrix, double* vector, double eps, int n)
{
    int i, j, iNil, jNil;
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
    }
    
    while (VectorNorm(vector, n) > eps)
    {
        iNil = 0;
        
        for (i = 0; i < n; ++i)
            if (fabs(vector[iNil]) < fabs(vector[i]))
                iNil = i;
        
        jNil = (iNil > 0 ? 0 : 1);
        
        for (j = 0; j < n; ++j)
            if (j != iNil)
                if (fabs(matrix[iNil*n+jNil]) < fabs(matrix[iNil*n+j]))
                    jNil = j;
        
        x = -2.0 * matrix[iNil*n+jNil];
        y = matrix[iNil*n+iNil] - matrix[jNil*n+jNil];
        
        if (fabs(y) < 1e-100)
        {
            cosPhi = sqrt(2)/2;
            sinPhi = sqrt(2)/2;
        }
        else
        {
            cosPhi = sqrt(2)/2 * sqrt(1.0 + fabs(y) / sqrt(x * x + y * y));
            sinPhi = 0.5 * (x * y > 0 ? 1.0 : -1.0) * fabs(x) / (cosPhi * sqrt(x * x + y * y));
        }
        
        for (j = 0; j < n; ++j)
        {
            x = matrix[iNil*n+j];
            matrix[iNil*n+j] = x * cosPhi - matrix[jNil*n+j] * sinPhi;
            matrix[jNil*n+j] = x * sinPhi + matrix[jNil*n+j] * cosPhi;
        }
        
        for (j = 0; j < n; ++j)
        {
            if (j != iNil && j != jNil)
            {
                matrix[j*n+iNil] = matrix[iNil*n+j];
                matrix[j*n+jNil] = matrix[jNil*n+j];
            }
        }
        
        x = matrix[iNil * (n + 1)];
        matrix[iNil*n+iNil] = x * cosPhi - matrix[iNil*n+jNil] * sinPhi;
        
        y = matrix[jNil*n+iNil];
        matrix[jNil*n+jNil] = y * sinPhi + matrix[jNil*(n+1)] * cosPhi;
        
        matrix[iNil*n+jNil] = 0.0;
        matrix[jNil*n+iNil] = 0.0;
        
        vector[iNil] = 0.0;
        for (i = 0; i < n; ++i)
            if (i != iNil)
                vector[iNil] += matrix[i*n+iNil] * matrix[i*n+iNil];
        
        vector[jNil] = 0.0;
        for (j = 0; j < n; ++j)
            if (j != jNil)
                vector[jNil] += matrix[j*n+jNil] * matrix[j*n+jNil];
        }
    
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
