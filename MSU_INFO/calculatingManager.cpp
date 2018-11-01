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
#define eps 1e-10

using namespace std;

void calculateValues(double* matrix, double* vector, int n)
{
    double left, right;
    
    Rotation(matrix, n);
    
    right = MatrixNorm(matrix, n) + eps;
    left = -right;
    
    values(matrix, n, vector, left, right);
}

void values(double *matrix, int n, double *vector, double left, double right)
{
    static int k = 0;
    int c, j;
    
    c = n_(matrix, n, right) - n_(matrix, n, left);
    
    cout<<left<<' '<<right<<' '<<k<<' '<<c<<endl;
    
    if (right - left > eps && c != 0)
    {
        values(matrix, n, vector, left, (left+right)/2);
        values(matrix, n, vector, (left+right)/2, right);
    }
    else if (c != 0)
    {
        for (j = 0; j < c; ++j)
            vector[k + j] = (left+right)/2;
        
        k += c;
    }//95
}

int n_(double* matrix, int n, double lam)
{
    int i, res;
    double x, y, u, v, a, maxx, b, gam;
    
    x = matrix[0] - lam;
    y = 1.0;
    
    if (x*y < 0)
        res = 1;
    else
        res = 0;
    
    for (i = 1; i < n; ++i)
    {
        a = matrix[i*n+i] - lam;
        b = matrix[i*n + i-1];
        
        maxx = fabs(b*b*y);
        
        if (fabs(x) > maxx)
            maxx = fabs(x);
        
        gam = (1/eps)/maxx;
        
        u = gam * (a*x - b*b*y);
        v = gam * x;
        
        if (u*x < 0.0)
            ++res;
        
        x = u;
        y = v;//97
    }
    
    return res;
}

void Rotation(double* matrix, int n)
{
    int i, j, k;
    double x, y, r, s, matrix_ii, matrix_ij, matrix_ji, matrix_jj, cosPhi, sinPhi;
    
    for (i = 1; i < n-1; ++i)
    {
        for (j = i+1; j < n; ++j)
        {
            x = matrix[i*n + i-1];
            y = matrix[j*n + i-1];
            
            if (fabs(y) < 1e-100)
                continue;
            
            r = sqrt(x*x+y*y);
            
            if (r < 1e-100)
                continue;
            
            cosPhi = x/r;
            sinPhi = -y/r;
            
            matrix[i*n + i-1] = matrix[(i-1)*n+i] = r;
            matrix[j*n + i-1] = matrix[(i-1)*n+j] = 0.0;
            
            for (k = i+1; k < n; ++k)
            {
                if (k == j)
                    continue;
                
                x = matrix[i*n+k];
                y = matrix[j*n+k];
                matrix[k*n+i] = matrix[i*n+k] = x * cosPhi - y * sinPhi;
                matrix[k*n+j] = matrix[j*n+k] = x * sinPhi + y * cosPhi;
            }
            
            x = matrix[i*n+i];
            y = matrix[j*n+j];
            r = matrix[i*n+j];
            s = matrix[j*n+i];
            
            matrix_ii = x * cosPhi - s * sinPhi;
            matrix_ji = x * sinPhi + s * cosPhi;
            matrix_ij = r * cosPhi - y * sinPhi;
            matrix_jj = r * sinPhi + y * cosPhi;
            
            matrix[i*n+i] = matrix_ii * cosPhi - matrix_ij * sinPhi;
            matrix[j*n+i] = matrix_ii * sinPhi + matrix_ij * cosPhi;
            matrix[i*n+j] = matrix[j*n+i];
            matrix[j*n+j] = matrix_ji * sinPhi + matrix_jj * cosPhi;
        }
    }
}

double MatrixNorm(double* matrix, int n)
{
    int i, j;
    double sum, res;
    
    res = 0.0;
    for (i = 0; i < n; ++i)
    {
        sum = 0.0;
        for (j = 0; j < n; ++j)
            sum += fabs(matrix[i*n+j]);
        
        if (res < sum)
            res = sum;
    }
    
    return res;
}



