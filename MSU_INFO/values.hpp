#ifndef values_hpp
#define values_hpp

#include <stdio.h>

void calculate_values(double* a, double* x, double *cos_phi, double *sin_phi, double *x_, double eps, int n);
void reflection(double* a, double *x_, int n);
void QR(double *a, double *cos_phi, double *sin_phi, int k, int n);
void RQ(double *a, double *cos_phi, double *sin_phi, int k, int n);


#endif /* values_hpp */
