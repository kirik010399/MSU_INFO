#include "func.hpp"
#include <stdio.h>
#include <math.h>

double f(int k, int n, int i, int j)
{
if (k==1) return n-fmax(i,j)+1;
if (k==2) return fmax(i,j);
if (k==3) return fabs(i-j);
if (k==4) return 1.0/(i+j+1);

return -1;
}

int enter(double* a, double *b, int n, int k, FILE* in)
{
int i, j;

for (i=0; i<n; i++)
    {
    b[i]=0;
    
    for (j=0; j<n; j++)
        {
        if (k==0)
            {
            if (fscanf(in, "%lf", &a[i*n+j])!=1) return -1;
            }
        else
            {
            a[i*n+j] = f(k,n,i,j);
            }
        if (j%2==0) b[i]+=a[i*n+j];
        }
    }

return 0;
}

void print(double* a, int l, int n, int m)
{
int i, j;

for (i=0; i<fmin(l,m); i++)
    {
    for (j=0; j<m; j++) printf("%10.3e ", a[i*n+j]);
    printf("\n");
    }
}

double norm(double* a, double* b, double* x, int n)
{
int i, j;
double norm1=0.0, norm2=0.0;
double tmp;

for (i=0; i<n; i++)
    {
    tmp=0.0;
    for (j=0; j<n; j++) tmp+=a[i*n+j] * x[j];
    tmp-=b[i];
    norm1+=tmp*tmp;
    }

norm2 = 0.0;

for (i=0; i<n; i++) norm2+=b[i]*b[i];
    
return sqrt(norm1)/sqrt(norm2);
}

double error(double *x, int n)
{
double error = 0;
int i;

for (i=0; i<n; i++)
    {
    if (i%2==0) error+=(x[i]-1)*(x[i]-1);
    else error+=x[i]*x[i];
    }
return sqrt(error);
}