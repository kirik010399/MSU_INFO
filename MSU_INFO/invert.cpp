#include "invert.hpp"
#include "matrix.hpp"
#include <math.h>

int invert(double *a, double *a1, double *a2, double *a_inv, double *a_inv1, double *a_inv2, double *x1, double *x2, double *sum1, double *sum2, int n, int threads_count, int thread_num)
{
    int i, j, k;
    int rows;
    int first;
    double tmp;
    double s1, s2;
    double eps = 1e-14;
        
    if (thread_num + 1 > n % threads_count)
        rows = n/threads_count;
    else
        rows = n/threads_count + 1;
    
    double norm = matrix_norm(a, n, threads_count, thread_num);

    for (i = 0; i < rows; ++i)
        for (j = 0; j < n; ++j)
            a[i*n+j] /= norm;
    
    for (i = 0; i < rows; i++)
        for (j = 0; j < n; j++)
            a_inv[i*n+j] = (thread_num+i*threads_count == j);

    for (i = 0; i < n; i++)
    {
        MPI_Barrier(MPI_COMM_WORLD);

        int owner = i % threads_count;
        int loc_i = i / threads_count;
        
        int first;
        
        if (thread_num > owner)
            first = loc_i;
        else
            first = loc_i + 1;
        
        s1 = 0;

        for (j = first; j < rows; ++j)
            s1 += a[j*n+i] * a[j*n+i];

        MPI_Allreduce(&s1, &s2, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        
        double norm_a1;
        if (thread_num == owner)
            norm_a1 = sqrt(s2 + a[loc_i*n+i] * a[loc_i*n+i]);
        
        MPI_Bcast(&norm_a1, 1, MPI_DOUBLE, owner, MPI_COMM_WORLD);
    
//        if (thread_num == 0)
//            printf("norm a_1: %.16lf\n", norm_a1);
        
        if (norm_a1 < eps)
            return -1;
        
        for (int k = 0; k < n; ++k)
            x1[k] = 0;
        
        if (thread_num == owner)
            x1[i] = a[loc_i*n+i] - norm_a1;
        
        for (j = first; j < rows; ++j)
            x1[thread_num + j*threads_count] = a[j*n+i];
        
        MPI_Allreduce(x1, x2, n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        
        double norm_x = sqrt(x2[i]*x2[i]+s2);
        
        if (norm_x < eps)
            continue;
        
        for (j = i; j < n; ++j)
            x2[j] /= norm_x;
        
        for (k = i; k < n; ++k) //лемма 10-11
        {
            double sum = 0.0;
            
            for (j = loc_i; j < rows; ++j)
                sum += x2[thread_num + j*threads_count] * a[j*n+k];
            
            sum1[k] = sum;
        }
        
        MPI_Allreduce(sum1, sum2, n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

        for (k = i; k < n; ++k)
        {
            sum2[k] *= 2.0;
            for (j = loc_i; j < rows; ++j)
                a[j*n+k] -= sum2[k] * x2[thread_num + j*threads_count];
        }
        
        for (k = 0; k < n; ++k) //лемма 10-11
        {
            double sum = 0.0;
            
            for (j = loc_i; j < rows; ++j)
                sum += x2[thread_num + j*threads_count] * a_inv[j*n+k];
            
            sum1[k] = sum;
        }
        
        MPI_Allreduce(sum1, sum2, n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
        
        for (k = 0; k < n; ++k)
        {
            sum2[k] *= 2.0;
            for (j = loc_i; j < rows; ++j)
                a_inv[j*n+k] -= sum2[k] * x2[thread_num + j*threads_count];
        }
    }
    
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
    
    for (i = 0; i < n * n; ++i)
        a1[i] = 0;
    
    for (i = 0; i < rows; ++i)
    {
        for (j = 0; j < n; ++j)
        {
            a1[(thread_num + i*threads_count)*n+j] = a[i*n+j];
        }
    }
    
    MPI_Allreduce(a1, a2, n*n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    
    if (thread_num == 0)
    {
        for (k = 0; k < n; ++k)
        {
            for (i = n-1; i >= 0; --i)
            {
                for (j = i+1; j < n; ++j)
                    a_inv2[i*n+k] -= a2[i*n+j] * a_inv2[j*n+k];
                
                a_inv2[i*n+k] /= a2[i*n+i];
            }
        }//Обратный Гаусс
    }
    
    MPI_Bcast(a_inv2, n*n, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    for (i = 0; i < n; ++i)
    {
        int owner = i % threads_count;
        int loc_i = i / threads_count;
        
        for (j = 0; j < n; ++j)
        {
            if (thread_num == owner)
                a_inv[loc_i*n+j] = a_inv2[i*n+j];
        }
    }
    
    for (i = 0; i < rows; ++i)
        for (j = 0; j < n; ++j)
            a_inv[i*n+j] /= norm;
    
    return 0; 
}

