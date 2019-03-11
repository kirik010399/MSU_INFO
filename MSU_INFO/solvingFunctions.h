#ifndef solvingFunctions_hpp
#define solvingFunctions_hpp

#include <stdio.h>

void calculateValues(double *matrix, double *result, double *cos, double *sin, int n, float eps, int debug);
double MatrixNorm(double* matrix, int n);
void Rotation(double* matrix, int n);
void QR(double* matrix, int n, int k, double* cos, double* sin);
void RQ(double* matrix, int n, int k, double* cos, double* sin);

#endif /* solvingFunctions_hpp */
