#include <stdio.h>

int main(void)
{
    FILE *fin, *fout;
    double a, b;
    int val;
    
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt","w");

    val = fscanf(fin, "%lf", &a);
    
    if (val == -1)
    {
        printf("Empty file\n");
        return -1;
    }
    else if (val == 0)
    {
        printf("Incorrect first number\n");
        return -2;
    }
    else if (val == 1)
    {
        printf("First number is correct\n");
    }
    
    val = fscanf(fin, "%lf", &b);

    if (val == -1)
    {
        printf("There is no second number\n");
        return -1;
    }
    else if (val == 0)
    {
        printf("Incorrect second number\n");
        return -2;
    }
    else if (val == 1)
    {
        printf("Second number is correct\n");
    }
    
    fprintf(fout, "Sum of numbers is: %f\n", a+b);
    
    fclose(fin);
    fclose(fout);
    
    return 0;
}
