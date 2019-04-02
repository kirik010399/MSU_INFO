#ifndef functions_hpp
#define functions_hpp

#include "mpi.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <cfloat>
#include <ctime>
#include <sys/time.h>
#include <sys/resource.h>

#define CUT_PART 9
#define EPS 1e-16

struct NormInd
{
    double norm;
    int thread;
};

int readMatrix(double *A, int n, const char *fileName, int p, int k, MPI_Comm comm, double *buf);
void initMatrix(double *A, int n, int p, int k);
void printMatrix(double *A, int n, const char *fileName, int p, int k, MPI_Comm comm, double *buf);
long double get_abs_time();
int findSolution(int n, const char *fileName, int k, int p);

#endif /* functions_hpp */
