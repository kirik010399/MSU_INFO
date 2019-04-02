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

int readMatrix(double *A, int n, int m, const char *fileName, int p, int k, MPI_Comm comm, double *buf);
void initMatrix(double *A, int n, int m, int p, int k);
void printMatrix(double *A, int n, int m, const char *fileName, int p, int k, MPI_Comm comm, double *buf);
void getBlock(double *A, int n, int m, int p, int i, int j, double *B);
void putBlock(double *A, int n, int m, int p, int i, int j, double *B);
void getBufBlock(double *buf, int n, int m, int i, int j, double *B);
void getBufColumn(double *buf, int n, int m, int i, double *b);
void swapColumns(double *A, int n, int m, int p, int id, int i, int j, int *colOrder, double *B);
void swapStrings(double *A, int n, int m, int p, int i, int j, double *B, double *b);
void clearColumn(double *b, double *bufColumn, double *B, int n, int m, int p, int i, int j);
void matrixMultVector(double *B, double *b, int i, int n, int m, int p);
int inverseMatrix(double *B, int m, double norm);
double getNorm(double *B, int m);
void multMatrices(double *a, double *b, double *c, int n);
void multBlocks(double *A, int n1, int m1, double *B, int n2, int m2, double *C);
void matrixMultVector(double *B, double *b, int i, int n, int m);
void diffBlocks(double *A, double *B, int n, int m);
double get_cpu_time();
double get_abs_time();
int findSolution(int n, int m, const char *fileName, int k, int p);

#endif /* functions_hpp */
