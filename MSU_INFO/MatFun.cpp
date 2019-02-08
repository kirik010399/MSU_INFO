#include "MatFun.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

double func(int i, int j, int n)  {
    if (i == n-1)
        return j+1;
    if (j == n-1)
        return i+1;
    if (i == j)
        return 1;
    return 0;
}

int enterData(double* a, int n, FILE* fin)  {
    int i, j;
    
    if (fin)  {
        for (i = 0; i < n; ++i)  {
            for (j = 0; j < n; ++j) {
                if (fscanf(fin, "%lf", &a[i*n+j]) != 1)
                    return -1;
            }
        }
    }
    else  {
        for (i = 0; i < n; ++i)  {
            for (j = 0; j < n; ++j)  {
                a[i*n+j] = func(i, j, n);
            }
        }
    }
    
    for (i = 0; i < n; ++i)  {
        for (j = 0; j < n; ++j)  {
            if (!(fabs(a[i*n+j] - a[j*n+i]) < 1e-100))
                return -1;
        }
    }
    
    return 0;
}

void printResult(double* res, int k)  {
    printf("%f\n", res[k-1]); 
}

pair<double, double> residualNorm(double* a, double* res, int n)  {
    double inv1, inv2;
    int i, j;
    pair<double, double> p;
    
    inv1 = 0.0;
    inv2 = 0.0;
    
    for (i = 0; i < n; ++i)  {
        inv1 += res[i] - a[i*n+i];
        inv2 += res[i] * res[i];
        
        for (j = 0; j < n; ++j)
            inv2 -= a[i*n+j] * a[i*n+j];
    }
    
    p.first = inv1;
    p.second = inv2;
    
    return p;
}
