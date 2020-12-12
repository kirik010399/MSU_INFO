#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>

double f(int k, int n, int i, int j);
int enter_matrix(double* a, int n, int k, FILE* fin);
void print_matrix(double* a, int l, int n, int m);
void residual(double* a, double* x, double *norm1, double *norm2, int n);
double norm(double *a, int n);

#endif /* matrix_hpp */
