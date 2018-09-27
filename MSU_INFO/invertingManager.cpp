//
//  invertingManager.cpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 20.09.2018.
//  Copyright © 2018 Кирилл Мащенко. All rights reserved.
//

#include "invertingManager.hpp"
#include <math.h>

using namespace std; 

int invertMatrix(double* matrix, double* inverseMatrix, int n)
{
    int i;
    int j;
    int k;
    double a;
    double b;
    
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
        a = 0.0;
        
        for (j = i + 1; j < n; j++)
            a += matrix[j*n+i] * matrix[j*n+i];//(12)
        
        b = sqrt(a + matrix[i*n+i] * matrix[i*n+i]);//(13)
        
        if (b < 1e-100)
            return 0;
        
        matrix[i*n+i] -= b;//(14)
        
        a = sqrt(matrix[i*n+i] * matrix[i*n+i] + a);//(15)
        
        if (a < 1e-100)
        {
            matrix[i*n+i] += b;
            continue;
        }
        
        a = 1.0/a;//(16)
        
        for (j = i; j < n; ++j)
            matrix[j*n+i] *= a; //(16), R is keeped in up triangle, Q isn't keeped
        
        for (k = i + 1; k < n; ++k)
        {
            a = 0.0;
            for (j = i; j < n; ++j)
                a += matrix[j*n+i] * matrix[j*n+k];
            
            a *= 2.0;
            for (j = i; j < n; ++j)
                matrix[j*n+k] -= a * matrix[j*n+i];
        }
        
        for (k = 0; k < n; ++k)
        {
            a = 0.0;
            for (j = i; j < n; ++j)
                a += matrix[j*n+i] * inverseMatrix[k*n+j];
            
            a *= 2.0;
            for (j = i; j < n; ++j)
                inverseMatrix[k*n+j] -= a * matrix[j*n+i];
        }
        
        matrix[i*n+i] = b;
    }
    
    for (i = 0; i < n; ++i)
    {
        for (j = i + 1; j < n; ++j)
        {
            swap(inverseMatrix[i*n+j], inverseMatrix[j*n+i]);
        }
    }
    
    for (k = 0; k < n; ++k)
    {
        for (i = n - 1; i >= 0; --i)
        {
            a = inverseMatrix[i*n+k];
            
            for (j = i + 1; j < n; ++j)
                a -= matrix[i*n+j] * inverseMatrix[j*n+k];
            
            inverseMatrix[i*n+k] = a/matrix[i*n+i];
        }
    }
    
    return 1;
}
