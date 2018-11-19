#ifndef matrixUtils_hpp
#define matrixUtils_hpp

#include <stdio.h>

struct myPair
{
    double inv1;
    double inv2;
};

double func(int i, int j, int n);
int enterMatrix(double* matrix, int n, FILE* fin);
void printVector(double* vector, int n, int m, int k);
struct myPair residualNorm(double* matrix, double* vector, int n);

#endif /* matrixUtils_hpp */
