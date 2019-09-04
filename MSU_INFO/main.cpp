#include <stdio.h>

double sum1(FILE *fin);
void sum2(FILE *fin, double *s);

int main(void)
{
        double result1;
    //    double result2;
    
    FILE *fin, *fout;
    
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt","w");
    
    result1 = sum1(fin);
    fprintf(fout,"%lf\n", result1);
    
    //    sum2(fin, &result2);
    //    fprintf(fout,"%lf\n", result2);
    
    fclose(fin);
    fclose(fout);
    
    return 0;
}

double sum1(FILE *fin)
{
    double a, s = 0;
    
    while (fscanf(fin, "%lf", &a) != EOF)
        s += a;
    
    return s;
}

void sum2(FILE *fin, double *s)
{
    double a;
    
    *s = 0;
    
    while (fscanf(fin, "%lf", &a) != EOF)
        *s += a;
}

