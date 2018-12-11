#ifndef invertingManager_hpp
#define invertingManager_hpp

#include <stdio.h>

typedef struct
{
    double elem;
    int rowIndex;
    int colIndex;
} maxElem;

int invertMatrix(double* matrix, double* inverseMatrix, int n, maxElem* max_, int *var, int rank, int threadsCount);
void synchronize(int total_threads);

#endif /* invertingManager_hpp */
