#include <stdio.h>
#include <stdlib.h>

double sum(FILE *fin);

int main(void)
{
    double result;

    FILE *fin, *fout;

    fin = fopen("input.txt", "r");
    fout = fopen("output.txt","w");

    result = sum(fin);
    fprintf(fout,"%lf\n", result);

    fclose(fin);
    fclose(fout);

    return 0;
}

double sum(FILE *fin)
{
    double a, s = 0;

    if (fscanf(fin, "%lf", &a) == EOF)
        exit(0);

    s = a;

    while (fscanf(fin, "%lf", &a) != EOF)
        s += a;

    return s;
}

