#ifndef solvingManager_hpp
#define solvingManager_hpp

#include <stdio.h>

int solve(double* a, double* b, double* x, int* index, int *funcFlag, int n, int number, int count);
void synchronize(int total_threads);

#endif /* solvingManager_hpp */
