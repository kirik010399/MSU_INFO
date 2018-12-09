#ifndef solvingManager_hpp
#define solvingManager_hpp

#include <stdio.h>

int solveSystem(double* matrix, double* vector, double* result, int* var, int n, int rank, int threadsCount);
void synchronize(int total_threads);

#endif /* solvingManager_hpp */
