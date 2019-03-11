#ifndef matrixFunctions_hpp
#define matrixFunctions_hpp

#include <stdio.h>

double func0(int i, int j, int n);
double func1(int i, int j, int n);
double func2(int i, int j, int n);

int enterData(double *matrix, double *vector, int n, FILE *fin, int functionNumber); 
void printResult(double* result, int n, int m, FILE *fout); 
float residualNorm(double* matrix, double* vector, double* result, int n);
float errorNorm(double *result, int n);

#endif /* matrixFunctions_hpp */
