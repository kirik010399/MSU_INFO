#ifndef invert_hpp
#define invert_hpp

#include "mpi.h"
#include <stdio.h>

int invert(double *a,  double *a1, double *a2, double *a_inv, double *a_inv1, double *a_inv2, double *x1, double *x2, double *sum1, double *sum2, int n, int threads_count, int thread_num);

#endif /* invert_hpp */
