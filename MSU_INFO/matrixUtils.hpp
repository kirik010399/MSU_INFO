#ifndef matrixUtils_hpp
#define matrixUtils_hpp

#include <stdio.h>

int enterMatrix(double* matrix, int n, FILE* fin);
void printMatrix(double* matrix, int n, int m);
double residualNorm(double* matrix, double* inverseMatrix, int n);

#endif /* matrixUtils_hpp */
