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
    int i, j, k;
    double a;
    
    double eps = fmax(pow(10, -n*3), 1e-100);
    
    for (i = 0; i < n; ++i)
    {
        if (fabs(matrix[i*n+i]) < eps)
            return -1;
        
        a = 1.0/matrix[i*n+i];
        
        for (j = i; j < n; ++j)
            matrix[i*n+j] *= a;
        
        for (j = 0; j < n; ++j)
            inverseMatrix[i*n+j] *= a;
        
        for (j = 0; j < n; ++j)
        {
            if (i != j)
            {
                a = matrix[j*n+i];
                
                for (k = i; k < n; ++k)
                    matrix[j*n+k] -= matrix[i*n+k] * a;
                
                for (k = 0; k < n; ++k)
                    inverseMatrix[j*n+k] -= inverseMatrix[i*n+k] * a;
            }
        }
    }
    
    return 0;
}
