#ifndef values_hpp
#define values_hpp

#include <stdio.h>

int calculate_values(double* a, double* x, double eps, int n);
void rotate(double* a, int n);
int LR(double *a, int k, int n);
void RL(double *a, int k, int n);

#endif /* values_hpp */
