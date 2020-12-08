#ifndef solve_hpp
#define solve_hpp

#include <stdio.h>
#include <pthread.h>

typedef struct
{
    double elem;
    int row_index;
    int col_index;
} max_elem;

void solve(double *a, double *b, double *x, int *ind, max_elem *max_, int n, int thread_num, int threads_count, int *return_flag);
void synchronize(int total_threads);

#endif /* solve_hpp */
