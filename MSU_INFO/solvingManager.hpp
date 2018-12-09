#ifndef solvingManager_hpp
#define solvingManager_hpp

#include <stdio.h>

int solveSystem(double* a, double* b, double* x, int* var, int n, int rank, int threadsCount);
void synchronize(int total_threads);

#endif /* solvingManager_hpp */
