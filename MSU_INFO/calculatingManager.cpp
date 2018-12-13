#include "calculatingManager.hpp"
#include <math.h>
#include <iostream>

using namespace std;

void calculateValues(double* a, double* result, double eps, int n)
{
    double *x1, *x2;
    double z = MatrixNorm(n, a);
    
    x1 = new double [n];
    x2 = new double [n];
    NearTriangle(n, a, x1, eps);
    
    z*=eps;
    for(int i = 0; i<n-2; ++i)
    {
        result[n-1-i] = answer(n, n-i, a, x1, x2, eps,z);
    }
    
    double A = 1;
    double B = -(a[0]+a[n+1]);
    double C = (a[0]*a[n+1]-a[n]*a[1]);
    double di = sqrt(B*B-4*A*C);
    
    result[0]=(-B-di)/(2*A);
    result[1]=(-B+di)/(2*A);
    
    delete []x1;
    delete []x2;
}

double answer(int n,int p, double* a,double* x1,double* x2, double eps,double z)
{
    while(fabs(a[n*(p-1)+p-2]) > z)
    {
        double t = a[n*(p-1)+(p-1)];
        
        if(fabs(a[(p-1)*n+(p-1)])<eps)
            t += a[n*(p-1)+(p-2)]/2;
        
        for(int i = 0; i<p; ++i)
            a[i+i*n]-=t;
        
        realization(n,p,a,x1, x2,eps);
        
        for(int i = 0; i<p; ++i)
            a[i+i*n] += t;
    }
    return a[(p-1)*n+(p-1)];
}

void realization(int n, int p, double* a,double* x1, double* x2,double eps)
{
    for(int i = 0; i<p-1; ++i)
    {
        if(fabs(a[(i+1)*n+i]) < eps)
        {
            x1[i]=0.;
            x2[i]=1.;
        }
        else
        {
            double s = a[(i+1)*n+i]*a[(i+1)*n+i];
            double MatrixNorm = sqrt(s+a[i*n+i]*a[i*n+i]);
            
            x1[i]=a[i*n+i]-MatrixNorm;
            x2[i]=a[(i+1)*n+i];
            
            double normaX = sqrt(s+x1[i]*x1[i]);
            x1[i]/=normaX;
            x2[i]/=normaX;
            
            a[i+i*n] = MatrixNorm;
        }
        
        for(int k = 0; k < p; ++k)
        {
            double skal = 0.;
            skal = x1[i]*a[i*n+k]+x2[i]*a[(i+1)*n+k];
            skal*=2;
            a[i*n+k] -= skal*x1[i];
            a[(i+1)*n+k] -= skal*x2[i];
        }
        
        a[(i+1)*n+i]=0.;
    }
    
    for(int i = 0; i<p-1; ++i)
    {
        for(int k = 0; k<p; ++k)
        {
            double skal = 0.;
            skal = x1[i]*a[k*n+i] + x2[i] * a[k*n+(i+1)];
            skal *= 2;
            a[k*n+i] -= skal * x1[i];
            a[k*n+(i+1)] -= skal * x2[i];
        }
    }
}

double MatrixNorm(int n,double* a)
{
    double Max = 0.;
    for(int i = 0; i<n; ++i)
    {
        double sum = 0.;
        
        for(int j = 0; j<n; ++j)
            sum += fabs(a[i*n+j]);
        
        if(Max<sum)
            Max = sum;
    }
    return Max;
}

void NearTriangle(int n, double* a, double* x, double eps)
{
    for(int i = 0; i < n-2; ++i)
    {
        double s = 0.;
        
        for(int j = i+2; j < n; ++j)
        {
            s += a[i+j*n]*a[i+j*n];
            x[j]=a[i+j*n];
        }
        
        if(s<1e-10)
            continue;
        
        double norma = sqrt(s+a[i+n*(i+1)]*a[i+n*(i+1)]);
        x[i+1]=a[i+n*(i+1)]-norma;
        
        double normaX = 1/sqrt(s+x[i+1]*x[i+1]);
        
        for(int j = i+1; j<n; ++j)
            x[j]*=normaX;
        
        for(int k = i; k<n; ++k)
        {
            double skal = 0.;
            
            for(int t = i+1; t<n; ++t)
                skal += x[t]*a[t*n+k];
            
            skal*=2;
            for(int j = i+1; j<n; ++j)
                a[k+n*j]-=skal*x[j];
        }
        
        for(int k = 0; k<n; ++k)
        {
            double skal = 0;
            
            for(int t = i+1; t<n; ++t)
                skal += x[t]*a[k*n+t];
            
            skal*=2;
            for(int j = i+1 ;j<n; ++j)
                a[j+n*k]=a[j+n*k]-skal*x[j];
        }
    }
}

