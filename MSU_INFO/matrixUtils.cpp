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
                matrix[i*n+j] = func(i, j);
            }
        }
    }
    
    return 0;
}

void printVector(double* vector, int n, int m)
{
    int i;
    int min_ = fmin(n,m);
    
    for (i = 0; i < min_; ++i)
        cout<<vector[i]<<' ';
    
    cout<<endl;
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
        inv1 -= matrix[i*n+i];
        for (j = 0; j < n; ++j)
            inv2 -= matrix[i*n+j] * matrix[j*n+i];
        
        inv1 += vector[i];
        inv2 += vector[i] * vector[i];
    }
    
    p.first = inv1;
    p.second = inv2;
    
    return p;
}
