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
    int i;
    int j;
    int k;
    double a;
    double b;
    double *d;

    double eps = fmax(pow(10, -n*3), 1e-100);
    
    d = new double [n];
    
    for (i = 0; i < n; ++i)
    {
        d[i] = 0;
        
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

        if (b < eps)
        {
            delete[]d;
            return 0;
        }//det = 0;

        d[i] = matrix[i*n+i] - b;
        
        for (j = i+1; j < n; ++j)
            d[j] = matrix[j*n+i]; //(14)
        
        a = sqrt(d[i] * d[i] + a);//(15)

        if (a < eps)
            continue;

        for (j = i; j < n; ++j)
            d[j] /= a; //(16)

        for (k = i + 1; k < n; ++k)
        {
            a = 0.0;
            for (j = i; j < n; ++j)
                a += d[j] * matrix[j*n+k];

            a*=2.0;//from formula
            for (j = i; j < n; ++j)
                matrix[j*n+k] -= a * d[j];
        }

        for (k = 0; k < n; ++k)
        {
            a = 0.0;
            for (j = i; j < n; ++j)
                a += d[j] * inverseMatrix[j*n+k];

            a*=2.0;//from formula
            for (j = i; j < n; ++j)
                inverseMatrix[j*n+k] -= a * d[j];
        }

        matrix[i*n+i] = b;//on diag R
    }
    
    //R in up triangle, Q in down triangle and in d

    for (k = 0; k < n; ++k)
    {
        for (i = n - 1; i >= 0; --i)
        {
            a = inverseMatrix[i*n+k];

            for (j = i + 1; j < n; ++j)
                a -= matrix[i*n+j] * inverseMatrix[j*n+k];

            inverseMatrix[i*n+k] = a/matrix[i*n+i];
        }
    }//Reverse Gauss
    
    delete []d;
    return 1;
}
