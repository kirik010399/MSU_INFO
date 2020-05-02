#include <iostream>
#include <stdio.h>
#include <math.h>

class CommonSolver
{
public:
    CommonSolver(){}
    virtual void getSolution(){}
    virtual void fillSizes(int k){}
    
    void printErrors()
    {
        for (int k = 20; k <= 1000; k += 20)
        {
            T = 1.0;
            fillSizes(k);
            tau = T/n;
            h = 1.0/(m-1);
            
            data = fopen("data.txt", "w");
            getSolution();
            fclose(data);
            
            data = fopen("data.txt", "r");
            printf("n: %d, max error: %lf\n", n, residual());
            fclose(data);
        }
    }
    
    double residual()
    {
        double maxDif = 0;
        
        for (int i = 0; i < n+1; ++i)
        {
            for (int j = 0; j < m+1; ++j)
            {
                double temp;
                fscanf(data, "%lf", &temp);
                double dif = fabs(temp - answerFunction(i*tau, j*h-h/2));
                
                if (dif > maxDif)
                    maxDif = dif;
            }
        }
        return maxDif;
    }
    
    double answerFunction(double t, double x)
    {
        return 0;
    }
    
    double factorFunction(double x)
    {
        return x;
    }
    
    double function(double t, double x)
    {
        return 0;
    }
    
protected:
    int n; //for t
    int m; //for x
    double h;
    double tau, T;
    FILE *data;
};

class ExplicitSolver: public CommonSolver
{
public:
    ExplicitSolver(){}
    
    virtual void fillSizes(int k)
    {
        m = k;
        n = T*(2*k-1)*(2*k-1)/2;
    }
    
    virtual void getSolution()
    {
        
    }
    
    
private:
};

class KrankNikolsonSolver: public CommonSolver
{
public:
    KrankNikolsonSolver(){}
    
    virtual void fillSizes(int k)
    {
        m = k;
        n = k;
    }
    
    virtual void getSolution()
    {
        double *a, *b, *c, *f, *y, *sol;
        a = new double[n+1];
        b = new double[n+1];
        c = new double[n+1];
        f = new double[n+1];
        y = new double[n+1];
        sol = new double[n+1];
        factor = new double[n+1];

        f[0] = 0;
        f[n] = 0;
        
        fillMatrix(a, b, c);

        solveMatrix(y, a, b, c, f);

//        double res = residual(y, sol);
        
        delete []a;
        delete []b;
        delete []c;
        delete []f;
        delete []y;
        delete []sol;
        delete []factor;
    }
    
    void fillMatrix(double *a, double *b, double *c)
    {
        c[0] = 1.0;
        b[0] = -1.0;
        
        for (int i = 1; i < n; ++i)
        {
            a[i] = 1.0/(h*h);
            c[i] = 2.0/(h*h) + factor[i];
            b[i] = 1.0/(h*h);
        }
        
        a[n] = 1.0;
        c[n] = 1.0;
    }
    
    void solveMatrix(double *y, double* a, double* b, double* c, double *f)
    {
        int i;
        double* alpha;
        double* beta;
        
        alpha = new double[n+1];
        beta = new double[n+1];
        
        alpha[1] = b[0]/c[0];
        beta[1] = f[0]/c[0];
        
        for (i = 1; i < n; ++i)
        {
            alpha[i+1] = b[i] / (c[i] - a[i]*alpha[i]);
            beta[i+1] = (f[i] + a[i]*beta[i]) / (c[i] - a[i]*alpha[i]);
        }
        
        y[n] = (f[n] + a[n]*beta[n]) / (c[n] - a[n]*alpha[n]);
        
        for (i = n-1; i >= 0; --i)
            y[i] = alpha[i+1]*y[i+1] + beta[i+1];
        
        delete []alpha;
        delete []beta;
    }
    
private:
    double *factor;
};

int main()
{
    printf("Explicit alrgorithm errors:\n");
    ExplicitSolver explicitSolver;
    explicitSolver.printErrors();
    
    printf("Krank Nikolson alrgorithm errors:\n");
    KrankNikolsonSolver krankNikolsonSolver;
    krankNikolsonSolver.printErrors();
    return 0;
}
