#include "mpi.h"
#include "functions.hpp"

int main(int argc, char *argv[])
{
    int n, k, p, errorCode = 0;
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
    
    double time = get_abs_time();
    errorCode = findSolution(n, fileName, k, p);
    
    if (errorCode == -1)
    {
        MPI_Finalize();
        return 0;
    }
    
    time = get_abs_time() - time;
    
    if (k == 0)
        printf("Abs Time: %f\n", time);
    
    MPI_Finalize();
    return 0;
}
