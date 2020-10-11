#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>

double f(int k, int n, int i, int j);
int enter_matrix(double* a, double *b, int n, int k, FILE* fin);
void print_matrix(double* a, int l, int n, int m);
double norm(double* a, double* b, double* x, int n);
double error_norm(double *x, int n);

#endif /* matrix_hpp */
