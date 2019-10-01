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

vector <double> f2cWithShift(vector <double> y, int n)
{
    double h = 1.0/(n-1);
    
    vector <double> c;
    
    c.push_back(0);
    
//    double tempSum = 0;
//
//    for (int i = 1; i <= n-1; ++i)
//        tempSum += sin(M_PI*(i*h-h/2)*(2*1-1)*0.5) * sin(M_PI*(i*h-h/2)*(2*2-1)*0.5);
//
//    printf("%lf\n", tempSum);
    
    for (int k = 1; k <= n-1; ++k)
    {
        double sum = 0;
        
        for (int i = 1; i <= n-1; ++i)
            sum += y[i] * sin(M_PI*(i*h-h/2)*(2*k-1)*0.5) * h;
        
        double sum1 = 0;
        
        for (int i = 1; i <= n-1; ++i)
            sum1 += sin(M_PI*(i*h-h/2)*(2*k-1)*0.5) * sin(M_PI*(i*h-h/2)*(2*k-1)*0.5) * h;
                
        c.push_back(sum/sum1);
    }
    
    c.push_back(0);
    
    return c;
}

vector <double> c2fWithShift(vector <double> c, int n)
{
    double h = 1.0/(n-1);
    vector <double> y;
        
    for (int i = 1; i <= n-1; ++i)
    {
        double sum = 0;
        
        for (int m = 0; m <= n-1; ++m)
        {
            sum += c[m] * sin(M_PI*(i*h-h/2)*(2*m-1)*0.5);
        }
        
        if (i == 1)
            y.push_back(-sum);
        
        y.push_back(sum);

        if (i == n-1)
            y.push_back(sum);
    }
        
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
    
    c = f2cWithShift(y, n);
    
    for (int i = 0; i < n + 1; ++i)
    {
        fprintf(fout, "%f ", c[i]);
    }
    
    fprintf(fout, "\n");
    
    y1 = c2fWithShift(c, n);
    
    for (int i = 0; i < n + 1; ++i)
    {
        fprintf(fout, "%f ", y1[i]);
    }
    
    fclose(fin);
    fclose(fout);
}


