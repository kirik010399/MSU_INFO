#ifndef matrix_hpp
#define matrix_hpp

#include "mpi.h"
#include <stdio.h>

double f(int k, int n, int i, int j);
int read_matrix(double *a, double *buf, int n, char *filename, int threads_count, int thread_num);
void init_matrix(double *a, int n, int k, int threads_count, int thread_num);
void print_matrix(double *a, int n, int m, int threads_count, int thread_num, double *buf);
double error_norm(double* a, double* a_inv, double *a_inv1, double *a_inv2, int n, int threads_count, int thread_num);
double matrix_norm(double* a, int n, int threads_count, int thread_num);

#endif /* matrix_hpp */
