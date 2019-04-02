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

int readMatrix(double *A, double *b, int n, const char *fileName, int p, int k, MPI_Comm comm, double *buf);
void initMatrix(double *A, double *b, int n, int p, int k);
void printMatrix(double *A, double *b, int n, const char *fileName, int p, int k, MPI_Comm comm, double *buf);
void printSolution(double *x, int n);
double getResidual(int id, int p, int n, double *A, double *b, double *x);
double getNormError(double *x, int n);

#endif /* functions_hpp */
