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

double func(int i, int j, int n)
{
    if (i == n-1)
        return j+1;
    if (j == n-1)
        return i+1;
    if (i == j)
        return 1;
    return 0; 
}

int enterMatrix(double* matrix, int n, FILE* fin)
{
    int i, j;
    
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
                matrix[i*n+j] = func(i, j, n);
            }
        }
    }
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            if (!(fabs(matrix[i*n+j] - matrix[j*n+i]) < 1e-100))
                return -1;
        }
    }
    
    return 0;
}

void printVector(double* vector, int k)
{
    cout<<vector[k-1]<<endl;
}

pair<double, double> residualNorm(double* matrix, double* vector, int n)
{
    double inv1, inv2;
    int i, j;
    pair<double, double> p;
    
    inv1 = 0.0;
    inv2 = 0.0;
    
    for (i = 0; i < n; ++i)
    {
        inv1 += vector[i] - matrix[i*n+i];
        inv2 += vector[i] * vector[i];
        
        for (j = 0; j < n; ++j)
            inv2 -= matrix[i*n+j] * matrix[i*n+j];
    }
    
    p.first = inv1;
    p.second = inv2;
    
    return p;
}
