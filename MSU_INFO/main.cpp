#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double f (double x);

void generatePoints(FILE *fin, double a, double b, int n)
{
    double dt = fabs(b-a)/(n-1);
    
    for (double i = a; i <= b; i+=dt)
    {
        fprintf(fin, "%f %f\n", i, f(i));
    }
}

void generateChPoints(FILE *fin, double a, double b, int n)
{
    for (double i = 1; i <= n; i+=1)
    {
        double x = (a+b)/2 + (b-a) * 0.5 * cos(M_PI*(2*i-1)/(2*n));
        fprintf(fin, "%f %f\n", x, f(x));
    }
}

double lagrange(vector <double> x,  vector <double> y, double x0, int n)
{
    double res = 0;
    
    for (int i = 0; i < n; ++i)
    {
        double temp = y[i];

        for (int j = 0; j < n; ++j)
        {
            if (i == j)
                continue;
            
            temp *= (x0 - x[j])/(x[i]-x[j]);
        }
        
        res += temp;
    }
    
    return res;
}

double f (double x)
{
    return 1.0/(25 * x * x + 1);
}

int main(void)
{
    FILE *fin1, *fin, *fout;
    int n;
    double a, b;
    double tempX, tempY;
    vector <double> x;
    vector <double> y;
    
    fin1 = fopen("input.txt", "r");
    fin = fopen("input1.txt", "w");
    fout = fopen("output.txt", "w");
    
    fscanf(fin1, "%d%lf%lf", &n, &a, &b);
    
//    generatePoints(fin, a, b, n);
    generateChPoints(fin, a, b, n);
    
    fclose(fin);
    fclose(fin1);
    
    fin = fopen("input1.txt", "r");
    
    for (int i = 0; i < n; ++i)
    {
        fscanf(fin, "%lf%lf", &tempX, &tempY);
        x.push_back(tempX);
        y.push_back(tempY);
    }
    
    double l ;
    for (int i = 0; i < n-1; ++i)
    {
        l = lagrange(x, y, x[i], n);
        fprintf(fout, "%f %f %f %f\n", x[i], f(x[i]), l, f(x[i]) - l);
        
        tempX = x[i] + (x[i + 1] - x[i])/2;
        l = lagrange(x, y, tempX, n);
        
        fprintf(fout, "%f %f %f %f\n", tempX, f(tempX), l, f(tempX) - l);
    }
    
    l = lagrange(x, y, x[n-1], n);

    fprintf(fout, "%f %f %f %f\n", x[n-1], f(x[n-1]), l, f(x[n-1]) - l);
    
    fclose(fin);
    fclose(fout); 
}


