#ifndef calculatingManager_hpp
#define calculatingManager_hpp

#include <stdio.h>

int calculateValues(double* matrix, double* vector, double left, double right, double eps, int n, double *x, double *y, double *z);
int values(double *matrix, int n, double *vector, double left, double right, double eps);
int n_(double* a, int n, double lam);
void Refl(double* a, int n, double *x, double *y, double *z);

#endif /* calculatingManager_hpp */
