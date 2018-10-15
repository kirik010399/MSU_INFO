//
//  invertingManager.cpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 20.09.2018.
//  Copyright © 2018 Кирилл Мащенко. All rights reserved.
//

#include "invertingManager.hpp"
#include <math.h>
#include <iostream>
//#define eps 1e-100

using namespace std; 

int invertMatrix(double* matrix, double* inverseMatrix, int n)
{
    int i, j, k, notNullStrInd;
    double a;
    
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
        a = fabs(matrix[i*n+i]);
        
        if (a < eps)
        {
            notNullStrInd = i;

            for (j = i; j < n; ++j)
            {
                if (fabs(matrix[j*n+i]) > a)
                {
                    a = fabs(matrix[j*n+i]);
                    notNullStrInd = j;
                    break;
                }
            }
            
            if (a < eps)
                return -1;

            if (notNullStrInd != i) // Swap strings (i<-> notNull)
            {
                for (j = 0; j < n; ++j)
                    swap(matrix[notNullStrInd*n+j], matrix[i*n+j]);
                
                for (j = 0; j < n; ++j)
                    swap(inverseMatrix[notNullStrInd*n+j], inverseMatrix[i*n+j]);
            }
        }
        
        for (j = 0; j < n; ++j)
        {
            if (i != j)
            {
                a = matrix[j*n+i]/matrix[i*n+i];
                
                for (k = i; k < n; ++k)
                    matrix[j*n+k] -= matrix[i*n+k] * a;
                
                for (k = 0; k < n; ++k)
                    inverseMatrix[j*n+k] -= inverseMatrix[i*n+k] * a;
            }
        }
    }
    
    return 0;
}
