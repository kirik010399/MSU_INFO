#include <iostream>
#include <stdio.h>
#include <math.h>

class CommonSolver
{
public:
    CommonSolver(){}
    virtual double function(double x){return 0;}
    virtual double solution(double x){return 0;}
    virtual double getErrorToN(){return 0;}
    
    void printErrors()
    {
        for (n = 10; n <= 10000; n*=10)
        {
            h = 1.0/(n-1);
            printf("n: %d, norm: %lf\n", n, getErrorToN());
        }
    }
    
    double residual(double *y1, double *y2)
    {
        double res = 0;
        
        for (int i = 0; i < n+1; ++i)
        {
            double dif = y1[i] - y2[i];
            res += dif*dif * h;
        }
        return sqrt(res)/(h*h);
    }
    
    void generateFunction(double *f)
    {
        f[0] = -function(h/2);
        int k = 1;
        for (double i = h/2; i <= 1-h/2 + 1e-10; i += h)
        {
            f[k] = function(i);
            ++k;
        }
        if (k != n)
           printf("error\n");
        
        f[n] = function(1-h/2);
    }
    
    void generateSolution(double *y)
    {
        y[0] = -solution(h/2);
        int k = 1;
        for (double i = h/2; i <= 1-h/2 + 1e-10; i += h)
        {
            y[k] = solution(i);
            ++k;
        }
        if (k != n)
           printf("error\n");
        
        y[n] = solution(1-h/2);
    }
    
protected:
    int n;
    double h;
};

class FourierSolver: public CommonSolver
{
public:
    FourierSolver(){}
    
    virtual double getErrorToN()
    {
        double *c, *f, *y, *sol;
        c = new double[n+1];
        f = new double[n+1];
        y = new double[n+1];
        sol = new double[n+1];

        generateFunction(f);
        setFactor();
        
        f2c(f, c);
        c2y(c, y);

        generateSolution(sol);
        
        double res = residual(y, sol);
        
        delete []c;
        delete []f;
        delete []y;
        delete []sol;
        
        return res;
    }
    
    virtual double function(double x)
    {
        return sin(M_PI*x/2);
    }
    
    virtual double solution(double x)
    {
        return 4 * sin(M_PI*x/2)/(12+M_PI*M_PI);
    }
    
    void setFactor()
    {
        b = 3;
    }
    
    double eigenFunctionComponent(int m, int k)
    {
        return sin(M_PI*h*(2*m-1)*(2*k-1)/4);
    }
    
    double eigenValue(int m)
    {
        return 4/(h*h) * sin(M_PI*h*(2*m-1)/4)*sin(M_PI*h*(2*m-1)/4) + b;
    }
    
    double product(double *y1, double *y2)
    {
        double sum = 0;
        
        for (int k = 1; k <= n-1; ++k)
            sum += y1[k] * y2[k] * h;
        
        return sum;
    }
    
    void f2c(double *f, double *c)
    {
        double *e;
        e = new double[n+1];
        
        c[0] = 0;
        c[n] = 0;
        
        for (int m = 1; m <= n-1; ++m)
        {
            fillEigenFunction(e, m);
            c[m] = product(f, e) / (eigenValue(m) * product(e, e));
        }
        
        delete []e;
    }

    void c2y(double* c, double *y)
    {
        for (int k = 0; k < n+1; ++k)
        {
            y[k] = 0;
            for (int m = 0; m < n+1; ++m)
                y[k] += c[m] * eigenFunctionComponent(m, k);
        }
    }

    void fillEigenFunction(double *e, int m)
    {
        e[0] = 0;
        e[n] = 0;
        
        for (int k = 1; k <= n-1; ++k)
            e[k] = eigenFunctionComponent(m, k);
    }
    
private:
    double b;
};

class ThomasSolver: public CommonSolver
{
public:
    ThomasSolver(){}
    
    virtual double getErrorToN()
    {
        double *a, *b, *c, *f, *y, *sol;
        a = new double[n+1];
        b = new double[n+1];
        c = new double[n+1];
        f = new double[n+1];
        y = new double[n+1];
        sol = new double[n+1];

        generateFunction(f);
        setFactor();
        fillMatrix(a, b, c);

        generateSolution(sol);
        
        double res = residual(y, sol);
        
        delete []a;
        delete []b;
        delete []c;
        delete []f;
        delete []y;
        delete []sol;
        
        return res;
    }
    
    virtual double function(double x)
    {
        return sin(M_PI*x/2);
    }
    
    virtual double solution(double x)
    {
        return 4 * sin(M_PI*x/2)/(12+M_PI*M_PI);
    }
    
    void setFactor()
    {
        b[0] = -h/2;
        int k = 1;
        for (double i = h/2; i <= 1-h/2 + 1e-10; i += h)
        {
            b[k] = i;
            ++k;
        }
        if (k != n)
           printf("error\n");
        
        b[n] = 1+h/2;
    }
    
    void fillMatrix()
    {
        
    }
    
private:
    double *b;
};

int main()
{
    FourierSolver fourierSolver;
    fourierSolver.printErrors();
    
    ThomasSolver thomasSolver;
    thomasSolver.printErrors();
    
    return 0;
}
