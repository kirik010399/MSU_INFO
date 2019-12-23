#ifndef matrixUtils_hpp
#define matrixUtils_hpp

#include <stdio.h>

void enterData(double* matrix, double *vector, int n);
void printResult(double* matrix, int n, int m);
double residualNorm(double* matrix, double* vector, double* result, int n); 
double errorFunction(double *result, int n);

#endif /* matrixUtils_hpp */
