//
//  matrixUtils.cpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 20.09.2018.
//  Copyright © 2018 Кирилл Мащенко. All rights reserved.
//

#include "matrixUtils.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

double func(int i, int j)
{
    return i+j==999?1:0;
}

int enterMatrix(double* matrix, int n, FILE* fin)
{
    int i;
    int j;
    
    if (fin)
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                if (fscanf(fin, "%lf", &matrix[i*n+j]) != 1)
                    return -1;
            }
        }
    }
    else
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                matrix[i*n+j] = func(i, j);
            }
        }
    }
    
    return 0;
}

void printMatrix(double* matrix, int n, int m)
{
    int i;
    int j;
    int min_ = fmin(n,m);
    
    for (i = 0; i < min_; ++i)
    {
        for (j = 0; j < min_; ++j)
        {
            cout<<matrix[i*n+j]<<' ';
        }
        cout<<endl;
    }
}

double residualNorm(double* matrix, double* inverseMatrix, int n)
{
    int i;
    int j;
    int k;
    double a;
    double sum = 0.0;
    double max = 0.0;
        
    for (i = 0; i < n; ++i)
    {
        sum = 0.0;
        
        for (j = 0; j < n; ++j)
        {
            a = 0.0;
            
            for (k = 0; k < n; ++k)
                a += matrix[i*n+k] * inverseMatrix[k*n+j];
            
            if (i == j)
                a -= 1.0;
            
            sum += fabs(a);
        }
        
        if (sum > max)
            max = sum;
    }
    
    return max;
}
