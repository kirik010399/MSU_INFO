#ifndef matrixFunctions_hpp
#define matrixFunctions_hpp

#include <stdio.h>

double func1(int i, int j, int n);
double func2(int i, int j, int n);
double func3(int i, int j, int n);

int enterData(double *matrix, double *vector, int n, FILE *fin, int functionNumber); 
void printResult(double* result, int n, int m, FILE *fout); 
double residualNorm(double* matrix, double* vector, double* result, int n);
double errorNorm(double *result, int n);

#endif /* matrixFunctions_hpp */
