#include <iostream>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <algorithm>

double func(double x)
{
    return x * x * x * exp(x);
}

double integrateFunc(double x)
{
    return sin(x) - x*cos(x);
}

double integrateNewton(double a, double b, int n)
{
    double sum = 0;
    double dx = (b-a)/n;
    
    for (int i = 0; i < n; ++i)
    {
        double a0 = a+dx*i;
        double b0 = a+dx*(i+1);
        
        double dx0 = (b0 - a0)/3;
        
        double tempX0 = a0;
        double tempX1 = a0 + dx0;
        double tempX2 = a0 + 2*dx0;
        double tempX3 = a0 + 3*dx0;
        
        double c0 = (b0-a0)/8;
        double c1 = 3*(b0-a0)/8;
        double c2 = 3*(b0-a0)/8;
        double c3 = (b0-a0)/8;
                
        sum += c0 * func(tempX0) + c1 * func(tempX1) + c2 * func(tempX2) + c3 * func(tempX3);
    }
    
    return sum;
}

double integrateGauss(double a, double b, int n)
{
    double sum = 0;
    double dx = (b-a)/n;
    
    double x0 = -sqrt(3.0/7+2*sqrt(6.0/5)/7);
    double x1 = -sqrt(3.0/7-2*sqrt(6.0/5)/7);
    double x2 = -x1;
    double x3 = -x0;
        
    for (int i = 0; i < n; ++i)
    {
        double a0 = a+dx*i;
        double b0 = a+dx*(i+1);
        
        double tempX0 = (b0 - a0) * x0/2 + (b0 + a0)/2;
        double tempX1 = (b0 - a0) * x1/2 + (b0 + a0)/2;
        double tempX2 = (b0 - a0) * x2/2 + (b0 + a0)/2;
        double tempX3 = (b0 - a0) * x3/2 + (b0 + a0)/2;
        
        double c1 = (b0 - a0) * ((b0*b0 + a0*b0 + a0*a0)/3 - (tempX0*tempX0 + tempX3*tempX3)/2) / (tempX1*tempX1 + tempX2*tempX2 - tempX0*tempX0 - tempX3*tempX3);
        double c0 = (b0 - a0)/2 - c1;
        double c2 = c1;
        double c3 = c0;
        
        sum += c0*func(tempX0) + c1*func(tempX1) + c2*func(tempX2) + c3*func(tempX3);
    }
    
    return sum;
}

int main()
{
    double a, b;
    int n;
    FILE *fin, *foutNewton, *foutGauss;
    
    fin = fopen("input.txt", "r");
    foutNewton = fopen("outputNewton.txt", "w");
    foutGauss = fopen("outputGauss.txt", "w");

    fscanf(fin, "%lf %lf %n", &a, &b, &n);
    
    printf("Newton method: %.16lf\n", integrateNewton(a, b, n));
    printf("Gauss method: %.16lf\n", integrateGauss(a, b, n));
    
    double realResult = 6 + 12 * M_E * M_E * M_E;
    printf("Real integral: %.16lf\n", realResult);
    
    for (int i = 1; i <= 100; ++i)
    {
        fprintf(foutNewton, "%.16lf, ", fabs(realResult - integrateNewton(a, b, i))/fabs(realResult));
        fprintf(foutGauss, "%.16lf, ", fabs(realResult - integrateGauss(a, b, i))/fabs(realResult));
    }
    
    fclose(fin);
    fclose(foutNewton);
    fclose(foutGauss);

    return 0;
}
