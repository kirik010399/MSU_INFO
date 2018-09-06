#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    double *a, *b;
    int n=0,i=0,j=0, k=0, val=0, l;
    FILE *fin, *fout;
    
    fin = fopen("input.txt","r");
    fout = fopen("output.txt","w");
    
    val = fscanf(fin,"%d",&n);
    
    if (val!=1)
        return -1;
    
    if (n==0)
        return -1;
    
    a = (double*)malloc(n * n * sizeof (double));
    b = (double*)malloc(n * n * sizeof (double));

    for (i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
        {
            val = fscanf(fin,"%lf",&a[i*n+j]);
            if (val!=1)
                return -1;
            k++;
        }
    }
    
    if (k!=n*n)
        return -1;
    
    for (i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
        {
            for (l = 0; l < n; ++l)
            {
                b[i*n+j]+=a[i*n+l]*a[l*n+j];
            }
        }
    }
    
    for (i=0;i<n;++i)
    {
        for(j=0;j<n;++j)
        {
            fprintf(fout,"%lf ",b[i*n+j]);
        }
        fprintf(fout,"\n");
    }
    
    return 0;
}
