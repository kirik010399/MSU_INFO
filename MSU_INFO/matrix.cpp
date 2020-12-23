#include "matrix.hpp"
#include <stdio.h>
#include <math.h>

double f(int k, int n, int i, int j)
{
    switch (k)
    {
        case 1:
            return n-fmax(i, j)+1;
        case 2:
            return fmax(i, j);
        case 3:
            return fabs(i-j);
        case 4:
            return 1.0/(i+j+1);
        default:
            return -1;
    }
}

int read_matrix(double *a, double *buf, int n, char *filename, int threads_count, int thread_num)
{
    FILE *fin = 0;
    int i, j;
    int err = 0, dst;
    
    if (thread_num == 0)
    {
        fin = fopen(filename, "r");
        
        if (!fin)
            err = 1;
    }
    
    MPI_Bcast(&err, 1, MPI_INT, 0, MPI_COMM_WORLD);
    
    if (err)
        return -1;
    
    for (int i = 0; i < n; ++i)
        buf[i] = 0;
    
    for (i = 0; i < n; ++i)
    {
        // from process 0 to process dst
        dst = i % threads_count;
        
        if (thread_num == 0)
        {
            for (j = 0; j < n; ++j)
            {
                if (fscanf(fin, "%lf", &buf[j]) != 1)
                {
                    err = 1;
                    break;
                }
            }
            
            if (dst != 0)
                MPI_Send(buf, n, MPI_DOUBLE, dst, 0 /* tag */, MPI_COMM_WORLD);
        }
        else if (thread_num == dst)
        {
            MPI_Status st;
            MPI_Recv(buf, n, MPI_DOUBLE, 0, 0 /* tag */, MPI_COMM_WORLD, &st);
        }
        
        if (thread_num == dst)
        {
            int loc_i = i / threads_count;
            
            for (int j = 0; j < n; ++j)
                a[loc_i*n+j] = buf[j];
        }
    }
    
    if (thread_num == 0)
        fclose(fin);
    
    MPI_Bcast(&err, 1, MPI_INT, 0, MPI_COMM_WORLD);//потому что броудкатс у всех
    
    if (err)
        return -2;
    
    return 0;
}

void init_matrix(double *a, int n, int k, int threads_count, int thread_num)
{
    int i, j, owner;
    
    for (i = 0; i < n; ++i)
    {
        owner = i % threads_count;
        
        if (thread_num == owner)
        {
            int loc_i = i / threads_count;
            
            for (j = 0; j < n; ++j)
            {
                a[loc_i*n+j] = f(k, n, i, j);
            }
        }
    }
}

void print_matrix(double *a, int n, int m, int threads_count, int thread_num, double *buf)
{
    int i, j;

    for (i = 0; i < m; i++)
    {
        int dst = i % threads_count;
        int loc_i = i / threads_count;

        if (thread_num == 0)
        {
            if (thread_num == dst)
            {
                for (j = 0; j < m; j++)
                    printf("%10.3e ", a[loc_i*n+j]);
                
                printf("\n");
            }
            else
            {
                MPI_Status st;
                MPI_Recv(buf, m, MPI_DOUBLE, dst, 0, MPI_COMM_WORLD, &st);
                
                for (j = 0; j < m; j++)
                    printf("%10.3e ", buf[j]);
                printf("\n");
            }
        }
        else if (thread_num == dst)
        {
            for (j = 0; j < m; j++)
                buf[j] = a[loc_i*n+j];
            MPI_Send(buf, m, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD);
        }
    }
}

double error_norm(double* a, double* a_inv, double *a_inv1, double *a_inv2, int n, int threads_count, int thread_num)
{
    int i, j, k;
    double temp, sum = 0.0, max = 0.0;
    int rows;
        
    if (thread_num + 1 > n % threads_count)
        rows = n/threads_count;
    else
        rows = n/threads_count + 1;
    
    for (i = 0; i < n * n; ++i)
        a_inv1[i] = 0;
    
    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            a_inv1[(thread_num + i*threads_count)*n+j] = a_inv[i*n+j];
        }
    }
    
    MPI_Allreduce(a_inv1, a_inv2, n*n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        
    for (i = 0; i < n; ++i)
    {
        int owner = i % threads_count;
        int loc_i = i / threads_count;
                
        if (thread_num == owner)
        {
            sum = 0.0;

            for (j = 0; j < n; ++j)
            {
                temp = 0.0;
                
                for (k = 0; k < n; ++k)
                    temp += a[loc_i*n+k] * a_inv2[k*n+j];
                
                if (i == j)
                    temp -= 1.0;
                
                sum += fabs(temp);
            }
            
            if (sum > max)
                max = sum;
        }
    }
    
    double global_max;
    
    MPI_Allreduce(&max, &global_max, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
    
    return global_max; 
}

double matrix_norm(double* a, int n, int threads_count, int thread_num)
{
    int i, j, k;
    double temp, sum = 0.0, max = 0.0;
        
    for (i = 0; i < n; ++i)
    {
        int owner = i % threads_count;
        int loc_i = i / threads_count;
                
        if (thread_num == owner)
        {
            sum = 0.0;

            sum += fabs(a[loc_i*n+j]);
            
            if (sum > max)
                max = sum;
        }
    }
    
    double global_max;
    
    MPI_Allreduce(&max, &global_max, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
    
    return global_max;
}
