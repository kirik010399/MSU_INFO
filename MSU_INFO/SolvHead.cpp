#include "SolvHead.hpp"
#include <math.h>
#include <iostream>

using namespace std;

void calculateValues(double* a, double* res, double eps, int k, int n)
{
    int i, j, alp;
    double left, right;
    double maxA, maxB;
    
    for (i = 0; i < n; ++i)
        res[i] = 0;
    
    Rotation(a, n);
    
    maxA = a[0];
    maxB = a[1];
    
    for (i = 1; i < n; ++i){
        if (fabs(a[i*n+i]) > maxA)
            maxA = fabs(a[i*n+i]);
        
        if (i<n-1){
            if (fabs(a[i*n + i+1]) > maxB)
                maxB = fabs(a[i*n + i+1]);
        }
    }
    
    alp = 4*fmax(maxA, maxB);
    
    if( fabs(alp) > 1e-18 ){
        for (i = 0; i < n; ++i){
            for (j = 0; j < n; ++j){
                a[i*n+j]/=alp;
                
                if (i!=j && a[i*n+j] < 1e-18)
                    a[i*n+j] = 0;
            }
        }//97
    }
    
    right = MatrixNorm(a, n) + eps;//95
    left = -right;
    
    values(a, n, res, left, right, k, eps);
    
    for (i = 0; i < n; ++i)
        res[i]*=alp;
}

void values(double *a, int n, double *res, double left, double right, int k, double eps)  {
    double c;
    
    while(right-left > eps)  {
        c = (left+right)/2;
        
        if (n_(a, n, c) < k)
            left = c;
        else
            right = c;
    }
    
    res[k-1] = (left+right)/2;
}

int n_(double* a, int n, double lam)  {
    int k, m;
    double x, y, u, v, A, maxx, B, gam;
    x = a[0] - lam;
    y = 1.0;
    if (x*y < 0)
        m = 1;
    else
        m = 0;
    
    for (k = 1; k < n; ++k)  {
        A = a[k*n+k] - lam;
        B = a[k*n + k-1];
        
        maxx = fmax(fabs(x), fabs(B*B*y));
        
        if(maxx < 1e-18)
            maxx = 1e-15;
        
        gam = (1/1e-18)/maxx;
        
        u = gam * (A*x - B*B*y);
        v = gam * x;
        
        if (u*x < 0.0)
            ++m;
        x = u;
        y = v;    //страница 97
    }
    
    return m;
}

void Rotation(double* a, int n){
    int i, j, k;
    double x, y, r, a_ik, a_jk, CosPhi, SinPhi;
    double a_ii, a_ij, a_ji, a_jj;
    
    for (i = 0; i < n-2; ++i){
        for (j = i+2; j < n; ++j){
            x = a[(i+1)*n+i];
            y = a[j*n+i];
            
            if (fabs(y) < 1e-18)
                continue;
            r = sqrt(x*x+y*y);
            if (r < 1e-18)
                continue;
            
            CosPhi = x/r;
            SinPhi = -y/r;
            
            for (k = i; k < n; ++k){
                a_ik = a[(i+1)*n+k];
                a_jk = a[j*n+k];
                
                a[(i+1)*n+k] = a_ik * CosPhi - a_jk * SinPhi;
                a[j*n+k] = a_ik * SinPhi + a_jk * CosPhi;//*Tij
                
                if (k != i+1 && k != j){
                    a[k*n+i+1] = a[(i+1)*n+k];
                    a[k*n+j] = a[j*n+k];
                }
            }
            
            a_ii = a[(i+1)*n+i+1];
            a_ji = a[j*n+i+1];
            a_ij = a[(i+1)*n+j];
            a_jj = a[j*n+j];
            
            a[(i+1)*n+i+1] = a_ii * CosPhi - a_ij * SinPhi;
            a[j*n+i+1] = a_ji * CosPhi - a_jj * SinPhi;
            a[(i+1)*n+j] = a_ii * SinPhi + a_ij * CosPhi;
            a[j*n+j] = a_ji * SinPhi + a_jj * CosPhi;
        }//страница   63 *Tij T
    }
}

double MatrixNorm(double* a, int n)  {
    int i, j;
    double sum, res;
    res = 0.0;
    for (i = 0; i < n; ++i)  {
        sum = 0.0;
        for (j = 0; j < n; ++j)
            sum += fabs(a[i*n+j]);
        
        if (res < sum)
            res = sum;
    }
    return res;
}



