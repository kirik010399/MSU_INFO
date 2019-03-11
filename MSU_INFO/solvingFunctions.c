#include "solvingFunctions.h"
#include <math.h>

void calculateValues(double *matrix, double *result, double *cos, double *sin, int n, float eps, int debug)
{
    int i, j, k;
    double acc;
    double shift;
    double tr, det;
    double a,b,c,d;
    double D;
    
    Rotation(matrix, n);
    acc = MatrixNorm(matrix, n) * eps;
    
    for (k = n-1; k >= 2; --k){
        while (fabs(matrix[k*n+k-1]) > acc){
            shift = matrix[k*n+k];
            
            for (j = 0; j <= k; ++j)
                matrix[j*n+j] -= shift;
            
            QR(matrix, n, k+1, cos, sin);
            RQ(matrix, n, k+1, cos, sin);
        
            for (j = 0; j <= k; ++j)
                matrix[j*n+j] += shift;
        }
    }
    
    //l^2-tr*l+det=0
    
    a = matrix[0*n+0];
    b = matrix[0*n+1];
    c = matrix[1*n+0];
    d = matrix[1*n+1];

    tr = a+d;
    det = a*d-b*c;
    
    D = tr*tr-4*1*det;

    matrix[0*n+0] = (tr + sqrt(D))/2;
    matrix[1*n+1] = (tr - sqrt(D))/2;
    
    for (i = 0; i < n; ++i)
        result[i] = matrix[i*n+i];
}

void QR(double* matrix, int n, int k, double* cos, double* sin)
{
    int i, j;
    double x, y, r;
    
    for (i = 0; i < k-1; ++i){
        x = matrix[i*n+i];
        y = matrix[(i+1)*n+i];
        
        r = sqrt(x*x+y*y);
        
        if (r < 1e-18){
            cos[i] = 1.0;
            sin[i] = 0.0;
        }
        else{
            cos[i] = x/r;
            sin[i] = -y/r;
        }
        
        for (j = i; j < n; ++j){
            matrix[i*n+j] = x * cos[i] - y * sin[i];
            matrix[(i+1)*n+j] = x * sin[i] + y * cos[i];//*Tij
        }
    }
}

void RQ(double* matrix, int n, int k, double* cos, double* sin)
{
    int i, j;
    double x, y;
    
    for (i = 0; i < k - 1; ++i){
        for (j = 0; j < i + 2; ++j){
            x = matrix[j*n+i];
            y = matrix[j*n+i+1];
            
            matrix[j*n+i] = x * cos[i] - y * sin[i];
            matrix[j*n+i+1] = x * sin[i] + y * cos[i];
        }
    }
}

void Rotation(double* matrix, int n){
    int i, j, k;
    double x, y, r, matrix_ik, matrix_jk, CosPhi, SinPhi;
    double matrix_ii, matrix_ij, matrix_ji, matrix_jj;
    
    for (i = 0; i < n-2; ++i){
        for (j = i+2; j < n; ++j){
            x = matrix[(i+1)*n+i];
            y = matrix[j*n+i];
            
            if (fabs(y) < 1e-18)
                continue;
            
            r = sqrt(x*x+y*y);
            
            if (r < 1e-18)
                continue;
            
            CosPhi = x/r;
            SinPhi = -y/r;
            
            for (k = i; k < n; ++k){
                matrix_ik = matrix[(i+1)*n+k];
                matrix_jk = matrix[j*n+k];
                
                matrix[(i+1)*n+k] = matrix_ik * CosPhi - matrix_jk * SinPhi;
                matrix[j*n+k] = matrix_ik * SinPhi + matrix_jk * CosPhi;//*Tij
                
                if (k != i+1 && k != j){
                    matrix[k*n+i+1] = matrix[(i+1)*n+k];
                    matrix[k*n+j] = matrix[j*n+k];
                }
            }
            
            matrix_ii = matrix[(i+1)*n+i+1];
            matrix_ji = matrix[j*n+i+1];
            matrix_ij = matrix[(i+1)*n+j];
            matrix_jj = matrix[j*n+j];
            
            matrix[(i+1)*n+i+1] = matrix_ii * CosPhi - matrix_ij * SinPhi;
            matrix[j*n+i+1] = matrix_ji * CosPhi - matrix_jj * SinPhi;
            matrix[(i+1)*n+j] = matrix_ii * SinPhi + matrix_ij * CosPhi;
            matrix[j*n+j] = matrix_ji * SinPhi + matrix_jj * CosPhi;
        }//страница   63 *Tij T
    }
}

double MatrixNorm(double* matrix, int n)  {
    int i, j;
    double sum, res;
    res = 0.0;
    for (i = 0; i < n; ++i)  {
        sum = 0.0;
        for (j = 0; j < n; ++j)
            sum += fabs(matrix[i*n+j]);
        
        if (res < sum)
            res = sum;
    }
    return res;
}

