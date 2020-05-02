#include <iostream>
#include <stdio.h>
#include <math.h>

class CommonSolver
{
public:
    CommonSolver(){}
    virtual void getSolution(){}
    virtual void fillSizes(int k){}
    virtual double divFunc(){return 1;}
    virtual void calculateNext(int i){}
    
    void printErrors()
    {
        double *temp;
        
        for (int k = 20; k <= 1000; k += 20)
        {
            T = 1.0;
            fillSizes(k);
            tau = T/n;
            h = 1.0/(m-1);
            
            data = fopen("data.txt", "w");
            
            u_cur = new double[m+1];
            u_next = new double[m+1];
            
            for(int j = 0; j <= m; ++j)
            {
                u_cur[j] = answerFunction(0, j*h-h/2);
                fprintf(data, "%.16lf ", u_cur[j]);
            }
            fprintf(data, "\n");
            
            for (int i = 0; i < n; ++i)
            {
                calculateNext(i);
                
                temp = u_next;
                u_next = u_cur;
                u_cur = temp;
//                swap(u_next, u_cur);
                
                for (int j = 0; j <= m; ++j)
                    fprintf(data, "%.16lf ", u_cur[j]);
                
                fprintf(data, "\n");
            }
            fclose(data);
            
            data = fopen("data.txt", "r");
            printf("size: %d, max error: %lf\n", m, residual()/divFunc());
            
            delete []u_cur;
            delete []u_next;
            fclose(data);
        }
    }
    
    double residual()
    {
        double maxDif = 0;
        
        for (int i = 0; i <= n; ++i)
        {
            for (int j = 0; j <= m; ++j)
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
    double *u_cur, *u_next;
};

class ExplicitSolver: public CommonSolver
{
public:
    ExplicitSolver(){}
    
    virtual void fillSizes(int k)
    {
        m = k;
        n = T * (2*k-1)*(2*k-1)/2;
    }
    
    virtual double divFunc()
    {
        return tau + h*h;
    }
    
    void calculateNext(int i)
    {
        for(int j = 1; j < m; ++j)
            u_next[j] =  (u_cur[j+1] - 2 * u_cur[j] + u_cur[j-1]) * tau/(h*h) + u_cur[j]
                        - tau * factorFunction(h*j - h/2) * u_cur[j] + tau * function(tau*i, h*j - h/2);

        u_next[0] = -u_next[1];
        u_next[m] = u_next[m-1];
    }
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
    
    virtual double divFunc()
    {
        return tau*tau + h*h;
    }
    
    void calculateNext(int i)
    {
        double *a, *b, *c, *f;
        
        a = new double[m+1];
        b = new double[m+1];
        c = new double[m+1];
        f = new double[m+1];
        
        fillMatrix(a, b, c);
        fillF(f, i);
        
        solveMatrix(u_next, a, b, c, f);
        
        delete []a;
        delete []b;
        delete []c;
        delete []f;
    }
        
    void fillMatrix(double *a, double *b, double *c)
    {
        c[0] = 1.0;
        b[0] = -1.0;
        
        for (int j = 1; j < m; ++j)
        {
            a[j] = 1.0/(2*h*h);
            c[j] = 2.0/(h*h) + 1.0/tau + factorFunction(h*j-h/2)/2;
            b[j] = 1.0/(2*h*h);
        }
        
        a[m] = 1.0;
        c[m] = 1.0;
    }
    
    void fillF(double *f, int i)
    {
        for (int j = 1; j <= m; ++j)
            f[j] = (u_cur[j+1] - 2*u_cur[j] + u_cur[j-1])/(2*h*h) + u_cur[j]/tau
                    - factorFunction(h*j-h/2)/2 * u_cur[j] + (function(tau*(i+1), h*j-h/2) + function(tau*i, h*j-h/2))/2;
        
        f[0] = 0;
        f[m] = 0;
    }
    
    void solveMatrix(double *y, double *a, double *b, double *c, double *f)
    {
        double *alpha;
        double *beta;
        
        alpha = new double[m+1];
        beta = new double[m+1];
        
        alpha[1] = b[0]/c[0];
        beta[1] = f[0]/c[0];
        
        for (int i = 1; i < m; ++i)
        {
            alpha[i+1] = b[i] / (c[i] - a[i]*alpha[i]);
            beta[i+1] = (f[i] + a[i]*beta[i]) / (c[i] - a[i]*alpha[i]);
        }
        
        y[m] = (f[m] + a[m]*beta[m]) / (c[m] - a[m]*alpha[m]);
        
        for (int i = m-1; i >= 0; --i)
            y[i] = alpha[i+1]*y[i+1] + beta[i+1];
        
        delete []alpha;
        delete []beta;
    }
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
