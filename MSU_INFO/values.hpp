#ifndef values_hpp
#define values_hpp

#include <stdio.h>

void calculate_values(double* a, double* x, double *x1, double *x2, double *x_, double *y_, double *z_, double eps, int n);
void reflection(double* a, double *x_, double *y_, double *z_, int n);
void QR(double *a, double *x1, double *x2, int k, int n);
void RQ(double *a, double *x1, double *x2, int k, int n);


#endif /* values_hpp */
