#include "solution.hpp"
#include "functions.hpp"

using namespace std; 

int findSolution(double *A, double *b, double *buf, double *x, int *colOrder, int n, int id, int p)
{
    int i, j, k, s, q, err = 0, globalErr, num, globalNum, len, loc_i, loc_j, loc_max_i, minStr, numOfStr;
    double tmp, maxNorm;
    MPI_Status st;
    
    NormInd normInd, globalNormInd;
    int maxPos[2];
    int maxStr, maxCol;
    
    numOfStr = n / p + 1;
    
    for (i = 0; i < n; i++)
    {
        x[i] = 0;
        colOrder[i] = i;
    }
    
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
    }
    
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
    
    return 0;
}
