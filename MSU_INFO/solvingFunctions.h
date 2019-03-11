#ifndef solvingFunctions_hpp
#define solvingFunctions_hpp

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void solveSystem(double* matrix, double* vector, double* result, int *var, int n, int *flag, float eps, int debug, int rank, int threadsCount);
void synchronize(int total_threads);

#endif /* solvingFunctions_hpp */
