#ifndef matrixUtils_h
#define matrixUtils_h

#include <stdio.h>

double func(int i, int j, int n);
int enterMatrix(double* matrix, int n, FILE* fin);
void printMatrix(double* matrix, int n, int m);
double residualNorm(double* matrix, double* inverseMatrix, int n);

#endif /* matrixUtils_h */
