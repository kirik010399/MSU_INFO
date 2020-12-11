#include "mpi.h"
#include <stdio.h>
#include <iostream>
#include <time.h>
#include <math.h>
#include "matrix.hpp"
#include "invert.hpp"
#include <sys/time.h>

using namespace std;

long double get_time();

int main(int argc, char *argv[])
{
    int n, m, i, k;
    int num_of_str;
    int thread_num, threads_count;
    double *a;
    double *a_inv;
    double *a_inv1;
    double *a_inv2;
    double *buf;
    double *x1, *x2;
    double *sum1, *sum2;
    char *filename;
    long double t;
    int flag = 0;
    
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &threads_count);
    MPI_Comm_rank(MPI_COMM_WORLD, &thread_num);
    
    if (argc < 4)
    {
        printf("Некорректный запуск программы. Правильный формат:\n. mpirun -np threads /a.out n m k *filename (если k != 0)");
        MPI_Finalize();
        return -1;
    }
    
    if (sscanf(argv[1], "%d", &n) != 1 || sscanf(argv[2], "%d", &m) != 1 || sscanf(argv[3], "%d", &k) != 1)
    {
        printf("Данные запуска некорректны.\n");
        MPI_Finalize();
        return -1;
    }
    
    if ((k == 0 && argc != 5) || (k != 0 && argc != 4))
    {
        printf("Данные запуска некорректны.\n");
        MPI_Finalize();
        return -1;
    }
    
    if (n < 0 || m < 0 || m > n || k < 0 || k > 4)
    {
        printf("Данные некорректны.\n");
        MPI_Finalize();
        return -1;
    }

    if (k == 0)
        filename = argv[4];
    
    int rows;
    
    if (thread_num + 1 > n % threads_count)
        rows = n/threads_count;
    else
        rows = n/threads_count + 1;
    
    a = new double [n * rows];
    a_inv = new double [n * rows];
    x1 = new double [n];
    x2 = new double [n];
    sum1 = new double [n];
    sum2 = new double [n];
    buf = new double[n];
    
    a_inv1 = new double [n*n];
    a_inv2 = new double [n*n];
    
    if (k == 0)
        flag = read_matrix(a, buf, n, filename, threads_count, thread_num);
    else
        init_matrix(a, n, k, threads_count, thread_num);
    
    if (flag < 0)
    {
        if (thread_num == 0)
            printf("Матрица некорректна.\n");
        
        delete []a;
        delete []a_inv;
        delete []x1;
        delete []x2;
        delete []sum1;
        delete []sum2;
        delete []buf;
        delete []a_inv1;
        delete []a_inv2;
        
        MPI_Finalize();
        
        return -2;
    }
    
    if (thread_num == 0)
        printf("\nИзначальная матрица:\n");
    
    print_matrix(a, n, m, threads_count, thread_num, buf);
    
    MPI_Barrier(MPI_COMM_WORLD);
    t = get_time();
    
    flag = invert(a, a_inv, x1, x2, sum1, sum2, n, threads_count, thread_num);
    
    MPI_Barrier(MPI_COMM_WORLD);
    t = get_time() - t;
        
    if (flag < 0)
    {
        if (thread_num == 0)
            printf("Матрица некорректна.\n");
        
        delete []a;
        delete []a_inv;
        delete []x1;
        delete []x2;
        delete []sum1;
        delete []sum2;
        delete []buf;
        delete []a_inv1;
        delete []a_inv2;
        
        MPI_Finalize();
        
        return -2;
    }
    
    if (thread_num == 0)
        printf("\nОбратная матрица:\n");
    
    print_matrix(a_inv, n, m, threads_count, thread_num, buf);
    
    if (thread_num == 0)
        printf("\nВремя: %Lf с.\n", t);
    
    if (k == 0)
        flag = read_matrix(a, buf, n, filename, threads_count, thread_num);
    else
        init_matrix(a, n, k, threads_count, thread_num);
    
    double err = error_norm(a, a_inv, a_inv1, a_inv2, n, threads_count, thread_num);
    
    if (thread_num == 0)
        printf("\nПогрешность: %10.3e\n", err);
    
    delete []a;
    delete []a_inv;
    delete []x1;
    delete []x2;
    delete []sum1;
    delete []sum2;
    delete []buf;
    delete []a_inv1;
    delete []a_inv2;
    
    MPI_Finalize();

    return 0;
}

long double get_time()
{
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec + t.tv_usec/1000000.0;
}
