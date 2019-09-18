#include <stdio.h>

void badAddOneToNumber(double a);
void goodAddOneToNumber(double *a);

int main(void)
{
    FILE *fin, *fout;
    double a;
    
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt","w");
    
    fscanf(fin, "%lf", &a);
    
    printf("Current number: %lf\n", a);

    badAddOneToNumber(a);
    printf("Current numbers after bad adding one: %lf\n", a);
    
    goodAddOneToNumber(&a);
    printf("Current number after good adding one: %lf\n", a);
    
    fclose(fin);
    fclose(fout);
    
    return 0;
}

void badAddOneToNumber(double a)
{
    a = a + 1;
}

void goodAddOneToNumber(double *a)
{
    *a = *a + 1;
}

