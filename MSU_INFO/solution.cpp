#include "solution.hpp"
#include "functions.hpp"

using namespace std; 

int findSolution(double *A, double *b, double *buf, double *x, int n, int id, int p)
{
    int i, j, k, q, s, err = 0, globalErr, num, globalNum, len, loc_i, loc_j, loc_max_i, minStr, numOfStr;
    double tmp, maxNorm;
    MPI_Status st;
    
    NormInd normInd, globalNormInd;
    int maxStr;
    
    numOfStr = n / p + 1;
    
    for (i = 0; i < n; i++)
    {
        x[i] = 0;
    }
    
    for (i = 0; i < n; ++i)
    {
        minStr = (i % p <= id) ? i - i % p + id : i + (p - i % p) + id;
        
        maxStr = minStr;
        maxNorm = 0;
        
        normInd.thread = -1;
        normInd.norm = maxNorm;
        
        for (s = minStr; s < n; s+=p)
        {
            for (q = 0; q < n; ++q)
            {
                loc_i = s / p;
                if (fabs(A[loc_i*n+i]) > maxNorm)
                {
                    maxNorm = fabs(A[loc_i*n+i]);
                    maxStr = s;
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
        MPI_Bcast(&maxStr, 1, MPI_INT, globalNormInd.thread, MPI_COMM_WORLD);
        
        if ((globalNormInd.thread == (i % p)) && (globalNormInd.thread == id))
        {
            if (maxStr != i)
            {
                loc_i = i / p;
                loc_max_i = maxStr / p;
                
                for (j = 0; j < n; ++j)
                    swap(A[loc_max_i*n+j], A[loc_i*n+j]);
                
                swap(b[loc_max_i], b[loc_i]);
            }
        }
        else if (globalNormInd.thread == id)
        {
            if (maxStr != i)
            {
                len = n;
                memset(buf, 0, (len + 1)*sizeof(double));
                
                int loc_i = maxStr/ p;
                memcpy(buf, A + loc_i * n, len*sizeof(double));
                memcpy(buf + len, b + loc_i, sizeof(double));
                
                MPI_Sendrecv_replace(buf, len + 1, MPI_DOUBLE, i % p, 0 /* tag */, i % p, 0 /* tag */, MPI_COMM_WORLD, &st);
                
                memcpy(A + loc_i * n, buf, len*sizeof(double));
                memcpy(b + loc_i, buf + len, sizeof(double));
            }
        }
        else if ((i % p) == id)
        {
            if (maxStr != i)
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
        
        for (j = id; j < n; j+=p)
        {
            if (j != i)
            {
                loc_j = j / p;
                tmp = A[loc_j*n+i];
                
                for (k = i; k < n; ++k)
                    A[loc_j*n+k] -= buf[k] * tmp;
                
                b[loc_j] -= buf[n] * tmp;
            }
        }
    }
    
    for (i = 0; i < n; ++i)
    {
        int loc_i = i / p;
        buf[i] = 0;
        
        if (id == i % p)
            buf[i] = b[loc_i];
    }
    
    MPI_Allreduce(buf, x, n, MPI_DOUBLE, MPI_SUM, MPI_COMM_WORLD);
    
    return 0;
}
