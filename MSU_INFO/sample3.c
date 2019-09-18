#include <stdio.h>
#include <stdlib.h>

int sum_pr(FILE *fin, double *s, double *p);

int main(void)
{
    double s, p;
    int eofFlag;
    
    FILE *fin, *fout;
    
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt","w");
    
    eofFlag = sum_pr(fin, &s, &p);
    
    if (eofFlag != -1)
        fprintf(fout,"Sum: %lf, Prod: %lf\n", s, p);
    
    fclose(fin);
    fclose(fout);
    
    return 0;
}

int sum_pr(FILE *fin, double *s, double *p)
{
    double a;
    
    if (fscanf(fin, "%lf", &a) == EOF)
        return -1;
    
    *s = a;
    *p = a;
    
    while (fscanf(fin, "%lf", &a) != EOF)
    {
        *s += a;
        *p *= a;
    }
    
    return 0;
}


