#ifndef calculatingManager_h
#define calculatingManager_h

#include <stdio.h>

void calculateValues(double* matrix, double* vector, double eps, int n);
void values(double *matrix, int n, double *vector, double left, double right, double eps);
int n_(double* a, int n, double lam);
void Reflection(double* a, double eps, int n);
double MatrixNorm(double* matrix, int n);

#endif /* calculatingManager_h */
