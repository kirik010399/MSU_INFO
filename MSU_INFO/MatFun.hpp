#ifndef MatFun_hpp
#define MatFun_hpp

#include <stdio.h>

double func(int i, int j, int n);
int enterData(double* a, double* b, int n, FILE* fin);
void printResult(double* a, int n, int m);
double residualNorm(double* a, double* b, double* x, int n, int number, int count);
double errorNorm(double *x, int n);

#endif /* MatFun_hpp */