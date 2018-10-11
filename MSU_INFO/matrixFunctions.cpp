//
//  matrixFunctions.cpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 20.09.2018.
//  Copyright © 2018 Кирилл Мащенко. All rights reserved.
//

#include "matrixFunctions.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

double func(int i, int j)
{
    return i+j==999?1:0;
}

int getElem(int i, int j)
{
    if (i < j)
        return j*(j+1)/2+i;
    else
        return i*(i+1)/2+j;
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
                if (fscanf(fin, "%lf", &matrix[getElem(i, j)]) != 1)
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
                matrix[getElem(i, j)] = func(i, j);
            }
        }
    }
    
    return 0;
}

void printMatrix(double* matrix, int n, int m)
{
    int i, j;
    int min_ = fmin(n,m);
    
    for (i = 0; i < min_; ++i)
    {
        for (j = 0; j < min_; ++j)
        {
            printf("%f ", matrix[getElem(i, j)]);
        }
        printf("\n");
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
                a += matrix[getElem(i, k)] * inverseMatrix[getElem(k, j)];
            
            if (i == j)
                a -= 1.0;
            
            sum += fabs(a);
        }
        
        if (sum > max)
            max = sum;
    }
    
    return max;
}
