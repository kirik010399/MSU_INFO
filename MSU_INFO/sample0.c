#include <stdio.h>
#include <stdlib.h>

double sum(FILE *fin, double a0);

int main(void)
{
    double result, a;
    
    FILE *fin, *fout;
    
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt","w");
    
    if (fscanf(fin, "%lf", &a) != EOF)
    {
        result = sum(fin, a);
        fprintf(fout,"%lf\n", result);
    }
    
    fclose(fin);
    fclose(fout);
    
    return 0;
}

double sum(FILE *fin, double a0)
{
    double a, s = a0;
    
    while (fscanf(fin, "%lf", &a) != EOF)
        s += a;
    
    return s;
}

