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
    int i, j;
    int count;
    double left, right;
    double currentLeft, currentRight, currentMiddle;
    
    Rotation(matrix, n);
    
    right = MatrixNorm(matrix, n) + 1e-10;
    left = -right;
    
    i = 0;
    currentLeft = left;
    currentRight = right;
    
    while (i < n)
    {
        while (currentRight - currentLeft > eps)
        {
            currentMiddle = 0.5 * (currentLeft + currentRight);
            
            if (n_(matrix, n, currentMiddle) < i+1)
                currentLeft = currentMiddle;
                else
                    currentRight = currentMiddle;
        }
        
        currentMiddle = 0.5 * (currentLeft + currentRight);
        count = n_(matrix, n, currentRight) - n_(matrix, n, currentLeft);
        
        for (j = 0; j < count; ++j)
            vector[i + j] = currentMiddle;
            
        i += count;
        
        currentLeft = currentMiddle;
        currentRight = right;
    }
}

int n_(double* matrix, int n, double lam)
{
    int i, res;
    double x, y, u, v, a, matrix_k, b_k1, gam;
    
    x = matrix[0] - lam;
    y = 1.0;
    res = x < 0.0 ? 1 : 0;
    
    for (i = 1; i < n; ++i)
    {
        matrix_k = matrix[i*n+i] - lam;
        b_k1 = matrix[i*n + i-1];
        
        a = fabs(b_k1 * b_k1 * y);
        
        if (fabs(x) > a)
            a = fabs(x);
        
        if (a < 1e-50)
            a = 1e-15;
        
        gam = 1e15/a;
        u = gam * (matrix_k * x - b_k1 * b_k1 * y);
        v = gam * x;
        
        if (u * x < 0.0)
            ++res;
        
        x = u;
        y = v;
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
            x = matrix[i*n+ i-1];
            y = matrix[j*n+ i-1];
            
            if (fabs(y) < 1e-100)
                continue;
            
            r = sqrt(x * x + y * y);
            
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



