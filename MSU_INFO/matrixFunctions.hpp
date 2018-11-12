#ifndef aFunctions_hpp
#define aFunctions_hpp

#include <stdio.h>

double func(int i, int j, int n);
int enterData(double* a, double* b, int n, FILE* fin);
void printResult(double* a, int n, int m);
double inaccuracyNorm(double* a, double* b, double* x, int n);
double errorNorm(double *x, int n);

#endif /* aFunctions_hpp */
