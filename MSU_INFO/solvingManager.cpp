//
//  invertingManager.cpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 20.09.2018.
//  Copyright © 2018 Кирилл Мащенко. All rights reserved.
//

#include "solvingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std; 

int solveSystem(double* matrix, double* vector, double* result, int n)
{
    int i, j, k, b;
    double a;

    double eps = max(pow(10, -n*3), 1e-100);
    
    for (j = 0; j < n; ++j)
    {
        a = matrix[j*n+j];
        b = j;
        
        for (i = j+1; i < n; ++i)
        {
            if (fabs(matrix[i*n+j]) > fabs(a))
            {
                a = matrix[i*n+j];
                b = i;
            }
        }
        
        if (fabs(a) < eps) 
            return 0;
        
        if (b != j)
        {
            for (i = j; i < n; ++i)
                swap(matrix[b*n+i], matrix[j*n+i]);
            
            swap(vector[b], vector[j]);
        }
        
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
    
    return 1;
}
