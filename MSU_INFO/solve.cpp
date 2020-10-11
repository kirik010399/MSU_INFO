#include "solve.hpp"
#include <math.h>

using namespace std;

int solve(double* a, double* b, double* x, int *ind, int n)
{
int i, j, k;
double tmp;
int maxs, maxc;

for (i=0; i<n; i++) ind[i] = i;

for (i=0; i<n; i++)
    {
    tmp = fabs(a[i*n+i]);
    maxs = i;
    maxc = i;
    
    for (j=i; j<n; j++)
        {
        for (k=i; k<n; k++)
            {
            if (fabs(a[j*n+k])>tmp)// Search for max in matrix
                {
                tmp=fabs(a[j*n+k]);
                maxs=j;
                maxc=k;
                }
            }
        }
    
    if (fabs(tmp)<1e-30) return -1;
    
    for (j=0; j<n; j++) swap(a[maxs*n+j],a[i*n+j]);
    for (j=0; j<n; j++) swap(a[j*n+maxc],a[j*n+i]);
    swap(b[maxs],b[i]);
    swap(ind[i],ind[maxc]);
    
    for(j=0; j<n; j++)
        {
        if (i!=j)
            {
            tmp=a[j*n+i]/a[i*n+i];
            for(k=i; k<n; k++) a[j*n+k]-=tmp*a[i*n+k];
            b[j]-=tmp*b[i];
            }
        }
}
for (i=0; i<n; i++) x[ind[i]]=b[i]/a[i*n+i];
    
return 0;
}

