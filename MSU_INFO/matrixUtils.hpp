#ifndef matrixUtils_hpp
#define matrixUtils_hpp

#include <stdio.h>

double func(int i, int j, int n);
int enterData(double* matrix, double* vector, int n, FILE* fin);
void printResult(double* matrix, int n, int m);
double residualNorm(double* matrix, double* vector, double* result, int n);
double errorNorm(double *result, int n);

#endif /* matrixUtils_hpp */
