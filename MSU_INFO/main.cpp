#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void f2cFinal(vector <vector <double> > &c, vector <vector <double> > &y, int n)
{
    double h = 1.0/n;
    double h1 = 1.0/(n-1);
    int n1 = n + 1;
        
    for (int i = 0; i < n1; ++i)
    {
        c[i][0] = 0;
        c[0][i] = 0;
        c[i][n1-1] = 0;
        c[n1-1][i] = 0;
    }
    
    for (int i = 1; i <= n-1; ++i)
    {
        for (int j = 1; j <= n-1; ++j)
        {
            double sum = 0;
            
            for (int k = 1; k <= n-1; ++k)
            {
                for (int p = 1; p <= n-1; ++p)
                {
                    sum += y[k][p] * sin(M_PI*i*k*h) * h * sin(M_PI*(p*h1-h1/2)*(2*j-1)*0.5) * h1;
                }
            }
            
            double sum1 = 0;
            
            for (int k = 1; k <= n-1; ++k)
            {
                for (int p = 1; p <= n-1; ++p)
                {
                    sum1 += sin(M_PI*i*k*h) * sin(M_PI*i*k*h) * h * sin(M_PI*(p*h1-h1/2)*(2*j-1)*0.5) * sin(M_PI*(p*h1-h1/2)*(2*j-1)*0.5) * h1;
                }
            }
            
            c[i][j] = sum/sum1;
        }
    }
}

void c2fFinal(vector <vector <double> > &c, vector <vector <double> > &y, int n)
{
    double h = 1.0/n;
    double h1 = 1.0/(n-1);
    int n1 = n + 1;

    for (int i = 0; i < n1; ++i)
    {
        for (int j = 0; j < n1; ++j)
        {
            double sum = 0;
            
            for (int k = 0; k < n1; ++k)
            {
                for (int p = 1; p < n1; ++p)
                {
                    sum += c[k][p] * sin(M_PI*i*k*h) * sin(M_PI*(p*h1-h1/2)*(2*j-1)*0.5);
                }
            }
            
            y[i][j] = sum;
        }
    }
}

int main()
{
    FILE *fin, *fin1, *fout;
    int n;
    
    fin = fopen("input.txt", "r");
    fin1 = fopen("input1.txt", "r");
    fout = fopen("output.txt", "w");
    
    fscanf(fin, "%d", &n);
    
    vector <vector <double> > c;
    vector <vector <double> > y;
    vector <vector <double> > y1;
    
    for (int i = 0; i < n + 1; ++i)
    {
        vector<double> tempC;
        vector<double> tempY;
        vector<double> tempY1;

        for (int j = 0; j < n + 1; ++j)
        {
            double a;
            fscanf(fin1, "%lf", &a);
            tempY.push_back(a);
            tempC.push_back(0);
            tempY1.push_back(0);
        }
        
        y.push_back(tempY);
        c.push_back(tempC);
        y1.push_back(tempY1);
    }
    
    f2cFinal(c, y, n);
    
    for (int i = 0; i < n + 1; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
        {
            fprintf(fout, "%f ", c[i][j]);
        }
        fprintf(fout, "\n");
    }
    
    fprintf(fout, "\n");
    
    c2fFinal(c, y1, n);
    
    for (int i = 0; i < n + 1; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
        {
            fprintf(fout, "%f ", y1[i][j]);
        }
        fprintf(fout, "\n");
    }
       
    fprintf(fout, "\n");
    
    fclose(fin);
    fclose(fout);
}


