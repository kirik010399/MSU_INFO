#ifndef calculatingManager_hpp
#define calculatingManager_hpp

#include <stdio.h>

void calculateValues(double* matrix, double* vector, double left, double right, double eps, int n);
void values(double *matrix, int n, double *vector, double left, double right, double eps);
int n_(double* a, int n, double lam);
void Reflection(double* a, int n);

#endif /* calculatingManager_hpp */
