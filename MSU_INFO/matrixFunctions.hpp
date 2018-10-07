#ifndef matrixFunctions_hpp
#define matrixFunctions_hpp

#include <stdio.h>

int enterData(double* matrix, double* vector, int n, FILE* fin);
void printResult(double* matrix, int n, int m);
double residualNorm(double* matrix, double* vector, double* result, int n); 
double errorNorm(double *result, int n);

#endif /* matrixFunctions_hpp */
