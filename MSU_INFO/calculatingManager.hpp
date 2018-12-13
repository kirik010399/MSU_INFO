#ifndef calculatingManager_hpp
#define calculatingManager_hpp

#include <stdio.h>

void calculateValues(double* matrix, double* vector, double eps, int n);
double answer(int n,int p, double* a,double* x1,double* x2, double eps,double z);
void realization(int n, int p, double* a,double* x1, double* x2,double eps);
double MatrixNorm(int n,double* a);
void NearTriangle(int n, double* a, double* x, double eps);



#endif /* calculatingManager_hpp */
