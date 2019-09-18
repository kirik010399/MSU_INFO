#include <stdio.h>
#include <stdlib.h>

int sum(FILE *fin, double *s);

int main(void)
{
    double s;
    int eofFlag;
    
    FILE *fin, *fout;
    
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt","w");
    
    eofFlag = sum(fin, &s);
    
    if (eofFlag != -1)
        fprintf(fout,"Sum: %lf\n", s);
    
    fclose(fin);
    fclose(fout);
    
    return 0;
}

int sum(FILE *fin, double *s)
{
    double a;
    
    if (fscanf(fin, "%lf", &a) == EOF)
        return -1;
    
    *s = a;
    
    while (fscanf(fin, "%lf", &a) != EOF)
        *s += a;
    
    return 0;
}


