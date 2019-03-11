#ifndef matrixFunctions_hpp
#define matrixFunctions_hpp

#include <stdio.h>

double func0(int i, int j, int n);
double func1(int i, int j, int n);
double func2(int i, int j, int n);

int enterData(double *matrix, int n, FILE *fin, int functionNumber); 
void printResult(double* result, int n, int m, FILE *fout);
void printMatrix(double *matrix, int n, int m, FILE *fout);
void residualNorm(double* matrix, double* vector, float *inv1, float *inv2, int n);

#endif /* matrixFunctions_hpp */
