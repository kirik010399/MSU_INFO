#include <iostream>
#include <math.h>


class CommonSolver
{
public:
    CommonSolver(){}
    
    double func(double x)
    {
    //    return sin(M_PI*(1+0.5)*x);
        return sin(M_PI*(1+0.5)*x) * (x + 9*M_PI*M_PI/4);
    }

    double func_orig(double x) // True solution of a given differential equation
    {
    //    return sin(M_PI*(1+0.5)*x) / (M_PI*(1+0.5) * M_PI*(1+0.5) + 5);
        return sin(M_PI*(1+0.5)*x);
    }

    double res_norm(double* y, double h, int N)
    {
        int i;
        double norm;
        
        norm = 0;
        for (i = 0; i < N+1; i++)
            norm += h*(y[i] - func_orig(i*h - h/2))*(y[i] - func_orig(i*h - h/2));
        
        return sqrt(norm) / (h*h);
    }
    
    void printErros()
    {
        for (N = 10; N < 10001; N *= 10)
            {
                C = new double[N+1];
                f = new double[N+1];
                y = new double[N+1];
                eig_func = new double[N+1];
                
                a = new double[N+1];
                b = new double[N+1];
                c = new double[N+1];
                coef = new double[N+1];
                
                h = 2./(2*N-1);
                
                for (i = 0; i < N+1; i++)
                    coef[i] = i*h - h/2; // Progonka
        //            coef[i] = 5; // Fourier
                
                a[0] = 0; // not using
                b[N] = 0; // not using

                for (i = 1; i < N; i++)
                {
                    a[i] = 1 / (h*h);
                    c[i] = 2 / (h*h) + coef[i];
                    b[i] = 1 / (h*h);
                }
                c[0] = 1;
                b[0] = -1;
                a[N] = 2/(h*h);
                c[N] = coef[N] + 2/(h*h);
                
                for (i = 0; i < N+1; i++)
                    f[i] = func(i*h-h/2);
                f[0] = 0;
                
        //        f2c(C, f, eig_func, coef[0], h, N);
        //        c2y(C, y, h, N);
                
                solver_progonka(y, a, b, c, f, N);
                
                error = res_norm(y, h, N);
                printf("%d %.16lf\n", N, error);
                
                delete []C;
                delete []f;
                delete []y;
                delete []eig_func;
            }
    }
};


class ThomasAlgorithm: public CommonSolver
{
public:
    ThomasAlgorithm(){}

    void solver_progonka(double* y, double* a, double* b, double* c, double* f, int N)
    {
        int i;
        double* alpha;
        double* beta;
        
        alpha = new double[N+1];
        beta = new double[N+1];
        
        alpha[1] = b[0]/c[0];
        beta[1] = f[0]/c[0];
        
        for (i = 1; i < N; i++)
        {
            alpha[i+1] = b[i] / (c[i] - a[i]*alpha[i]);
            beta[i+1] = (f[i] + a[i]*beta[i]) / (c[i] - a[i]*alpha[i]);
        }
        
        y[N] = (f[N] + a[N]*beta[N]) / (c[N] - a[N]*alpha[N]);
        
        for (i = N-1; i >= 0; i--)
            y[i] = alpha[i+1]*y[i+1] + beta[i+1];
        
        delete []alpha;
        delete []beta;
    }
};

class FourierAlgorithm
{
public:
    FourierAlgorithm(){}
    
    double eigen_value(int m, double coef, double h, int N)
    {
        return 4/(h*h) * sin(M_PI*(m+0.5)*h/2) * sin(M_PI*(m+0.5)*h/2) + coef;
    }

    void eigen_func(double* g, int m, double h, int N)
    {
        for (int i = 0; i < N+1; i++)
            g[i] = sin(M_PI*(m+0.5)*(i*h-h/2));
    }

    double dot_product(double* f, double* g, double h, int N)
    {
        double product = 0;
        
        for (int i = 1; i < N; i++) // Скалярное
            product += f[i] * g[i] * h;
        product += f[N] * g[N] * h/2;
        
        return product;
    }

    void f2c(double *C, double *f, double* eig_func, double b, double h, const int N)
    {
        for (int m = 0; m < N; m++)
        {
            eigen_func(eig_func, m, h, N);
            C[m] = dot_product(f, eig_func, h, N) / (dot_product(eig_func, eig_func, h, N) * eigen_value(m, b, h, N));
        }
        return;
    }

    void c2y(double* C, double* y, double h, int N)
    {
        int i, m;
        
        for (i = 0; i < N+1; i++)
        {
            y[i] = 0;
            for (m = 0; m < N; m++)
                y[i] += C[m] * sin(M_PI*(m+0.5)*(i*h-h/2));
        }
    }
};



int main()
{
    int i, N;
    double h, error;
    double* C;
    double* f;
    double* y;
    double* eig_func;
    
    double* a;
    double* b;
    double* c;
    double* coef;
        
    
    
    return 0;
}
