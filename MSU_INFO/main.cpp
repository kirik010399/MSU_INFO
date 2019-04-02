#include "mpi.h"
#include "functions.hpp"
#include "solution.hpp"

long double get_abs_time();

int main(int argc, char *argv[])
{
    int n, k, p, numOfStr, errorCode = 0;
    double residual;
    long double time;
    const char *fileName = 0;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &p);
    MPI_Comm_rank(MPI_COMM_WORLD, &k);
    
    if ((argc > 3) || (argc < 2) || ((n = atoi(argv[1])) <= 0))
    {
        if (k == 0)
            printf("Error: incorrect input!\n");
        MPI_Finalize();
        return 0;
    }
    
    if (argc == 3)
        fileName = argv[2];
    
    numOfStr = n / p + 1;

    double *A = new double[n * numOfStr];
    double *b = new double[numOfStr];
    double *buf = new double[n + numOfStr];
    double *x = new double[n];
    
    if (fileName)
        errorCode = readMatrix(A, b, n, fileName, p, k, MPI_COMM_WORLD, buf);
    else
        initMatrix(A, b, n, p, k);
    
    if (errorCode)
    {
        if (k == 0)
            printf("Error: can't read matrix!\n");
        
        MPI_Finalize();
        return 0;
    }
    
    printMatrix(A, b, n, 0, p, k, MPI_COMM_WORLD, buf);
    
    time = get_abs_time();
    errorCode = findSolution(A, b, buf, x, n, k, p);
    time = get_abs_time() - time;
    
    if (errorCode == 0 && k == 0)
    {
        printSolution(x, n);
    }
    
    if (fileName)
        readMatrix(A, b, n, fileName, p, k, MPI_COMM_WORLD, buf);
    else
        initMatrix(A, b, n, p, k);
    
    residual = getResidual(k, p, n, A, b, x);
    
    if (k == 0)
    {
        printf("\nResidual norm: %e\n", residual);
        printf("Norm of error: %e\n", getNormError(x, n));
        printf("Abs Time: %Lf\n", time);
    }
    
    delete[] x;
    delete[] A;
    delete[] b;
    delete[] buf;
    
    if (errorCode == -1)
    {
        MPI_Finalize();
        return 0;
    }
    
    MPI_Finalize();
    return 0;
}

long double get_abs_time()
{
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec + t.tv_usec/1000000.0;
}
