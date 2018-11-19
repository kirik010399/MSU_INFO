#include "calculatingManager.h"
#include <math.h>
#include <stdlib.h>

void calculateValues(double* matrix, double* vector, double eps, int n)
{
    double sk, r, r1, x1, x2, c, d;
    int i, j, k;
    double *cos, *sin;
    
    Rotation(matrix, n, eps);
    
    cos = (double*)malloc((n-1) * sizeof(double));
    sin = (double*)malloc((n-1) * sizeof(double));
    
    for (k = n; k > 2; --k)
    {
        while (fabs(matrix[(k-1)*n+k-2]) > eps && fabs(matrix[(k-2)*n + k-1]) > eps)
        {
            sk = matrix[(k-1)*n+(k-1)];
            
            for (i = 0; i < k; ++i)
                matrix[i*n+i] -= sk;
            
            //QR
            for (i = 0; i < k-1; ++i)
            {
                r = sqrt(matrix[i*n+i]*matrix[i*n+i] + matrix[(i+1)*n+i]*matrix[(i+1)*n+i]);
                
                if (r < eps)
                {
                    if (matrix[i*n+i] > 0)
                        cos[i] = 1;
                    else
                        cos[i] = -1;
                    
                    sin[i] = 0;
                }
                else
                {
                    r1 = 1/r;
                    cos[i] = matrix[i*n+i] * r1;
                    sin[i] = -matrix[(i+1)*n+i] * r1;
                }
                
                x1 = matrix[i*n+(i+1)];
                x2 = matrix[(i+1)*n+(i+1)];
                
                matrix[i*n+i+1] = x1 * cos[i] - x2 * sin[i];
                matrix[(i+1)*n+(i+1)] = x1 * sin[i] + x2 * cos[i];
                
                if (i != k - 2)
                    matrix[(i+1)*n+(i+2)] *= cos[i];
                
                matrix[i*n+i] = r;
                matrix[(i+1)*n+i] = 0;
            }
            
            //RQ
            for (i = 0; i < k - 1; ++i)
            {
                for (j = i; j < i + 2; ++j)
                {
                    if ((fabs(sin[i]) < eps) && (fabs(cos[i]) < eps))
                        break;
                    
                    x1 = matrix[j*n+i];
                    x2 = matrix[j*n+(i+1)];
                    
                    matrix[j*n+i] = x1 * cos[i] - x2 * sin[i];
                    matrix[j*n+(i+1)] = x1 * sin[i] + x2 * cos[i];
                }
                
                matrix[i*n+(i+1)] = matrix[(i+1)*n+i];
            }
            
            for (i = 0; i < k; ++i)
                matrix[i*n+i] += sk;
        }
    }
    
    if (n >= 2)
    {
        c = matrix[0] + matrix[n+1];
        d = (c * c - 4 * matrix[0] * matrix[n+1] + 4 * matrix[1] * matrix[n]);
        
        if (d < eps)
            d = 0;
        else
            d = sqrt(d);
        
        matrix[0] = (c + d) / 2;
        matrix[n + 1] = (c - d) / 2;
    }
    
    for (i = 0; i < n; ++i)
        vector[i] = matrix[i*n+i];
    
    free(cos);
    free(sin);
}

void Rotation(double* matrix, int n, double eps)
{
    int i, j, k;
    double x, y, r, matrix_ik, matrix_jk, cosPhi, sinPhi;
    double matrix_ii, matrix_ij, matrix_ji, matrix_jj;
    
    for (i = 0; i < n-2; ++i)
    {
        for (j = i+2; j < n; ++j)
        {
            x = matrix[(i+1)*n+i];
            y = matrix[j*n+i];
            
            if (fabs(y) < eps)
                continue;
            
            r = sqrt(x*x+y*y);
            
            if (r < eps)
                continue;
            
            cosPhi = x/r;
            sinPhi = -y/r;
            
            for (k = i; k < n; ++k)
            {
                matrix_ik = matrix[(i+1)*n+k];
                matrix_jk = matrix[j*n+k];
                
                matrix[(i+1)*n+k] = matrix_ik * cosPhi - matrix_jk * sinPhi;
                matrix[j*n+k] = matrix_ik * sinPhi + matrix_jk * cosPhi;
                
                if (k != i+1 && k != j)
                {
                    matrix[k*n+i+1] = matrix[(i+1)*n+k];
                    matrix[k*n+j] = matrix[j*n+k];
                }
            }//*Tij
            
            matrix_ii = matrix[(i+1)*n+i+1];
            matrix_ji = matrix[j*n+i+1];
            matrix_ij = matrix[(i+1)*n+j];
            matrix_jj = matrix[j*n+j];
            
            matrix[(i+1)*n+i+1] = matrix_ii * cosPhi - matrix_ij * sinPhi;
            matrix[j*n+i+1] = matrix_ji * cosPhi - matrix_jj * sinPhi;
            matrix[(i+1)*n+j] = matrix_ii * sinPhi + matrix_ij * cosPhi;
            matrix[j*n+j] = matrix_ji * sinPhi + matrix_jj * cosPhi;//*Tij^t
        }//67
    }
}
