#ifndef solvingManager_hpp
#define solvingManager_hpp

#include <stdio.h>

typedef struct
{
    double elem;
    int rowIndex;
    int colIndex; 
} maxElem;

int solveSystem(double* matrix, double* vector, double* result, int* var, maxElem *maxx, int *flag, int n, int rank, int threadsCount);
void synchronize(int total_threads);

#endif /* solvingManager_hpp */
