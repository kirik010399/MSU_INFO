#include "invert.hpp"
#include "matrix.hpp"
#include <math.h>

int invert(double *a, double *a_inv, double *x1, double *x2, double *sum1, double *sum2, int n, int threads_count, int thread_num)
{
    int i, j, k;
    int rows;
    int first;
    double tmp;
    double s1, s2;
    double eps = 1e-20;

    if (thread_num + 1 > n % threads_count)
        rows = n/threads_count;
    else
        rows = n/threads_count + 1;
    
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
    
    for (k = 0; k < n; ++k)
    {
        for (j = 0; j < n; ++j)
            x1[j] = 0;

        for (j = 0; j < rows; ++j)
            x1[thread_num + j*threads_count] = a_inv[j*n+k];

        MPI_Allreduce(x1, x2, n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);

        for (i = n-1; i >= 0; --i)
        {
            int owner = i % threads_count;
            int loc_i = i / threads_count;

            if (thread_num == owner)
            {
                for (j = i+1; j < n; ++j)
                {
                    x2[i] -= a[loc_i*n+j] * x2[j];
                }

                x2[i] /= a[loc_i*n+i];
                a_inv[loc_i*n+k] = x2[i];
            }
            MPI_Bcast(x2, n, MPI_DOUBLE, owner, MPI_COMM_WORLD);
        }
    }//Обратный Гаусс
    
    return 0; 
}

