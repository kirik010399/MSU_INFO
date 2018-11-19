#ifndef matrixUtils_hpp
#define matrixUtils_hpp

#include <stdio.h>
#include <algorithm>

using namespace std; 

double func(int i, int j, int n);
int enterMatrix(double* matrix, int n, FILE* fin);
void printVector(double* vector, int n, int m);
pair<double, double> residualNorm(double* matrix, double* vector, int n);

#endif /* matrixUtils_hpp */
