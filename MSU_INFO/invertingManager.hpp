#ifndef invertingManager_hpp
#define invertingManager_hpp

#include <stdio.h>

int invertMatrix(double* matrix, double* inverseMatrix,  int n, int rank, int threadsCount);
void synchronize(int total_threads);

#endif /* invertingManager_hpp */
