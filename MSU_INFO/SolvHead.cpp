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
                
                if (i!=j && a[i*n+j] < 1e-100)
                    a[i*n+j] = 0;
            }
        }//97
    }
    
    right = MatrixNorm(a, n) + eps;//95
    left = -right;
    
    eps = fmax(eps, 1e-10);
    
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
    int i, res;
    double x, y, u, v, value, maxx, value1, gam;
    x = a[0] - lam;
    y = 1.0;
    if (x*y < 0)
        res = 1;
    else
        res = 0;
    
    for (i = 1; i < n; ++i)  {
        value = a[i*n+i] - lam;
        value1 = a[i*n + i-1];
        
        maxx = fabs(value1*value1*y);
        
        if (fabs(x) > maxx)
            maxx = fabs(x);
        
        if(maxx < 1e-18)
            maxx = 1e-15;
        
        gam = (1/1e-18)/maxx;
        
        u = gam * (value*x - value1*value1*y);
        v = gam * x;
        
        if (u*x < 0.0)
            ++res;
        x = u;
        y = v;    //страница 97
    }
    
    return res;
}

void Rotation(double* a, int n)  {
    int i, j, k;
    double x, y, r, a_ik, a_jk, cosPhi, sinPhi;
    double a_ii, a_ij, a_ji, a_jj;
    
    for (i = 0; i < n-2; ++i)  {
        for (j = i+2; j < n; ++j)  {
            x = a[(i+1)*n+i];
            y = a[j*n+i];
            
            if (fabs(y) < 1e-100)
                continue;
            r = sqrt(x*x+y*y);
            if (r < 1e-100)
                continue;
            
            cosPhi = x/r;
            sinPhi = -y/r;
            
            for (k = i; k < n; ++k)  {
                a_ik = a[(i+1)*n+k];
                a_jk = a[j*n+k];
                
                a[(i+1)*n+k] = a_ik * cosPhi - a_jk * sinPhi;
                a[j*n+k] = a_ik * sinPhi + a_jk * cosPhi;//*Tij
                
                if (k != i+1 && k != j){
                    a[k*n+i+1] = a[(i+1)*n+k];
                    a[k*n+j] = a[j*n+k];
                }
            }
            a_ii = a[(i+1)*n+i+1];
            a_ji = a[j*n+i+1];
            a_ij = a[(i+1)*n+j];
            a_jj = a[j*n+j];
            
            a[(i+1)*n+i+1] = a_ii * cosPhi - a_ij * sinPhi;
            a[j*n+i+1] = a_ji * cosPhi - a_jj * sinPhi;
            a[(i+1)*n+j] = a_ii * sinPhi + a_ij * cosPhi;
            a[j*n+j] = a_ji * sinPhi + a_jj * cosPhi;
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



