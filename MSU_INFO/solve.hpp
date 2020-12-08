#ifndef solve_hpp
#define solve_hpp

#include <stdio.h>
#include <pthread.h>

void solve(double *a, double *b, double *x, int *ind, int n, int thread_num, int threads_count, int *return_flag);
void synchronize(int total_threads);

#endif /* solve_hpp */
