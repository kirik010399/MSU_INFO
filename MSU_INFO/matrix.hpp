#ifndef matrix_hpp
#define matrix_hpp

#include <stdio.h>

double f(int i, int j);
int enter_matrix(double* a, int n, FILE* fin);
void print_matrix(double* a, int n, int m);
double norm(double* a, double* a_inv, int n);

#endif /* matrix_hpp */
