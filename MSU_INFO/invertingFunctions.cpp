//
//  invertingManager.cpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 20.09.2018.
//  Copyright © 2018 Кирилл Мащенко. All rights reserved.
//

#include "invertingFunctions.hpp"
#include <math.h>
#include "matrixFunctions.hpp"
//#define eps 1e-100

int invertMatrix(double* matrix, double* inverseMatrix, double *vector, int n)
{
    int i, j, k;
    double a;

    double eps = fmax(pow(10, -n*3), 1e-100);
    
    for (i = 0; i < n; ++i)
        for (j = 0; j < n; ++j)
            inverseMatrix[getElem(i, j)] = double(i == j);
   
    for (i = 0; i < n; ++i)
    {
        for (j = i; j < n; ++j)
        {
            a = matrix[getElem(j, i)];
            
            for (k = 0; k < i; ++k)
                a -= inverseMatrix[getElem(i, k)]*inverseMatrix[getElem(j, k)]*vector[k];
            
            if (i == j)
            {
                if (a < 0)
                {
                    a = -a;
                    vector[i] = -1.0;
                }
                else
                    vector[i] = 1.0;
                
                printf("%lf ", a); 
                if (fabs(a) < eps)
                    return -1;
                
                a = sqrt(a);
                
                inverseMatrix[getElem(i, i)] = a;
            }
            else
                inverseMatrix[getElem(j, i)] = a/(inverseMatrix[getElem(i, i)]*vector[i]);
        }
    }
    
    for (i = 0; i < n; ++i)
    {
        for (j = i; j >= 0; --j)
        {
            if (i == j)
                a = 1;
            else
                a = 0;
            
            for (k = j + 1; k <= i; ++k)
                a -= matrix[getElem(i, k)] * inverseMatrix[getElem(j, k)];
            
            matrix[getElem(i, j)] = a / inverseMatrix[getElem(j, j)];
        }
    }
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            a = 0.0;
            
            for (k = (i > j) ? i : j; k < n; ++k)
                a += vector[k] * matrix[getElem(k, j)] * matrix[getElem(k, i)];
            
            inverseMatrix[getElem(i, j)] = a;
        }
    }
    
    return 0;
}
