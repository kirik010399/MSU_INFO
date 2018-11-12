//
//  calculatingManager.cpp
//  MSU_INFO
//
//  Created by Кирилл Мащенко on 20.09.2018.
//  Copyright © 2018 Кирилл Мащенко. All rights reserved.
//

#include "calculatingManager.hpp"
#include <math.h>
#include <iostream>
//#define eps 1e-100

using namespace std;

void calculateValues(double* matrix, double* vector, double left, double right, double eps, int n)
{
    Otr(matrix, n);
    
    values(matrix, n, vector, left, right, eps);
}

void values(double *matrix, int n, double *vector, double left, double right, double eps)
{
    static int k = 0;
    int c, j;
    
    c = n_(matrix, n, right) - n_(matrix, n, left);
    
//    cout<<left<<' '<<right<<' '<<k<<' '<<c<<endl;
    
    if (right - left > eps && c != 0)
    {
        values(matrix, n, vector, left, (left+right)/2, eps);
        values(matrix, n, vector, (left+right)/2, right, eps);
    }
    else if (c != 0)
    {
        for (j = 0; j < c; ++j)
            vector[k + j] = (left+right)/2;
        
        k += c;
    }//95
}


void Otr(double* a, int n)
{
    int i;
    int j;
    int k;
    double tmp1;
    double tmp2;
    
    for (i = 0; i < n - 2; ++i)
    {
        tmp1 = 0.0;
        
        for (j = i+2; j < n; ++j)
            tmp1 += a[j*n+i]*a[j*n+i];
        
        tmp2 = sqrt(a[(i+1)*n+i]*a[(i+1)*n+i] + tmp1);
        
        if (tmp2 < 1e-100)
        {
            a[(i+1)*n+i] = 0.0;
            a[(i+2)*n+i] = 0.0;
            
            continue;
        }
        
        if (tmp1 < 1e-100)
        {
            a[(i+2)*n+i] = 0.0;
            
            continue;
        }
        
        a[(i+1)*n+i] -= tmp2;
        
        tmp1 = 1.0/sqrt(a[(i+1)*n+i] * a[(i+1)*n+i] + tmp1);
        
        for (j = i + 1; j < n; ++j)
            a[j*n+i] *= tmp1;
        
        for (j = i+1; j < n; ++j)
        {
            tmp1 = 0.0;
            for (k = i+1; k < n; k++)
                tmp1 += a[j*n+k] * a[k*n+i];
            a[i * n + j] = tmp1;
        }
        
        tmp1 = 0.0;
        for (j = i + 1; j < n; ++j)
            tmp1 += a[i*n+j] * a[j*n+i];
        tmp1 *= 2.0;
        
        for (j = i+1; j < n; ++j)
            a[i*n+j] = 2.0 * a[i*n+j] - tmp1 * a[j*n+i];
        
        for (j = i+1; j < n; ++j)
            for (k = i+1; k < n; ++k)
                a[j*n+k] -= a[i*n+j] * a[k*n+i] + a[i*n+k] * a[j*n+i];
        
        a[(i+1)*n+i] = tmp2;
        a[i*n + i+1] = tmp2;
        
        for (j = i + 2; j < n; ++j)
        {
            a[j*n+i] = 0.0;
            a[i*n+j] = 0.0;
        }
    }
}

int n_(double* matrix, int n, double lam)
{
    int i;
    int res;
    double elem;
    
    elem = matrix[0] - lam;
    
    if (elem < 0)
        res = 1;
    else
        res = 0;
    
    for (i = 1; i < n; ++i)
    {
        elem = matrix[i*n+i] - lam - matrix[i*n + i-1] * matrix[(i-1)*n+i]/elem;
        
        if (elem < 0)
            ++res;
    }
    
    return res;
}
