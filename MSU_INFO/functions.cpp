#include "functions.hpp"
#include <iostream>

using namespace std;

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

long double get_abs_time()
{
    struct timeval t;
    gettimeofday(&t, 0);
    return t.tv_sec + t.tv_usec/1000000.0;
}

int findSolution(int n, const char *fileName, int id, int p)
{
    double *A, *b, *x, *buf;
    int i, j, k, s, q, err = 0, globalErr, num, globalNum, len, loc_i, loc_j, loc_max_i, minStr;
    double tmp, maxNorm;
    int numOfStr = n / p + 1;
    MPI_Status st;
    
    NormInd normInd, globalNormInd;
    int maxPos[2];
    int maxStr, maxCol;
    int *colOrder;
    
    A = new double[n * numOfStr];
    b = new double[numOfStr];
    buf = new double[n + numOfStr];
    x = new double[n];
    colOrder = new int[n];
        
    for (i = 0; i < n; i++)
    {
        x[i] = 0;
        colOrder[i] = i;
    }
    
    if (fileName)
        err = readMatrix(A, b, n, fileName, p, id, MPI_COMM_WORLD, buf);
    else
        initMatrix(A, b, n, p, id);
    
    if (err)
    {
        if (id == 0)
            printf("Error: can't read matrix!\n");
        delete[] x;
        delete[] colOrder;
        delete[] A;
        delete[] b;
        delete[] buf;
        
        return -1;
    }
    
    printMatrix(A, b, n, 0, p, id, MPI_COMM_WORLD, buf);
    
    err = 0;
    
    long double time = get_abs_time();
    for (i = 0; i < n; ++i)
    {
        minStr = (i % p <= id) ? i - i % p + id : i + (p - i % p) + id;
        
        maxStr = minStr;
        maxCol = i;
        maxNorm = 0;
        
        normInd.thread = -1;
        normInd.norm = maxNorm;
        maxPos[0] = -1;
        maxPos[1] = -1;
        
        for (s = minStr; s < n; s+=p)
        {
            for (q = i; q < n; ++q)
            {
                loc_i = s / p;
                if (fabs(A[loc_i*n+q]) > maxNorm)
                {
                    maxNorm = fabs(A[loc_i*n+q]);
                    maxStr = s;
                    maxCol = q;
                }
            }
        }
        
        num = 0; err = 0;
        globalNum = 0; globalErr = 0;
        
        s = (i % p <= id) ? i - i % p + id : i + (p - i % p) + id;
        if (s < n)
        {
            num = 1;
            normInd.thread = id;
            normInd.norm = maxNorm;
            maxPos[0] = maxStr;
            maxPos[1] = maxCol;

            if (fabs(maxNorm) < EPS)
                err = 1;
        }

        MPI_Allreduce(&num, &globalNum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
        MPI_Allreduce(&err, &globalErr, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);

        if (globalNum == globalErr)
        {
            if (id == 0)
                printf("Error: no main element\n");
            delete[] x;
            delete[] colOrder;
            delete[] A;
            delete[] b;
            delete[] buf;

            return -1;
        }
        
        MPI_Allreduce(&normInd, &globalNormInd, 1, MPI_DOUBLE_INT, MPI_MAXLOC, MPI_COMM_WORLD);
        MPI_Bcast(&maxPos, 2, MPI_INT, globalNormInd.thread, MPI_COMM_WORLD);
        
        if (maxPos[1] != i)
        {
            swap(colOrder[i], colOrder[maxPos[1]]);

            for (j = 0; j < numOfStr; ++j)
                swap(A[j*n+maxPos[1]], A[j*n+i]);
        }
        
        if ((globalNormInd.thread == (i % p)) && (globalNormInd.thread == id))
        {
            if (maxPos[0] != i)
            {
                loc_i = i / p;
                loc_max_i = maxPos[0] / p;
                
                for (j = 0; j < n; ++j)
                    swap(A[loc_max_i*n+j], A[loc_i*n+j]);
                
                swap(b[loc_max_i], b[loc_i]);
            }
        }
        else if (globalNormInd.thread == id)
        {
            if (maxPos[0] != i)
            {
                len = n;
                memset(buf, 0, (len + 1)*sizeof(double));
                
                int loc_i = maxPos[0] / p;
                memcpy(buf, A + loc_i * n, len*sizeof(double));
                memcpy(buf + len, b + loc_i, sizeof(double));
                
                MPI_Sendrecv_replace(buf, len + 1, MPI_DOUBLE, i % p, 0 /* tag */, i % p, 0 /* tag */, MPI_COMM_WORLD, &st);
                
                memcpy(A + loc_i * n, buf, len*sizeof(double));
                memcpy(b + loc_i, buf + len, sizeof(double));
            }
        }
        else if ((i % p) == id)
        {
            if (maxPos[0] != i)
            {
                len = n;
                memset(buf, 0, (len + 1)*sizeof(double));
                
                int loc_i = i / p;
                memcpy(buf, A + loc_i * n, len*sizeof(double));
                memcpy(buf + len, b + loc_i, sizeof(double));
                
                MPI_Sendrecv_replace(buf, len + 1, MPI_DOUBLE, globalNormInd.thread, 0 /* tag */, globalNormInd.thread, 0 /* tag */, MPI_COMM_WORLD, &st);
                
                memcpy(A + loc_i * n, buf, len*sizeof(double));
                memcpy(b + loc_i, buf + len, sizeof(double));
            }
        }
        
        if (i % p == id)
        {
            loc_i = i / p;
            tmp = 1.0 / A[loc_i*n+i];
            
            for (j = i; j < n; ++j)
                A[loc_i*n+j] *= tmp;
            
            b[loc_i] *= tmp;
        }
        // Ended multing i string
        
        len = n;
        if (id == (i % p))
        {
            memset(buf, 0, (len + 1)*sizeof(double));
            
            int loc_i = i / p;
            memcpy(buf, A + loc_i * n, len*sizeof(double));
            memcpy(buf + len, b + loc_i, sizeof(double));
        }
        
        MPI_Bcast(buf, len + 1, MPI_DOUBLE, i % p, MPI_COMM_WORLD); // Send i string to all processes
        
        minStr = ((i + 1) % p <= id) ? i + 1 - (i + 1) % p + id : i + 1 + (p - (i + 1) % p) + id;
        for (j = minStr; j < n; j+=p)
        {
            loc_j = j / p;
            tmp = A[loc_j*n+i];
            
            for (k = i; k < n; ++k)
                A[loc_j*n+k] -= buf[k] * tmp;
            
            b[loc_j] -= buf[n] * tmp;
        }
        
//        MPI_Barrier(MPI_COMM_WORLD);
        
//        printMatrix(A, b, n, 0, p, id, MPI_COMM_WORLD, buf);
    }
    
//    printMatrix(A, b, n, 0, p, id, MPI_COMM_WORLD, buf);
    
    for (i = n-1; i >= 0; --i)
    {
        int loc_i = i / p;
        
        if (id == i % p)
        {
            tmp = b[loc_i];
            
            for (j = i+1; j < n; ++j)
                tmp -= A[loc_i * n + j] * x[colOrder[j]];
            
            x[colOrder[i]] = tmp;
        }

        MPI_Bcast(x + colOrder[i], 1, MPI_DOUBLE, i % p, MPI_COMM_WORLD);
    }
    
    time = get_abs_time() - time;    
    
    if (id == 0)
    {
        int visiblePart = (n > CUT_PART) ? CUT_PART : n;
        printf("\nResult:\n");
        for (i = 0; i < visiblePart; i++)
            printf("%f ", x[i]);
        printf("\n");
    }
    
    if (fileName)
        err = readMatrix(A, b, n, fileName, p, id, MPI_COMM_WORLD, buf);
    else
        initMatrix(A, b, n, p, id);
    
    //RESIDUAL
    if (id == 0)
    {
        for (i = 0 ; i < n; i++)
            buf[i] = x[i];
    }
    
    MPI_Bcast(buf, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    double res = 0., globalRes, val;
    for (i = id; i < n; i+=p)
    {
        int loc_i = i / p;
        
        val = 0.0;
        
        for (j = 0; j < n; ++j)
            val += A[loc_i*n+j] * buf[j];
        
        val -= b[loc_i];
        
        res += val*val;
    }
    MPI_Allreduce(&res, &globalRes, 1, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    
    if (id == 0)
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
        
        printf("\nResidual norm: %e\n", sqrt(globalRes));
        printf("Norm of error: %e\n", sqrt(error));
        printf("Abs Time: %Lf\n", time);
    }
    
    delete[] A;
    delete[] b;
    delete[] buf;
    delete[] x;
    delete[] colOrder;
    
    return 0;
}
