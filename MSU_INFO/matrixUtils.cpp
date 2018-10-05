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
    return 1.0/(1.0+i+j);
}

int enterData(double* matrix, double *vector, int n, FILE* fin)
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
            
            if (fscanf(fin, "%lf", &vector[i]) != 1)
                return -1;
        }
    }
    else
    {
        for (i = 0; i < n; ++i)
        {
            vector[i] = 0;
            
            for (j = 0; j < n; ++j)
            {
                matrix[i*n+j] = func(i, j);
                
                if (j % 2 == 0)
                    vector[i] += matrix[i*n+j];
            }
        }
    }
    
    return 0;
}

void printResult(double* result, int n, int m)
{
    int i;
    int min_ = min(n,m);
    
    for (i = 0; i < min_; ++i)
        cout<<result[i]<<' ';
    
    cout<<endl;
}

double residualNorm(double* matrix, double* vector, double* result, int n)
{
    int i, j;
    double res = 0;
    double a;
    
    for (i = 0; i < n; ++i)
    {
        a = 0.0;
        
        for (j = 0; j < n; ++j)
            a += matrix[i*n+j] * result[j];
        
        a -= vector[i];
        
        res += a*a;
    }
    
    return sqrt(res);
}

double errorFunction(double *result, int n)
{
    double error = 0;
    int i;
    
    for (i = 0; i < n; ++i)
    {
        if (i % 2)
            error += result[i]*result[i];
        else
            error += (result[i]-1)*(result[i]-1);
    }
    
    return sqrt(error);
}
