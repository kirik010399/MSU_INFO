#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vector <double> f2c(vector <double> y, int n)
{
    double h = 1.0/n;
    vector <double> c;
    
    c.push_back(0);
    
    for (int k = 1; k <= n-1; ++k)
    {
        double sum = 0;
        
        for (int i = 1; i <= n-1; ++i)
            sum += y[i] * sin(M_PI*k*i*h) * h;
        
        double sum1 = 0;
        
        for (int i = 1; i <= n-1; ++i)
            sum1 += sin(M_PI*k*i*h) * sin(M_PI*k*i*h) * h;
        
        c.push_back(sum/sum1);
    }
    
    c.push_back(0);
    
    return c;
}

vector <double> c2f(vector <double> c, int n)
{
    double h = 1.0/n;
    vector <double> y;
    
    y.push_back(0);
    
    for (int i = 1; i <= n-1; ++i)
    {
        double sum = 0;
        
        for (int m = 0; m <= n-1; ++m)
        {
            sum += c[m] * sin(M_PI*m*i*h);
        }
        
        y.push_back(sum);
    }
    
    y.push_back(0);
    
    return y;
}

int main()
{
    FILE *fin, *fin1, *fout;
    int n;
    double a;
    vector <double> c, y, y1;
    
    fin = fopen("input.txt", "r");
    fin1 = fopen("input1.txt", "r");
    fout = fopen("output.txt", "w");
    
    fscanf(fin, "%d", &n);
    
    for (int i = 0; i < n + 1; ++i)
    {
        fscanf(fin1, "%lf", &a);
        y.push_back(a);
    }
    
    c = f2c(y, n);
    
    for (int i = 0; i < n + 1; ++i)
    {
        fprintf(fout, "%f ", c[i]);
    }
    
    fprintf(fout, "\n");
    
    y1 = c2f(c, n);
    
    for (int i = 0; i < n + 1; ++i)
    {
        fprintf(fout, "%f ", y1[i]);
    }
    
    fclose(fin);
    fclose(fout);
}


