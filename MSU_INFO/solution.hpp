#ifndef solution_hpp
#define solution_hpp

#include <stdio.h>

struct NormInd
{
    double norm;
    int thread;
};

int findSolution(double *A, double *b, double *buf, double *x, int n, int id, int p);

#endif /* solution_hpp */
