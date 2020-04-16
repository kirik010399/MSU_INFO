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

    double f(double x)
    {
   
    }

    double exactSolution(double x) // True solution of a given differential equation
    {

    }
    
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

class FourierAlgorithm: public CommonSolver
{
public:
    FourierAlgorithm(){}
    
    double f(double x)
    {
        
    }

    double exactSolution(double x) // True solution of a given differential equation
    {
        
    }
    
    double eigenFunctionComponent(int m, int k)
    {
        return sin(M_PI*h*(2*m-1)*(2*k-1)/4);
    }

    void fillEigenFunction(double *e, int m)
    {
        e[0] = 0;
        e[n] = 0;
        
        for (int k = 1; k <= n-1; ++k)
            e[i] = eigenFunctionComponent(m, k);
    }
    
    void product(double *y1, double *y2)
    {
        double sum = 0;
        
        for (int k = 1; k <= n-1; ++k)
            sum += y1[k] * y2[k] * h;
    }
    
    double eigenValue(int m, double b)
    {
        return 4/(h*h) * sin(M_PI*h*(2*m-1)/4)*sin(M_PI*h*(2*m-1)/4) + b;
    }
    
    void solve()
    {
        double *c;
        c = new double[n+1];
        
        f2c(c);
        c2y(c);
        delete []c;
    }
    
    void f2c(double *f)
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

    void c2y(double* y)
    {
        for (int k = 1; k <= n-1; ++k)
        {
            y[k] = 0;
            for (int m = 1; m <= n-1; ++m)
                y[k] += c[m] * eigenFunctionComponent(m, k);
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
