#include "functions.hpp"
#include <iostream>

using namespace std;

int readMatrix(double *A, double *b, int n, const char *fileName, int p, int k, MPI_Comm com, double *buf)
{
    FILE *in = 0;
    int i, j;
    int err = 0, dst;
    double sum;
    
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
            
            sum = 0.;
            for (j = 1; j < n; j += 2)
                sum += A[loc_i * n + j];
            b[i] = sum;
        }
        MPI_Bcast(b + i, 1, MPI_DOUBLE, dst, com);
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
    double sum;
    
    for (i = 0; i < n; i++)
    {
        owner = i % p;
        
        if (k == owner)
        {
            int loc_i = i / p;
            
            for (j = 0; j < n; j++)
                A[loc_i * n + j] = n - ((i > j) ? i : j);
            
            sum = 0.;
            for (j = 1; j < n; j += 2)
                sum += A[loc_i * n + j];
            b[i] = sum;
        }
        MPI_Bcast(b + i, 1, MPI_DOUBLE, owner, MPI_COMM_WORLD);
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








//double getNorm(double *B, int n, int m)
//{
//    int i, j;
//    double curSum, norm = 0.;
//    double *b;
//
//    for (i = 0; i < n; i++)
//    {
//        curSum = 0.;
//        b = B + i * m;
//
//        for (j = 0; j < m; j++)
//            curSum += fabs(b[j]);
//
//        if (curSum > norm)
//            norm = curSum;
//    }
//    return norm;
//}


double get_abs_time()
{
    struct timeval tm;
    gettimeofday(&tm, 0);
    
    return (double) tm.tv_sec + (double) tm.tv_usec/1e6;
}

int findSolution(int n, int m, const char *fileName, int id, int p)
{
    double *A, *b, *x, *buf, *B, *bufColumn;
    int i, j, z, s, q, err = 0, globalErr, num, globalNum, len;
    double tmp, minNorm;
    int numOfBlockStr = (n / m / p + 1) * m;
    MPI_Status st;
    
    NormInd normInd, globalNormInd;
    int minPos[2];
    int minStr, minCol;
    int k = n / m;
    int l = n - k * m;
    double initialNorm = DBL_MAX;
    int *colOrder;
    
    A = new double[n * numOfBlockStr];
    b = new double[numOfBlockStr];
    buf = new double[m * n + numOfBlockStr];
    bufColumn = new double[m];
    B = new double[3 * m * m];
    if (id == 0)
    {
        x = new double[n];
        colOrder = new int[k + 1];
        
        for (i = 0; i <= k; i++)
            colOrder[i] = i;
    }
    else
    {
        colOrder = new int[0];
        x = new double[1];
    }
    
    if (fileName)
        err = readMatrix(A, b, n, m, fileName, p, id, MPI_COMM_WORLD, buf);
    else
        initMatrix(A, b, n, m, p, id);
    
    if (err)
    {
        if (id == 0)
            printf("Error: can't read matrix!\n");
        delete[] x;
        delete[] colOrder;
        delete[] A;
        delete[] b;
        delete[] buf;
        delete[] bufColumn;
        delete[] B;
        
        return -1;
    }
    
    printMatrix(A, b, n, m, 0, p, id, MPI_COMM_WORLD, buf);
    
    err = 0;
    double globalNorm;
    double norm = getNorm(A, numOfBlockStr, n);
    
    MPI_Allreduce(&norm, &globalNorm, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
    
    for (i = 0; i < k; i++)
    {
        minStr = (i % p <= id) ? i - i % p + id : i + (p - i % p) + id;
        minCol = i;
        minNorm = initialNorm;
        
        normInd.thread = -1;
        minPos[0] = -1;
        minPos[1] = -1;
        normInd.norm = minNorm;
        
        for (s = minStr; s < k; s+=p)
        {
            for (q = i; q < k; q++)
            {
                getBlock(A, n, m, p, s, q, B);
                if ((inverseMatrix(B, m, globalNorm) != -1) && ((tmp = getNorm(B + m * m, m)) < minNorm))
                {
                    minNorm = tmp;
                    minStr = s;
                    minCol = q;
                }
            }
        }
        
        num = 0; err = 0;
        globalNum = 0; globalErr = 0;
        
        s = (i % p <= id) ? i - i % p + id : i + (p - i % p) + id;
        if (s < k)
        {
            num = 1;
            normInd.thread = id;
            minPos[0] = minStr;
            minPos[1] = minCol;
            normInd.norm = minNorm;
            
            if ((initialNorm - minNorm) < EPS * globalNorm)
                err = 1;
        }
        
        MPI_Allreduce(&num, &globalNum, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
        MPI_Allreduce(&err, &globalErr, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
        
        if (globalNum == globalErr)
        {
            if (id == 0)
                printf("Error: there is no invertible block! (no main element)\n");
            delete[] x;
            delete[] colOrder;
            delete[] A;
            delete[] b;
            delete[] buf;
            delete[] bufColumn;
            delete[] B;
            
            return -1;
        }
        
        MPI_Allreduce(&normInd, &globalNormInd, 1, MPI_DOUBLE_INT, MPI_MINLOC, MPI_COMM_WORLD);
        MPI_Bcast(&minPos, 2, MPI_INT, globalNormInd.thread, MPI_COMM_WORLD);
        
        if ((id == 0) && (minPos[1] != i))
        {
            tmp = colOrder[i];
            colOrder[i] = colOrder[minPos[1]];
            colOrder[minPos[1]] = tmp;
        }
        
        if ((globalNormInd.thread == (i % p)) && (globalNormInd.thread == id))
        {
            if (minPos[1] != i)
                swapColumns(A, n, m, p, id, i, minPos[1], B);
            if (minPos[0] != i)
                swapStrings(A, n, m, p, i, minPos[0], B, b);
        }
        else if (globalNormInd.thread == id)
        {
            if (minPos[1] != i)
                swapColumns(A, n, m, p, id, i, minPos[1], B);
            
            if (minPos[0] != i)
            {
                len = n * m;
                memset(buf, 0, (len + m)*sizeof(double));
                
                int loc_i = minPos[0] / p;
                memcpy(buf, A + loc_i * n * m, len*sizeof(double));
                memcpy(buf + len, b + loc_i * m, m*sizeof(double));
                
                MPI_Sendrecv_replace(buf, len + m, MPI_DOUBLE, i % p, 0 /* tag */, i % p, 0 /* tag */, MPI_COMM_WORLD, &st);
                
                memcpy(A + loc_i * n * m, buf, len*sizeof(double));
                memcpy(b + loc_i * m, buf + len, m*sizeof(double));
            }
        }
        else if ((i % p) == id)
        {
            if (minPos[1] != i)
                swapColumns(A, n, m, p, id, i, minPos[1], B);
            
            if (minPos[0] != i)
            {
                len = n * m;
                memset(buf, 0, (len + m)*sizeof(double));
                
                int loc_i = i / p;
                memcpy(buf, A + loc_i * n * m, len*sizeof(double));
                memcpy(buf + len, b + loc_i * m, m*sizeof(double));
                
                MPI_Sendrecv_replace(buf, len + m, MPI_DOUBLE, globalNormInd.thread, 0 /* tag */, globalNormInd.thread, 0 /* tag */, MPI_COMM_WORLD, &st);
                
                memcpy(A + loc_i * n * m, buf, len*sizeof(double));
                memcpy(b + loc_i * m, buf + len, m*sizeof(double));
            }
        }
        else
        {
            if (minPos[1] != i)
                swapColumns(A, n, m, p, id, i, minPos[1], B);
        }
        
        if (i % p == id)
        {
            getBlock(A, n, m, p, i, i, B);
            inverseMatrix(B, m, globalNorm);
            
            for (j = i+1; j < k; j++)
            {
                getBlock(A, n, m, p, i, j, B);
                multMatrices(B+m*m, B, B + 2 * m * m, m);
                putBlock(A, n, m, p, i, j, B + 2 * m * m);
            }
            
            getBlock(A, n, m, p, i, k, B);
            multBlocks(B+m*m, m, m, B, m, l, B + 2 * m * m);
            putBlock(A, n, m, p, i, k, B + 2 * m * m);
            
            matrixMultVector(B+m*m, b, i, n, m, p);
        }
        // Ended multing i string
        
        len = m * n;
        if (id == (i % p))
        {
            memset(buf, 0, (len + m)*sizeof(double));
            
            int loc_i = i / p;
            memcpy(buf, A + loc_i * n * m, len*sizeof(double));
            memcpy(buf + len, b + loc_i * m, m*sizeof(double));
        }
        
        MPI_Bcast(buf, len + m, MPI_DOUBLE, i % p, MPI_COMM_WORLD); // Send i string to all processes
        
        for (j = id; j < i; j+=p)
        {
            getBlock(A, n, m, p, j, i, B);
            for (z = i + 1; z < k; z++)
            {
                getBufBlock(buf, n, m, i, z, B+m*m);
                multMatrices(B, B + m * m, B + 2 * m * m, m);
                getBlock(A, n, m, p, j, z, B+m*m);
                diffBlocks(B + m * m, B + 2 * m * m, m, m);
                putBlock(A, n, m, p, j, z, B + m * m);
            }
            
            getBufBlock(buf, n, m, i, k, B+m*m);
            multBlocks(B, m, m, B + m  *m, m, l, B + 2 * m * m);
            getBlock(A, n, m, p, j, k, B + m * m);
            diffBlocks(B+m*m, B + 2 * m * m, m, l);
            putBlock(A, n, m, p, j, k, B + m *m);
            
            getBufColumn(buf, n, m, i, bufColumn);
            clearColumn(b, bufColumn, B, n, m, p, i, j);
        }
        
        minStr = ((i + 1) % p <= id) ? i + 1 - (i + 1) % p + id : i + 1 + (p - (i + 1) % p) + id;
        for (j = minStr; j < k; j+=p)
        {
            getBlock(A, n, m, p, j, i, B);
            for (z = i + 1; z < k; z++)
            {
                getBufBlock(buf, n, m, i, z, B+m*m);
                multMatrices(B, B + m * m, B + 2 * m * m, m);
                getBlock(A, n, m, p, j, z, B + m * m);
                diffBlocks(B + m * m, B + 2 * m * m, m, m);
                putBlock(A, n, m, p, j, z, B+m*m);
            }
            
            getBufBlock(buf, n, m, i, k, B+m*m);
            multBlocks(B, m, m, B + m * m, m, l, B + 2 * m * m);
            getBlock(A, n, m, p, j, k, B+m*m);
            diffBlocks(B+m*m, B+2*m*m, m, l);
            putBlock(A, n, m, p, j, k, B+m*m);
            
            getBufColumn(buf, n, m, i, bufColumn);
            clearColumn(b, bufColumn, B, n, m, p, i, j);
        }
        
        if (k % p == id)
        {
            getBlock(A, n, m, p, k, i, B);
            for (z = i + 1; z < k; z++)
            {
                getBufBlock(buf, n, m, i, z, B+m*m);
                multBlocks(B, l, m, B+m*m, m, m, B+2*m*m);
                getBlock(A, n, m, p, k, z, B+m*m);
                diffBlocks(B+m*m, B+2*m*m, l, m);
                putBlock(A, n, m, p, k, z, B+m*m);
            }
            
            getBufBlock(buf, n, m, i, k, B+m*m);
            multBlocks(B, l, m, B+m*m, m, l, B+2*m*m);
            getBlock(A, n, m, p, k, k, B+m*m);
            diffBlocks(B+m*m, B+2*m*m, l, l);
            putBlock(A, n, m, p, k, k, B+m*m);
            
            getBufColumn(buf, n, m, i, bufColumn);
            clearColumn(b, bufColumn, B, n, m, p, i, k);
        }
        
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
    if (l > 0)
    {
        if (k % p == id)
        {
            getBlock(A, n, m, p, k, k, B);
            
            if (inverseMatrix(B, l, globalNorm) == -1)
                err = 1;
        }
        
        MPI_Bcast(&err, 1, MPI_INT, k % p, MPI_COMM_WORLD);
        if (err)
        {
            if (id == 0)
                printf("Error: there is no invertible block!\n");
            delete[] x;
            delete[] colOrder;
            delete[] A;
            delete[] b;
            delete[] buf;
            delete[] bufColumn;
            delete[] B;
            
            return -1;
        }
        
        len = l * n;
        
        if (id == k % p)
        {
            matrixMultVector(B + l * l, b, k, n, m, p);
            
            memset(buf, 0, (len + l) * sizeof(double));
            
            int loc_i = k / p;
            memcpy(buf, A + loc_i * n * m, len * sizeof(double));
            memcpy(buf + len, b + loc_i * m, l * sizeof(double));
        }
        MPI_Bcast(buf, len + l, MPI_DOUBLE, k % p, MPI_COMM_WORLD);
        
        for (i = id; i < k; i += p)
        {
            getBlock(A, n, m, p, i, k, B);
            getBufColumn(buf, n, m, k, bufColumn);
            clearColumn(b, bufColumn, B, n, m, p, k, i);
        }
        
        MPI_Barrier(MPI_COMM_WORLD);
    }
    
    //    printMatrix(A, b, n, m, 0, p, id, MPI_COMM_WORLD, buf);
    
    for (i = 0; i < k + ((l > 0) ? 1 : 0); i++)
    {
        int loc_i = i / p;
        int height = (i == k) ? l : m;
        
        if (id == i % p)
        {
            if (id != 0)
                MPI_Send(b + loc_i * m, height, MPI_DOUBLE, 0, 0 /* tag */, MPI_COMM_WORLD);
            else
                memcpy(buf, b + loc_i * m, height * sizeof(double));
        }
        else if (id == 0)
        {
            MPI_Recv(buf, height, MPI_DOUBLE, i % p, 0 /* tag */, MPI_COMM_WORLD, &st);
        }
        
        if (id == 0)
        {
            for (j = 0; j < height; j++)
                x[colOrder[i] * m + j] = buf[j];
        }
    }
    
    MPI_Barrier(MPI_COMM_WORLD);
    
    if (id == 0)
    {
        int visiblePart = (n > CUT_PART) ? CUT_PART : n;
        printf("\nResult:\n");
        for (i = n - visiblePart; i < n; i++)
            printf("%f\n", x[i]);
    }
    
    if (fileName)
        err = readMatrix(A, b, n, m, fileName, p, id, MPI_COMM_WORLD, buf);
    else
        initMatrix(A, b, n, m, p, id);
    
    //RESIDUAL
    double sum;
    int i1, j1, q1, q2;
    
    if (id == 0)
    {
        for (i = 0 ; i < n; i++)
            buf[i] = x[i];
    }
    
    MPI_Bcast(buf, n, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    
    for (i = id; i <= k; i+=p)
    {
        int loc_i = i / p;
        for (j = 0; j <= k; j++)
        {
            getBlock(A, n, m, p, i, j, B);
            q1 = (i != k) ? m : l;
            q2 = (j != k) ? m : l;
            for (i1 = 0; i1 < q1; i1++)
            {
                sum = 0.;
                for (j1 = 0; j1 < q2; j1++)
                    sum += B[i1 * q2 + j1] * buf[j * m + j1];
                b[loc_i * m + i1] -= sum;
            }
        }
    }
    
    double maxResidual = 0;
    for (i = id; i <= k; i+=p)
    {
        int loc_i = i / p;
        
        int height = (i == k) ? l : m;
        for (j = 0; j < height; j++)
            maxResidual = max(maxResidual, fabs(b[loc_i * m + j]));
    }
    
    double globalResidual;
    MPI_Allreduce(&maxResidual, &globalResidual, 1, MPI_DOUBLE, MPI_MAX, MPI_COMM_WORLD);
    
    if (id == 0)
    {
        double maxError = 0.;
        for (i = 0; i < n; i++)
            if ((tmp = fabs(x[i] - i % 2)) > maxError)
                maxError = tmp;
        
        printf("\nResidual norm: %e\n", globalResidual);
        printf("Norm of error: %e\n", maxError);
    }
    
    delete[] A;
    delete[] b;
    delete[] buf;
    delete[] bufColumn;
    delete[] B;
    delete[] x;
    delete[] colOrder;
    
    return 0;
}
