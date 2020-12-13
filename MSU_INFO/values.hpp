#ifndef values_hpp
#define values_hpp

#include <stdio.h>

void calculate_values(double* a, double* x, double *x_, double eps, int n);
void reflection(double* a, double *x_, int n);
int LR(double *a, int k, int n);
void RL(double *a, int k, int n);

#endif /* values_hpp */
