//
//  invertingManager.cpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 20.09.2018.
//  Copyright © 2018 Кирилл Мащенко. All rights reserved.
//

#include "invertingManager.hpp"
#include <math.h>

int invertMatrix(double* matrix, double* inverseMatrix, int n)
{
    int i;
    int j;
    int k;
    double var1;
    double var2;
    
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
        var1 = 0.0;
        
        for (j = i + 1; j < n; j++)
        {
            var1 += matrix[j*n+i] * matrix[j*n+i];
        }
        
        var2 = sqrt(var1 + matrix[i*n+i] * matrix[i*n+i]);
        
        if (var2 < 1e-100)
            return 0;
        
        matrix[i*n+i] -= var2;
        
        var1 = sqrt(var1 + matrix[i*n+i] * matrix[i*n+i]);
        
        if (var1 < 1e-100)
        {
            matrix[i*n+i] += var2;
            continue;
        }
        
        var1 = 1.0 / var1;
        
        for (j = i; j < n; ++j)
        {
            matrix[j*n+i] *= var1;
        }
        
        for (k = i + 1; k < n; ++k)
        {
            var1 = 0.0;
            for (j = i; j < n; ++j)
            {
                var1 += matrix[j*n+i] * matrix[j*n+k];
            }
            
            var1 *= 2.0;
            for (j = i; j < n; ++j)
            {
                matrix[j*n+k] -= var1 * matrix[j*n+i];
            }
        }
        
        for (k = 0; k < n; ++k)
        {
            var1 = 0.0;
            for (j = i; j < n; ++j)
            {
                var1 += matrix[j*n+i] * inverseMatrix[k*n+j];
            }
            
            var1 *= 2.0;
            for (j = i; j < n; ++j)
            {
                inverseMatrix[k*n+j] -= var1 * matrix[j*n+i];
            }
        }
        
        matrix[i*n+i] = var2;
    }
    
    for (i = 0; i < n; ++i)
    {
        for (j = i + 1; j < n; ++j)
        {
            var1 = inverseMatrix[i*n+j];
            inverseMatrix[i*n+j] = inverseMatrix[j*n+i];
            inverseMatrix[j*n+i] = var1;
        }
    }
    
    for (k = 0; k < n; ++k)
    {
        for (i = n - 1; i >= 0; --i)
        {
            var1 = inverseMatrix[i*n+k];
            for (j = i + 1; j < n; ++j)
            {
                var1 -= matrix[i*n+j] * inverseMatrix[j*n+k];
            }
            
            inverseMatrix[i*n+k] = var1/matrix[i*n+i];
        }
    }
    
    return 1;
}
