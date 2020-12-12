#ifndef values_hpp
#define values_hpp

#include <stdio.h>

void calculate_values(double *a, double *x, int *values_count, double left, double right, double eps, int n);
void values(double *a, double *x, int *values_count, double left, double right, int n,  double eps);
int n_(double* a, int n, double lambda);
void rotate(double* a, int n);

#endif /* values_hpp */
