#ifndef SolvHead_hpp
#define SolvHead_hpp

#include <stdio.h>

typedef struct  {
    double value;
    int x;
    int y;
} maxelem;

int solve(double* a, double* b, double* x, int* index, maxelem* max_, int *retflag, int n, int number, int count);
void synchronize(int total_threads);

#endif /* SolvHead_hpp */
