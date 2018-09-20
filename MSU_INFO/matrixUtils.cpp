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
    return 1.0/(i+j+1.0);
}

int enterMatrix(double* a, int n, FILE* fin)
{
    int i;
    int j;
    
    if (fin)
    {
        for (i = 0; i < n; ++i)
        {
            for (j = 0; j < n; ++j)
            {
                if (fscanf(fin, "%lf", &a[i*n+j]) != 1)
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
                a[i*n+j] = func(i, j);
            }
        }
    }
    
    return 0;
}

void printMatrix(double* a, int n)
{
    int i;
    int j;
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            cout<<a[i*n+j]<<' ';
        }
        cout<<endl;
    }
}
