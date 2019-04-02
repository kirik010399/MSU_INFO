#include "functions.hpp"
#include <iostream>

using namespace std;

void printSolution(double *x, int n)
{
    int visiblePart = (n > CUT_PART) ? CUT_PART : n;
    printf("\nResult:\n");
    for (int i = 0; i < visiblePart; ++i)
        printf("%f ", x[i]);
    printf("\n");
}

int readMatrix(double *A, double *b, int n, const char *fileName, int p, int k, MPI_Comm com, double *buf)
{
    FILE *in = 0;
    int i, j;
    int err = 0, dst;
    
    if (k == 0)
    {
        in = fopen(fileName, "r");
        if (!in)
            err = 1;
    }
    
    MPI_Bcast(&err, 1, MPI_INT, 0, com);
    if (err)
        return -1;
    
    memset(buf, 0, n*sizeof(double));
    
    for (i = 0; i < n; i++)
    {
        // from process 0 to process dst
        dst = i % p;
        
        if (k == 0)
        {
            for (j = 0; j < n; j++)
                if (fscanf(in, "%lf", buf + j) != 1)
                {
                    err = 1;
                    break;
                }
            
            if (dst != 0)
                MPI_Send(buf, n, MPI_DOUBLE, dst, 0 /* tag */, com);
        }
        else if (k == dst)
        {
            MPI_Status st;
            MPI_Recv(buf, n, MPI_DOUBLE, 0, 0 /* tag */, com, &st);
        }
        
        if (k == dst)
        {
            int loc_i = i / p;
            memcpy(A + loc_i * n, buf, n*sizeof(double));
            
            b[loc_i] = 0;

            for (j = 0; j < n; j++)
            {
                if (j % 2 == 0)
                    b[loc_i] += A[loc_i * n + j];
            }
        }
    }
    
    if ((k == 0) && (in != 0))
        fclose(in);
    
    MPI_Bcast(&err, 1, MPI_INT, 0, com);
    if (err)
        return -2;
    
    return 0;
}

void initMatrix(double *A, double *b, int n, int p, int k)
{
    int i, j, owner;
    
    for (i = 0; i < n; i++)
    {
        owner = i % p;
        
        if (k == owner)
        {
            int loc_i = i / p;
            b[loc_i] = 0;
            
            for (j = 0; j < n; j++)
            {
                A[loc_i * n + j] = fabs(i-j);
                
                if (j % 2 == 0)
                    b[loc_i] += A[loc_i * n + j];
            }
        }
    }
}

void printMatrix(double *A, double *b, int n, const char *fileName, int p, int k, MPI_Comm com, double *buf)
{
    FILE *in = 0;
    int i, j, visiblePartStr, visiblePartCol, dst;
    
    if (k == 0)
    {
        if (fileName)
            in = fopen(fileName, "w");
        else
            in = stdout;
    }
    
    memset(buf, 0, (n + 1) * sizeof(double));
    
    if (k == 0)
        fprintf(in, "\n");
    
    visiblePartStr = n < CUT_PART ? n : CUT_PART;
    for (i = 0; i < visiblePartStr; i++)
    {
        // from process 0 to process dst
        dst = i % p;
        
        if (k == dst)
        {
            int loc_i = i / p;
            memcpy(buf, A + loc_i * n, n * sizeof(double));
            memcpy(buf + n, b + loc_i, 1 * sizeof(double));
        }
        
        if (k == dst && k != 0)
            MPI_Send(buf, n + 1, MPI_DOUBLE, 0, 0 /* tag */, com);
        else if (k == 0)
        {
            MPI_Status st;
            if (dst != 0)
                MPI_Recv(buf, n + 1, MPI_DOUBLE, dst, 0 /* tag */, com, &st);
            
            visiblePartCol = n < CUT_PART ? n : CUT_PART;
            for (j = 0; j < visiblePartCol; j++)
                fprintf(in, "%f ", buf[j]);
            fprintf(in, "| %f\n", buf[n]);
        }
    }
    
    if (k == 0)
        fprintf(in, "\n");
}

double getResidual(int id, int p, int n, double *A, double *b, double *x)
{
    int i, j;
    double res = 0., globalRes, val;
    for (i = id; i < n; i+=p)
    {
        int loc_i = i / p;
        
        val = 0.0;
        
        for (j = 0; j < n; ++j)
            val += A[loc_i*n+j] * x[j];
        
        val -= b[loc_i];
        
        res += val*val;
    }
    MPI_Allreduce(&res, &globalRes, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    
    return sqrt(globalRes);
}

double getNormError(double *x, int n)
{
    double error = 0;
    int i;
    
    for (i = 0; i < n; ++i)
    {
        if (i % 2)
            error += x[i]*x[i];
        else
            error += (x[i]-1)*(x[i]-1);
    }
    
    return sqrt(error);
}
