#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double weight(double *a, int str, int n, int m);
void sw(double *a, int str1, int str2, int n, int m);
void sort_mult(double *a, double *b, int n, int m);

int main(void)
{
    double *a, *b;
    int n=0, m=0, i=0, j=0, k=0, val=0;
    FILE *fin, *fout;
    
    fin = fopen("input.txt","r");
    fout = fopen("output.txt","w");
    
    val = fscanf(fin,"%d",&n);
    
    if (val!=1)
        return -1;
    
    val = fscanf(fin,"%d",&m);
    
    if (val != 1)
        return -1;
    
    if (n==0 || m==0)
        return -1;
    
    a = (double*)malloc(n * m * sizeof (double));
    b = (double*)malloc(n * sizeof (double));
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j)
        {
            val = fscanf(fin,"%lf",&a[i*m+j]);
            if (val!=1)
                return -1;
            k++;
        }
    }
    
    if (k!=n*m)
        return -1;
    
    sort_mult(a, b, n, m);
    
    fprintf (fout, "%d %d\n", n, m);
    
    for (i = 0; i < n;++i)
    {
        for(j = 0; j < m;++j)
        {
            fprintf(fout,"%lf ",a[i*m+j]);
        }
        fprintf(fout,"\n");
    }
    
    fprintf(fout,"\n");
    
    for (j = 0; j < n; ++j)
        fprintf(fout,"%lf ",b[j]);
    
    free(a);
    free(b);
    fclose(fin);
    fclose(fout);
    
    return 0;
}

void sort_mult(double *a, double *b, int n, int m)
{
    int k = 0, i = 0, j = 0;
    
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n-1; ++j)
        {
            if (weight(a,j,n,m) < weight(a,j+1,n,m))
            {
                sw(a, j, j+1, n, m);
            }
        }
    }
    
    k = 0;
    
    for (i = 0; i < n; ++i)
        b[i] = 0;
    
    for (i = 0; i < n; ++i)
    {
        for (j = 0; j < m; ++j)
        {
            b[k] += a[i*m+j]*a[j];
        }
        ++k;
    }
}

double weight(double *a, int str, int n, int m)
{
    int j = 0;
    double res = 0.0;
    
    if (m == 1)
        return 0;
    
    for (j = 0; j < m-1; ++j)
    {
        if (a[str*m+j+1]-a[str*m+j] > 0)
            res += a[str*m+j+1] - a[str*m+j];
    }
    
    return res;
}

void sw(double *a, int str1, int str2, int n, int m)
{
    double t = 0;
    int j = 0;
    
    for (j = 0; j < m; ++j)
    {
        t = a[str1*m+j];
        a[str1*m+j] = a[str2*m+j];
        a[str2*m+j] = t;
    }
}
