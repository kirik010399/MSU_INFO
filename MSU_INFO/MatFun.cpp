#include "MatFun.hpp"
#include <stdio.h>
#include <math.h>
#include <iostream>

using namespace std;

double func(int i, int j, int n) {
    n=n;
    return fabs(i-j);
}

int enterData(double* a, double *b, int n, FILE* fin) {
    int i;
    int j;
    
    if (fin) {
        for (i = 0; i < n; ++i) {
            for (j = 0; j < n; ++j) {
                if (fscanf(fin, "%lf", &a[i*n+j]) != 1)
                    return -1;
            }
            
            if (fscanf(fin, "%lf", &b[i]) != 1)
                return -1;
        }
    }
    else {
        for (i = 0; i < n; ++i) {
            b[i] = 0;
            
            for (j = 0; j < n; ++j)  {
                a[i*n+j] = func(i, j, n);
                
                if (j % 2 == 0)
                    b[i] += a[i*n+j];
            }
        }
    }
    
    return 0;
}

void printResult(double* x, int n, int m) {
    int i;
    int min_ = fmin(n,m);
    
    for (i = 0; i < min_; ++i)
        printf("%f ", x[i]);
    
    printf("\n");
}

double residualNorm(double* a, double* b, double* x, int n) {
    int i, j;
    double res = 0;
    double val;
    
    for (i = 0; i < n; ++i) {
        val = 0.0;
        
        for (j = 0; j < n; ++j)
            val += a[i*n+j] * x[j];
        
        val -= b[i];
        
        res += val*val;
    }
    
    return sqrt(res);
}

double errorNorm(double *x, int n) {
    double error = 0;
    int i;
    
    for (i = 0; i < n; ++i) {
        if (i % 2)
            error += x[i]*x[i];
        else
            error += (x[i]-1)*(x[i]-1);
    }
    
    return sqrt(error);
}
