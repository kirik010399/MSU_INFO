#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class StocksSolver
{
public:
    
    void fillInitialData()
    {
        nu = 1e-4;
        k = 1;
        r = 1;
        c = 1;
        G = 10;
    }
    
    double q(double x, double y)
    {
        return 3 * sin(2*M_PI*x) * sin(2*M_PI*y);
    }
    
    double omega0(double x, double y)
    {
        return 0;
    }
    
    double T0(double x, double y)
    {
        return 0;
    }
    
    double psi0(double x, double y)
    {
        return 0;
    }
    
    StocksSolver(int xCount, int yCount, int timeCount)
    {
        Mx = xCount;
        My = yCount;
        N = timeCount;
        
        hx = 1.0/Mx;
        hy = 1.0/My;
        tau = 1.0/N;

        fillInitialData();
        
        T = new double *[(Mx+1)];
        T_next = new double *[(Mx+1)];
        omega = new double *[(Mx+1)];
        omega_next = new double *[(Mx+1)];
        psi = new double *[(Mx+1)];
        f = new double *[(Mx+1)];
        C = new double *[(Mx+1)];
        d = new double *[(Mx+1)];

        for(int i = 0; i < Mx+1; ++i)
        {
            T[i] = new double[My+1];
            T_next[i] = new double[My+1];
            omega[i] = new double[My+1];
            omega_next[i] = new double[My+1];
            psi[i] = new double[My+1];
            f[i] = new double[My+1];
            C[i] = new double[My+1];
            d[i] = new double[My+1];
        }
    }
    
    virtual ~StocksSolver()
    {
        for(int i = 0; i < Mx+1; ++i)
        {
            delete [] T[i];
            delete [] T_next[i];
            delete [] omega[i];
            delete [] omega_next[i];
            delete [] psi[i];
            delete [] f[i];
            delete [] C[i];
            delete [] d[i];
        }

        delete []T;
        delete []T_next;
        delete []omega;
        delete []omega_next;
        delete []psi;
        delete []f;
        delete []C;
        delete []d;
    }
    
    void loop()
    {
        FILE* out_T;
        FILE* out_omega;
        FILE* out_psi;

        FILE* out_last_T;
        FILE* out_last_omega;
        FILE* out_last_psi;

        out_T = fopen("output_T.txt", "w");
        out_omega = fopen("output_omega.txt", "w");
        out_psi = fopen("output_psi.txt", "w");
        
        for (int i = 0; i < Mx+1; ++i)
        {
            for (int j = 0; j < My+1; ++j)
            {
                T[i][j] = T0(i*hx, j*hy);
                omega[i][j] = omega0(i*hx, j*hy);
                psi[i][j] = psi0(i*hx, j*hy);

                fprintf(out_T, "%.16lf ", T[i][j]);
                fprintf(out_omega, "%.16lf ", omega[i][j]);
                fprintf(out_psi, "%.16lf ", psi[i][j]);
            }
        }
        fprintf(out_T, "\n");
        fprintf(out_omega, "\n");
        fprintf(out_psi, "\n");

        for (int n = 0; n < N; ++n)
        {
            generateDataForT();
            calculateNextWithData(T_next, k);

            generateDataForOmega();
            calculateNextWithData(omega_next, nu);

            generateDataForPsi();
            calculateNextPsi();

            for (int i = 0; i < Mx+1; ++i)
            {
                for (int j = 0; j < My+1; ++j)
                {
                    fprintf(out_T, "%.16lf ", T_next[i][j]);
                    fprintf(out_omega, "%.16lf ", omega_next[i][j]);
                    fprintf(out_psi, "%.16lf ", psi[i][j]);
                }
            }
            fprintf(out_T, "\n");
            fprintf(out_omega, "\n");
            fprintf(out_psi, "\n");

            swap(T, T_next);
            swap(omega, omega_next);
        }

        fclose(out_T);
        fclose(out_omega);
        fclose(out_psi);

        out_last_T = fopen("output_last_T.txt", "w");
        out_last_omega = fopen("output_last_omega.txt", "w");
        out_last_psi = fopen("output_last_psi.txt", "w");

        for (int i = 0; i < Mx+1; ++i)
        {
            for (int j = 0; j < My+1; ++j)
            {
                fprintf(out_last_T, "%.16lf ", T[i][j]);
                fprintf(out_last_omega, "%.16lf ", omega[i][j]);
                fprintf(out_last_psi, "%.16lf", psi[i][j]);
            }
            fprintf(out_last_T, "\n");
            fprintf(out_last_omega, "\n");
            fprintf(out_last_psi, "\n");
        }

        fclose(out_last_T);
        fclose(out_last_omega);
        fclose(out_last_psi);
    }
    
    void generateDataForT()
    {
        for (int i = 0; i < Mx+1; ++i)
            for (int j = 0; j < My+1; ++j)
                f[i][j] = 0;

        for (int i = 1; i < Mx; ++i)
            for (int j = 1; j < My; ++j)
                f[i][j] = 1/tau * T[i][j] - (T[i+1][j]-T[i][j])/hx * (psi[i][j+1]-psi[i][j])/hy +
                                                     (T[i][j+1]-T[i][j])/hy * (psi[i+1][j]-psi[i][j])/hx +
                                                      q(i*hx, j*hy)/(r*c);
    }
    
    void generateDataForOmega()
    {
        for (int i = 0; i < Mx+1; ++i)
            for (int j = 0; j < My+1; ++j)
                f[i][j] = 0;

        for (int i = 1; i < Mx; ++i)
            for (int j = 1; j < My; ++j)
                f[i][j] = 1/tau * omega[i][j] - (omega[i+1][j]-omega[i][j])/hx * (psi[i][j+1]-psi[i][j])/hy +
                                                         (omega[i][j+1]-omega[i][j])/hy * (psi[i+1][j]-psi[i][j])/hx +
                                                          G * (T_next[i+1][j]-T_next[i-1][j])/(2*hx);
    }
    
    void generateDataForPsi()
    {
        for (int i = 0; i < Mx+1; ++i)
            for (int j = 0; j < My+1; ++j)
                f[i][j] = -1.0 * omega[i][j];
    }
    
    void calculateNextWithData(double **u_next, double a)
    {
        f2c();

        for (int i = 1; i < Mx; ++i)
            for (int j = 1; j < My; ++j)
                C[i][j] = C[i][j]/(a * (lambda(i, hx) + lambda(j, hy)) + 1/tau);

        for (int i = 0; i < Mx+1; ++i)
            for (int j = 0; j < My+1; ++j)
                u_next[i][j] = c2f(i*hx, j*hy);
    }
    
    void calculateNextPsi()
    {
        f2c();
        
        for (int i = 1; i < Mx; ++i)
            for (int j = 1; j < My; ++j)
                C[i][j] = C[i][j]/(lambda(i, hx) + lambda(j, hy));

        for (int i = 0; i < Mx+1; ++i)
            for (int j = 0; j < My+1; ++j)
                psi[i][j] = c2f(i*hx, j*hy);
    }

    double lambda(int m, double h)
    {
        return 4/(h*h) * sin(M_PI*m*h/2) * sin(M_PI*m*h/2);
    }

    void f2c()
    {
        double hx, hy, norm;

        hx = 1.0/Mx;
        hy = 1.0/My;

        for (int m = 0; m < Mx+1; ++m)
            for (int l = 0; l < My+1; ++l)
                C[m][l] = 0;
        
        for (int m = 1; m < Mx; ++m)
        {
            for (int l = 1; l < My; ++l)
            {
                d[m][l] = 0;
                norm = 0;

                for (int j = 1; j < My; ++j)
                {
                    d[m][l] += f[m][j] * sin(M_PI*l*j*hy) * hy;
                    norm += sin(M_PI*l*j*hy) * sin(M_PI*l*j*hy) * hy;
                }
                d[m][l] /= norm;
            }
        }

        for (int m = 1; m < Mx; ++m)
        {
            for (int l = 1; l < My; ++l)
            {
                C[m][l] = 0;
                norm = 0;

                for (int i = 1; i < Mx; ++i)
                {
                    C[m][l] += d[i][l] * sin(M_PI*m*i*hx) * hx;
                    norm += sin(M_PI*m*i*hx) * sin(M_PI*m*i*hx) * hx;
                }
                C[m][l] /= norm;
            }
        }
    }

    double c2f(double x, double y)
    {
        double func;
        func = 0;

        for (int m = 1; m < Mx; ++m)
            for (int l = 1; l < My; ++l)
                func += C[m][l] * sin(M_PI*m*x) * sin(M_PI*l*y);
        
        return func;
    }
    
private:
    int Mx, My, N;
    double hx, hy, tau, nu, k, r, c, G;
    
    double **T;
    double **T_next;
    double **omega;
    double **omega_next;
    double **psi;
    double **f;
    double **C;
    double **d;
};

int main()
{
//    int Mx, My, N;
//    printf("Введите Mx (количество узлов по x): ");
//    scanf("%d", &Mx);
//    printf("Введите My (количество узлов по y): ");
//    scanf("%d", &My);
//    printf("Введите N (количество узлов по t): ");
//    scanf("%d", &N);
    StocksSolver stocksSolver(10, 10, 10);
    stocksSolver.loop();
    return 0;
}

