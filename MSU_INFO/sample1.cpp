#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double f (double x, double y)
{
//    return sin(M_PI*x) * sin(M_PI*(p*h1-h1/2)*(2*j-1)*0.5);
}

void generatePointsFinal(FILE *fout, int n)
{
    double a = 0, b = 1;
    
    double dt = fabs(b-a)/(n);
    double newDt = (1.0 + dt)/n;
    
    for (double j = a; j <= b; j+=dt)
    {
        fprintf(fout, "%f ", -f(-dt/2 + newDt, j));
        
        for (double i = -dt/2 + newDt; i <= 1+dt/2-newDt; i+=newDt)
        {
            fprintf(fout, "%f ", f(i, j));
        }
        
        fprintf(fout, "%f\n", f(1+dt/2-newDt, j));
    }
}

int main(void)
{
    FILE *fin, *fout;
    int n;
    
    fin = fopen("input.txt", "r");
    fout = fopen("input1.txt", "w");
    
    fscanf(fin, "%d", &n);
    
    generatePointsFinal(fout, n);
    
    fclose(fin);
    fclose(fout);
}


