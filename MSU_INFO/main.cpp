#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

double q_func(double x, double y)
{
    return 3 * sin(2*M_PI*x) * sin(2*M_PI*y);
}

double lambda(int n, double h)
{
    return 4/(h*h) * sin(M_PI*n*h/2) * sin(M_PI*n*h/2);
}

void f2c(double **C, double **f, double **d, int Mx, int My)
{
    double hx, hy, norm;

    hx = 1.0/Mx;
    hy = 1.0/My;

    for (int m = 0; m < Mx+1; ++m)
        for (int k = 0; k < My+1; ++k)
            C[m][k] = 0;
    
    for (int m = 1; m < Mx; ++m)
    {
        for (int k = 1; k < My; ++k)
        {
            d[m][k] = 0;
            norm = 0;

            for (int j = 1; j < My; ++j)
            {
                d[m][k] += f[m][j] * sin(M_PI*k*j*hy) * hy;
                norm += sin(M_PI*k*j*hy) * sin(M_PI*k*j*hy) * hy;
            }
            d[m][k] /= norm;
        }
    }

    for (int m = 1; m < Mx; ++m)
    {
        for (int k = 1; k < My; ++k)
        {
            C[m][k] = 0;
            norm = 0;

            for (int i = 1; i < Mx; ++i)
            {
                C[m][k] += d[i][k] * sin(M_PI*m*i*hx) * hx;
                norm += sin(M_PI*m*i*hx) * sin(M_PI*m*i*hx) * hx;
            }
            C[m][k] /= norm;
        }
    }
}

double c2f(double **C, double x0, double y0, int Mx, int My)
{
    double func;
    func = 0;

    for (int m = 1; m < Mx; ++m)
        for (int k = 1; k < My; ++k)
            func += C[m][k] * sin(M_PI*m*x0) * sin(M_PI*k*y0);
    
    return func;
}

void step_psi(double **right_part, double **psi, double **C, double **d, double hx, double hy, int Mx, int My)
{
    f2c(C, right_part, d, Mx, My);

    for (int i = 1; i < Mx; ++i)
        for (int j = 1; j < My; ++j)
            C[i][j] = C[i][j]/(lambda(i, hx) + lambda(j, hy));

    for (int i = 0; i < Mx+1; ++i)
        for (int j = 0; j < My+1; ++j)
            psi[i][j] = c2f(C, i*hx, j*hy, Mx, My);
}


void step(double **right_part, double **u_next, double **C, double **d, double hx, double hy, double tau, int Mx, int My, double coef)
{
    f2c(C, right_part, d, Mx, My);

    for (int i = 1; i < Mx; ++i)
        for (int j = 1; j < My; ++j)
            C[i][j] = C[i][j]/(coef * (lambda(i, hx) + lambda(j, hy)) + 1/tau);

    for (int i = 0; i < Mx+1; ++i)
        for (int j = 0; j < My+1; ++j)
            u_next[i][j] = c2f(C, i*hx, j*hy, Mx, My);
}

void right_part_omega(double **right_part, double **omega, double **psi, double **T_next, double hx, double hy, double tau, int Mx, int My, double G_coef)
{
    for (int i = 0; i < Mx+1; ++i)
        for (int j = 0; j < My+1; ++j)
            right_part[i][j] = 0;

    for (int i = 1; i < Mx; ++i)
        for (int j = 1; j < My; ++j)
            right_part[i][j] = 1/tau * omega[i][j] - (omega[i+1][j] - omega[i][j]) / hx * (psi[i][j+1] - psi[i][j]) / hy +
                                                     (omega[i][j+1] - omega[i][j]) / hy * (psi[i+1][j] - psi[i][j]) / hx +
                                                      G_coef * (T_next[i+1][j] - T_next[i-1][j])/(2*hx);
}


void right_part_T(double **right_part, double **T, double **psi, double hx, double hy, double tau, int Mx, int My, double rho_coef, double c_coef)
{
    for (int i = 0; i < Mx+1; ++i)
        for (int j = 0; j < My+1; ++j)
            right_part[i][j] = 0;

    for (int i = 1; i < Mx; ++i)
        for (int j = 1; j < My; ++j)
            right_part[i][j] = 1/tau * T[i][j] - (T[i+1][j] - T[i][j]) / hx * (psi[i][j+1] - psi[i][j]) / hy +
                                                 (T[i][j+1] - T[i][j]) / hy * (psi[i+1][j] - psi[i][j]) / hx +
                                                  q_func(i*hx, j*hy) / (rho_coef * c_coef);
}

void right_part_psi(double **right_part, double **omega, int Mx, int My)
{
    for (int i = 0; i < Mx+1; i++)
        for (int j = 0; j < My+1; j++)
            right_part[i][j] = -1 * omega[i][j];
}

int main()
{
    int Mx, My, N;
    double hx, hy, tau, nu_coef, k_coef, rho_coef, c_coef, G_coef;

    double **T;
    double **T_next;
    double **omega;
    double **omega_next;
    double **psi;
    double **right_part;
    double **C;
    double **d;

    FILE* out_T;
    FILE* out_omega;
    FILE* out_psi;

    FILE* out_last_T;
    FILE* out_last_omega;
    FILE* out_last_psi;

    out_T = fopen("output_T.txt", "w");
    out_omega = fopen("output_omega.txt", "w");
    out_psi = fopen("output_psi.txt", "w");

    printf("Введите Mx (количество узлов по x): ");
    scanf("%d", &Mx);
    My = Mx;
    printf("Введите N (количество узлов по t): ");
    scanf("%d", &N);

    hx = 1.0/Mx;
    hy = 1.0/My;
    tau = 1.0/N;

    nu_coef = 1e-4;
    k_coef = 1;
    rho_coef = 1;
    c_coef = 1;
    G_coef = 10;

    T = new double *[(Mx+1)];
    T_next = new double *[(Mx+1)];
    omega = new double *[(Mx+1)];
    omega_next = new double *[(Mx+1)];
    psi = new double *[(Mx+1)];
    right_part = new double *[(Mx+1)];
    C = new double *[(Mx+1)];
    d = new double *[(Mx+1)];

    for(int i = 0; i < Mx+1; ++i)
    {
        T[i] = new double[My+1];
        T_next[i] = new double[My+1];
        omega[i] = new double[My+1];
        omega_next[i] = new double[My+1];
        psi[i] = new double[My+1];
        right_part[i] = new double[My+1];
        C[i] = new double[My+1];
        d[i] = new double[My+1];
    }

    for (int i = 0; i < Mx+1; ++i)
    {
        for (int j = 0; j < My+1; ++j)
        {
            T[i][j] = 0;
            omega[i][j] = 0;
            psi[i][j] = 0;

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
        right_part_T(right_part, T, psi, hx, hy, tau, Mx, My, rho_coef, c_coef);
        step(right_part, T_next, C, d, hx, hy, tau, Mx, My, k_coef);

        right_part_omega(right_part, omega, psi, T_next, hx, hy, tau, Mx, My, G_coef);
        step(right_part, omega_next, C, d, hx, hy, tau, Mx, My, nu_coef);

        right_part_psi(right_part, omega, Mx, My);
        step_psi(right_part, psi, C, d, hx, hy, Mx, My);

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

    for(int i = 0; i < Mx+1; ++i)
    {
        delete [] T[i];
        delete [] T_next[i];
        delete [] omega[i];
        delete [] omega_next[i];
        delete [] psi[i];
        delete [] right_part[i];
        delete [] C[i];
        delete [] d[i];
    }

    delete []T;
    delete []T_next;
    delete []omega;
    delete []omega_next;
    delete []psi;
    delete []right_part;
    delete []C;
    delete []d;

    return 0;
}

