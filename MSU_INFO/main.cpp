#include <stdio.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

double f (double x, double y)
{
    return y*(y-1)*(2*x*x*x - 3*x*x);
}

void f2cFinal(vector <vector <double> > &c, vector <vector <double> > &y, vector <vector <double> > &d, int n)
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
            double sum1 = 0;

            for (int k = 1; k <= n-1; ++k)
            {
                sum += y[k][j] * sin(M_PI*i*k*h) * h;
                sum1 += sin(M_PI*i*k*h) * sin(M_PI*i*k*h) * h;
            }
            
            d[i][j] = sum/sum1;
        }
    }
    
    for (int i = 1; i <= n-1; ++i)
    {
        for (int j = 1; j <= n-1; ++j)
        {
            double sum = 0;
            double sum1 = 0;

            for (int p = 1; p <= n-1; ++p)
            {
                sum += d[i][p] * sin(M_PI*(p*h1-h1/2)*(2*j-1)*0.5) * h1;
                sum1 += sin(M_PI*(p*h1-h1/2)*(2*j-1)*0.5) * sin(M_PI*(p*h1-h1/2)*(2*j-1)*0.5) * h1;
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
                for (int p = 0; p < n1; ++p)
                {
                    sum += c[k][p] * sin(M_PI*i*k*h) * sin(M_PI*(p*h1-h1/2)*(2*j-1)*0.5);
                }
            }
            
            y[i][j] = sum;
        }
    }
}

void residual(vector <vector <double> > c, int n)
{
    FILE *fout;
    fout = fopen("output1.txt", "w");
    double a = 0, b = 1;
    
    double dt = fabs(b-a)/(n);
    double newDt = 1.0/(n-1);
    int n1 = n + 1;
    
    double maxRes = 0;
    
    for (double i = a; i <= b + 1e-10; i+=dt/2)
    {
       for (double j = newDt/2; j <= 1-newDt/2 + 1e-10; j+=newDt/2)
        {
            double tempValue = 0;
                    
            for (int k = 0; k < n1; ++k)
            {
                for (int p = 0; p < n1; ++p)
                {
                    tempValue += c[k][p] * sin(M_PI*i*k) * sin(M_PI*(j)*(2*p-1)*0.5);
                }
            }
            
            double tempRes = fabs(f(j, i) - tempValue);
            
            fprintf(fout, "%f ", tempRes);
//            printf("%.16lf %.16lf %.16lf\n", i, j, tempRes);
            
            if(tempRes > maxRes)
                maxRes = tempRes;
        }
        fprintf(fout, "\n");
    }
    
    printf("%.16lf\n", maxRes);
}

void generatePointsFinal(FILE *fout, int n)
{
    double a = 0, b = 1;
    
    double dt = fabs(b-a)/(n);
    double newDt = 1.0/(n-1);
        
    int k1 = 0, k2 = 0;
    
    for (double j = a; j <= b + 1e-10; j+=dt)
    {
        k1 = 0;
        fprintf(fout, "%.16f ", -f(newDt/2, j));
        
        for (double i = newDt/2; i <= 1-newDt/2 + 1e-10; i += newDt)
        {
            fprintf(fout, "%.16f ", f(i, j));
            k1++;
        }
        
        fprintf(fout, "%.16f\n", f(1-newDt/2, j));
        if (k1 != n-1)
            printf("1");
        k2++;
    }
    if (k2 != n+1)
        printf("2");
}

int main()
{
    FILE *fin, *fin1, *fout;
//    int n;
    
    for (int n = 5; n <= 5; n += 1)
    {
        fin = fopen("input.txt", "r");
        fin1 = fopen("input1.txt", "w");
        fout = fopen("output.txt", "w");
        
    //    fscanf(fin, "%d", &n);
        
        generatePointsFinal(fin1, n);
        
        fclose(fin1);
        fin1 = fopen("input1.txt", "r");
        
        vector <vector <double> > c;
        vector <vector <double> > y;
        vector <vector <double> > y1;
        vector <vector <double> > d;
        
        for (int i = 0; i < n + 1; ++i)
        {
            vector<double> tempC;
            vector<double> tempY;
            vector<double> tempY1;
            vector<double> tempD;

            for (int j = 0; j < n + 1; ++j)
            {
                double a;
                fscanf(fin1, "%lf", &a);
                tempY.push_back(a);
                tempC.push_back(0);
                tempY1.push_back(0);
                tempD.push_back(0);
            }
            
            y.push_back(tempY);
            c.push_back(tempC);
            y1.push_back(tempY1);
            d.push_back(tempD);
        }
        
        f2cFinal(c, y, d, n);
        
        for (int i = 0; i < n + 1; ++i)
        {
            for (int j = 0; j < n + 1; ++j)
            {
                fprintf(fout, "%.16f ", c[i][j]);
            }
            fprintf(fout, "\n");
        }
        
        fprintf(fout, "\n");
        
        c2fFinal(c, y1, n);
        
        residual(c, n);
        
        for (int i = 0; i < n + 1; ++i)
        {
            for (int j = 0; j < n + 1; ++j)
            {
                fprintf(fout, "%.16f ", y1[i][j]);
            }
            fprintf(fout, "\n");
        }
           
        fprintf(fout, "\n");
        
        for (int i = 0; i < n + 1; ++i)
        {
            for (int j = 0; j < n + 1; ++j)
            {
                fprintf(fout, "%.16f ", y[i][j]);
            }
            fprintf(fout, "\n");
        }
          
        fprintf(fout, "\n");

        fclose(fin);
        fclose(fout);
    }
}


